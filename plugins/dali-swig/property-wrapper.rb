#!/usr/bin/env ruby
require 'pathname'
require 'scanf'

# Script does the following:
# - greps dali-core for DALI_PROPERTY macro which holds all the information about a property ( type, read only etc)
# - uses the filename of the macro to detect the class the properties belong to. E.g. actor-impl.cpp  = Actor
# - Scans each property macro and builds a list of DALi classes with an array of properties
# - Generates the csharp get/set  code for each property
# - Pastes the property get / set code into the DALi csharp files

# Given a DALi C++ property type this table stores the
# information needed to produce a csharp getter / setter
$typeTable =  [
        ["BOOLEAN",     "bool",             "ref",  "bool temp = false;"],
        ["FLOAT",       "float",            "ref",  "float temp = 0.0f;"],
        ["INTEGER",     "int",              "ref",  "int temp = 0;"],
        ["VECTOR2",     "Vector2",          "",     "Vector2 temp = new Vector2(0.0f,0.0f);"],
        ["VECTOR3",     "Vector3",          "",     "Vector3 temp = new Vector3(0.0f,0.0f,0.0f);"],
        ["VECTOR4",     "Vector4",          "",     "Vector4 temp = new Vector4(0.0f,0.0f,0.0f,0.0f);"],
        ["MATRIX3",     "Matrix3",          "",     "Matrix3 temp = new Matrix3();"],
        ["MATRIX",      "Matrix",           "",     "Matrix temp = new Matrix();"  ],
        ["RECTANGLE",   "RectInteger",      "",     "RectInteger temp = new RectInteger(0,0,0,0);"],
        ["ROTATION",    "Quaternion",       "",    "Quaternion temp = new Quaternion();"],
        ["STRING",      "string",           "out",  "string temp;"],
        ["ARRAY",       "Dali.Property.Array",   "",     "Dali.Property.Array temp = new Dali.Property.Array();"],
        ["MAP",         "Dali.Property.Map",     "",     "Dali.Property.Map temp = new Dali.Property.Map();"],
    ]

# Some csharp classes are renamed ( e.g. C++ Control is called View in C#)
$renameMap = [
              ["Control", "View"]
             ]

$daliSwigPath = String.new;

def getCSharpName( cppClassName )

    entry = $renameMap.select{ |a| a.first == cppClassName }
    if( entry.empty?)
      return cppClassName
    end
    return entry[0][1]
end

# use the table above to get information for a specific type
def getCSharpType( type )

    entry = $typeTable.select{ |a| a.first == type }
    if( entry.empty? )
      return nil
    end
    return entry[0]
end


# Property struct stores the information about a property after parsing the C++ DALI_PROPERTY macro
$propertyStruct = Struct.new("Property", :name, :type, :writable, :animatable,:constrainInput, :enum, :shortenum,  :csharpGetter, :csharpSetter, :childProperty,)

# daliClass struct stores a class name and an array of properties
$daliClassStruct = Struct.new("DaliClass", :name, :properties )

# class array stores all the dali classes ( actor, image etc)
$daliClassArray = Array.new

# list of files not generated by swig that we have tried to inject properties into
$filesNotWrapped= Array.new

# stats
$totalProperties = 0
$totalDaliClasses = 0

# global paths
$rootPath = ""
$daliCorePath = ""
$daliSwigPath = ""

# Extracts data  DALI__PROPERTY( "points", ARRAY,true,false,false,Dali::Path::Property::POINTS )
def extractPropertyInfo( propertyMacro )

    # want to extract the property name, type + read only status
    # split the DALI_PROPERTY macro definition by comma and quotes, and delete any empty segments
    data = propertyMacro.split(/[\s,"]/).reject { |s| s.empty? }

    propertyName = data[1]

    # e.g. turn viewMatrix into ViewMatrix
    propertyName[0] = propertyName[0].capitalize

    # extract the property enum name Dali::Path::Property::POINTS -> POINTS
    shortenum =  data[6].split(":").last

    # store the :name, :type, :writable, :animatable, :constrainInput, :enum
    property = $propertyStruct.new;

    property.name = propertyName
    property.type = data[2]
    property.writable = (data[3]=="true")
    property.animatable = (data[4] == "true")
    property.constrainInput = (data[5]=="true")
    property.enum = shortenum

    return property;
end

# Extracts data from Toolkit property definition
def extractToolkitPropertyInfo( propertyMacro )

    # Extract the property name, type
    property = $propertyStruct.new;

    # Split the macro definition by comma and quotes, close bracket and delete any empty segments
    data = propertyMacro.split(/[\s,")]/).reject { |s| s.empty? }

    if(data[1] == "PropertyRegistration")

      # Properties defined in Control using PropertyRegistration
      # const PropertyRegistration Control::Impl::PROPERTY_1(typeRegistration, "styleName", Toolkit::Control::Property::STYLE_NAME, Property::STRING, &Control::Impl::SetProperty, &Control::Impl::GetProperty);

      # Creates an array of strings that looks like this:
      # const 0
      # PropertyRegistration 1
      # Control::Impl::PROPERTY_1 2
      # typeRegistration 3
      # styleName 4
      # Toolkit::Control::Property::STYLE_NAME 5
      # Property::STRING 6
      # &Control::Impl::SetProperty 7
      # &Control::Impl::GetProperty 8
      #

      property.name = data[4]

      propertyType = data[6].rpartition("::")
      property.type = propertyType[2]

      propertyEnum = data[5].rpartition("::")
      property.enum = propertyEnum[2]

    else

      # Properties defined in macro DALI_PROPERTY_REGISTRATION or DALI_ANIMATABLE_PROPERTY_REGISTRATION or DALI_CHILD_PROPERTY_REGISTRATION
      # or DALI_ANIMATABLE_PROPERTY_REGISTRATION_WITH_DEFAULT:
      # DALI_PROPERTY_REGISTRATION(Toolkit, TextLabel, "multiLine", BOOLEAN, MULTI_LINE)
      # DALI_ANIMATABLE_PROPERTY_REGISTRATION_WITH_DEFAULT(Toolkit, ImageView, "pixelArea", Vector4(0.f, 0.f, 1.f, 1.f), PIXEL_AREA)

      # Creates an array of strings that looks like this:
      # DALI_PROPERTY_REGISTRATION( 0
      # Toolkit 1
      # PageTurnView 2
      # pageSize 3
      # VECTOR2 4
      # PAGE_SIZE 5
      #

      property.name = data[3]

      #puts property.name
      if property.name == "image"
        property.name = "imageMap"
      end

      if( data[0] == "DALI_ANIMATABLE_PROPERTY_REGISTRATION_WITH_DEFAULT(" )
        # TODO: Need to work out the property type from the value
        property.type = "VECTOR4"
      else
        property.type = data[4]
      end

      property.enum = data[data.length-1]

    end

    # e.g. turn styleName into StyleName
    property.name[0] = property.name[0].capitalize

    property.writable = true
    property.animatable = false
    property.constrainInput = false
    property.childProperty = false;

    # check to see if it's a child property
    if( data[0] == "DALI_CHILD_PROPERTY_REGISTRATION(" )
      #puts(" #{property.name} is child property ")
      property.childProperty = true;
    end
    if( data[0] == "DALI_ANIMATABLE_PROPERTY_REGISTRATION(" )
      #puts("  #{property.name} is animatable")
      property.animatable = true;
    end

    return property;
end

def writePropertiesToCSharpFile( daliClass )

   # open the CSharp file autogenerated by SWIG
  swigFiles =  $daliSwigPath + "/automatic/csharp/"

  # some C++ classes are renamed for C#
  className = getCSharpName( daliClass.name )

  fileName =(swigFiles + className ) + ".cs"


  # it's possible some classes in dali-core aren't being wrapped by swig, so if the swig generated file
  # doesn't exist just return
  if( ! File.exist?(fileName) )
    $filesNotWrapped.push("#{daliClass.name}.cs ")
    return
  end

  File.open(fileName, 'r+') do |file|

  last_line  =0
  file.each { last_line = file.pos unless file.eof? }

  # we seek to the end of the file... minus 3 characters which lets us overwrite the 2 closing brackets
  # so we can insert the getter/setter stuff into the file.
  file.seek( last_line-3, IO::SEEK_SET)

  for property in daliClass.properties

    if (!property.childProperty)
      file.write( property.csharpGetter );
      file.write( property.csharpSetter );
    end

  end

  file.write("\n}\n\n}");  # re-insert the closing brackets we over-wrote
  end

  puts("Injected #{daliClass.properties.length} C# Properties from #{daliClass.name} into #{className}.cs".blueBackground)

end

def writeChildPropertiesToCSharpFile( daliClass )

  # open the CSharp file autogenerated by SWIG
  swigFiles =  $daliSwigPath + "/automatic/csharp/"

  # Add all the child properties to Control
  fileName = (swigFiles+"View") + ".cs"

  if( ! File.exist?(fileName) )
    return
  end

  File.open(fileName, 'r+') do |file|

  last_line  =0
  file.each { last_line = file.pos unless file.eof? }

  # we seek to the end of the file... minus 3 characters which lets us overwrite the 2 closing brackets
  # so we can insert the getter/setter stuff into the file.
  file.seek( last_line-3, IO::SEEK_SET)

  $childPropertyCount = 0

  for property in daliClass.properties

    if (property.childProperty)
      file.write( property.csharpGetter );
      file.write( property.csharpSetter );
      $childPropertyCount += 1
    end

  end

  file.write("\n}\n\n}");  # re-insert the closing brackets we over-wrote
  end

  puts("Injected #{$childPropertyCount} C# Child Properties into #{"View"}.cs".blueBackground)

end

# Write the CSharp data to the generated .cs file
def writeCSharpData

    for daliClass in  $daliClassArray

        #puts ( daliClass.name )


        hasChildProperties = false

        for property in daliClass.properties
            propertyInfo = getCSharpType( property.type )

            if( propertyInfo.length() < 2 )
                # some types aren't supported yet like Rotation
                next
            end

            $totalProperties+=1  #  keep track of total

            propertyType = propertyInfo[1]    # e.g. bool or int
            propertyArg =  propertyInfo[2]  # e.g. ref or out
            tempDeclaration = propertyInfo[3] # e.g. bool temp;

            csharpClassName = getCSharpName(daliClass.name);


            propertyName = "#{csharpClassName}.Property.#{property.enum}"

            if property.childProperty
              propertyName = "#{csharpClassName}.ChildProperty.#{property.enum}"
              hasChildProperties = true
            end

            property.csharpGetter ="  public #{propertyType} #{property.name} \n"\
                     "  { \n"\
                     "    get \n" \
                     "    {\n"\
                     "      #{tempDeclaration}\n"\
                     "      GetProperty( #{propertyName}).Get( #{propertyArg} temp );\n"\
                     "      return temp;\n"\
                     "    }\n"

            if property.writable
                  #text.SetProperty(TextLabel.Property.HORIZONTAL_ALIGNMENT, new Property.Value("CENTER"));
                  property.csharpSetter = "    set \n" \
                         "    { \n"\
                         "      SetProperty( #{propertyName}, new Dali.Property.Value( value ) );\n" \
                         "    }\n"\
                         "  }\n"
            else
                   property.csharpSetter = "}"  # close the opening property declaration
            end
        end
        # write normal properties to the class's own csharp file
        writePropertiesToCSharpFile( daliClass )
        # write child properties to View.cs ( on Control has child properties)
        if (hasChildProperties)
          writeChildPropertiesToCSharpFile( daliClass )
        end
    end

end

def getDaliClassItem( className )

   # puts( "getDaliClassItem  "+ className )
    index = $daliClassArray.index{ |a| a.name == className }

    if( index == nil)
        # create a new item along with a array for it's properites
        classItem = $daliClassStruct.new( className, Array.new )
        $daliClassArray.push( classItem )
        $totalDaliClasses+=1  # for stats
    else
        # puts("class found " + className )
        classItem = $daliClassArray[ index ]
    end

    return classItem;

end



def init

    pn = Pathname.new(Dir.pwd)
    fullPath = pn.to_s

    $rootPath = fullPath.slice(0..( fullPath.index('/dali-toolkit')))
    $daliCorePath = $rootPath + "dali-core/dali"   # source code path
    $daliSwigPath = $rootPath + "dali-toolkit/plugins/dali-swig"
    $daliToolkitPath = $rootPath + "dali-toolkit/dali-toolkit"  # source code path

    puts("--------------------------------------------")
    puts("Injecting DALi properties into SWIG generated C# files ")
    puts("")


end

def writeDaliCoreProperties

    puts("Scanning for DALI_PROPERTY macro in dali-core");
    puts("Scanning folder: #{$daliCorePath}\n\n");

    # Executed a recursive grep over dali-core for the DALI_PROPERTY macro
    result =`grep --include \\*.cpp  -r "DALI_PROPERTY( \" #{$daliCorePath}`


    # We now have a list of lines that look like this:
    # dali/internal/event/animation/path-impl.cpp:DALI__PROPERTY( "points", ARRAY,true,false,false,Dali::Path::Property::POINTS )

    lines = result.split(/\n+/);
    for line in lines


      # Split the line into file name and property macro, splt 2 means just create two strings as we don't want to split
      # property Dali::Path::Property::POINTS string as well

      data  = line.split(":",2)
      fileName = data[0];
      macro = data[1];

      # Get the class name from the filename  ( e.g. image-actor-impl.cpp => image-actor)
      className = File.basename(fileName,"-impl.cpp").capitalize

      # convert it from image-actor to ImageActor
      className = className.split(/ |\_|\-/).map(&:capitalize).join

      # Get the property information ( name, type, read/writeable)
      propertyInfo = extractPropertyInfo( macro );

      # get or create a new DALi class item which stores the property information
      classItem  = getDaliClassItem( className )

      classItem.properties.push( propertyInfo )

    end

    writeCSharpData()
end

def writeDaliToolkitProperties


    puts("\nScanning for PROPERTY_REGISTRATION macros in dali-toolkit");
    puts("Scanning folder: #{$daliToolkitPath}\n\n");

    $daliClassArray.clear;

    # Executed a recursive grep over dali-toolkit for following macros
    # DALI_PROPERTY_REGISTRATION
    # DALI_ANIMATABLE_PROPERTY_REGISTRATION
    # DALI_CHILD_PROPERTY_REGISTRATION
    result =`grep --include \\*.cpp  -w 'Control::Impl::SetProperty\\|DALI_ANIMATABLE_PROPERTY_REGISTRATION_WITH_DEFAULT(\\|DALI_CHILD_PROPERTY_REGISTRATION(\\|DALI_ANIMATABLE_PROPERTY_REGISTRATION(\\|DALI_PROPERTY_REGISTRATION' -r #{$daliToolkitPath}`

    if( result == "" )
      puts("Error parsing #{$daliToolkitPath} no properties found")
      return
    end
    # create an array to store each DALi class and it's assoc
    classArray = Array.new

    # We now have a list of lines that look like this:
    # text-controls/text-label-impl.cpp:DALI_PROPERTY_REGISTRATION( Toolkit, TextLabel, "multiLine", BOOLEAN, MULTI_LINE )
    lines = result.split(/\n+/);
    for line in lines


      # Split the line into file name and property macro, split 2 means just create two strings
      data  = line.split(":",2)
      fileName = data[0];
      macro = data[1];

      # Get the class name from the filename  ( e.g. image-actor-impl.cpp => image-actor)
      className = File.basename(fileName,"-impl.cpp").capitalize

      # convert it from image-actor to ImageActor
      className = className.split(/ |\_|\-/).map(&:capitalize).join

      #puts(className);
      #puts(fileName);

        # Get the property information ( name, type, read/writeable)
      propertyInfo = extractToolkitPropertyInfo( macro );

      # get or create a new DALi class item which stores the property information
      classItem  = getDaliClassItem( className )

      classItem.properties.push( propertyInfo )

    end

    writeCSharpData()

end

# helper class to color the background
class String
def blueBackground;   "\e[44m#{self}\e[0m" end
end

def writeStats

  puts("\nFiles that have not been wrapped file by SWIG ( not included in dali.i file):")
  for i in $filesNotWrapped
    puts(i)
  end

  puts("Done. Injected #{$totalProperties} properties into #{$totalDaliClasses} DALi C# classes".blueBackground)

end

init()

writeDaliCoreProperties()

writeDaliToolkitProperties()

writeStats()

