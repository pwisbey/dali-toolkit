#
# Copyright (c) 2016 Samsung Electronics Co., Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

m4_define([dali_version],[0.1.0])
AC_INIT([dali], [dali_version])
AM_INIT_AUTOMAKE([-Wall foreign])

AC_PROG_CXX
AC_PROG_LIBTOOL

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

LT_INIT

DALI_TOOLKIT_VERSION=dali_version
AC_SUBST(DALI_TOOLKIT_VERSION)

PKG_CHECK_MODULES(DALICORE, dali-core)

DALI_TOOLKIT_CFLAGS=-DPLATFORM_TIZEN

AC_ARG_ENABLE(exportall,
              [AC_HELP_STRING([--enable-exportall],
                              [enables the exporting of all the symbols in the library])],
              [enable_exportall=yes],
              [enable_exportall=no])

AC_ARG_ENABLE([debug],
              [AC_HELP_STRING([--enable-debug],
                              [Turns on debugging])],
              [enable_debug=$enableval],
              [enable_debug=no])

AC_ARG_ENABLE([i18n],
              [AC_HELP_STRING([--enable-i18n],
                              [Turns on internationalisation])],
              [enable_i18n=$enableval],
              [enable_i18n=no])

# option to build JavaScript plugin
# configure settings and output
# --enable-javascript        // enable_javascript = yes
# --enable-javascript=yes    // enable_javascript = yes
# --enable-javascript=no     // enable_javascript = no
# --disable-javascript       // enable_javascript = no
#  no setting                // enable_javascript = automatic ( enable if v8 present)
AC_ARG_ENABLE([javascript],
              [AC_HELP_STRING([--enable-javascript],
                [Enable JavaScript plugin])],
              [enable_javascript=$enableval],
              [enable_javascript=automatic])

# option to build C# plugin
# configure settings and output
# --enable-csharp        // enable_csharp = yes
# --enable-csharp=yes    // enable_csharp = yes
# --enable-csharp=no     // enable_csharp = no
#  no setting            // enable_csharp = no
AC_ARG_ENABLE([csharp],
              [AC_HELP_STRING([--enable-csharp],
                [Enable csharp plugin])],
              [enable_csharp=$enableval],
              [enable_csharp=automatic])

if test "x$enable_debug" = "xyes"; then
  DALI_TOOLKIT_CFLAGS="$DALI_TOOLKIT_CFLAGS -DDEBUG_ENABLED"
fi

if test "x$enable_debug" = "xno" -a "x$enable_exportall" = "xno"; then
  DALI_TOOLKIT_CFLAGS="$DALI_TOOLKIT_CFLAGS -fvisibility=hidden -DHIDE_DALI_INTERNALS"
fi

if test "x$enable_i18n" = "xyes"; then
  DALI_TOOLKIT_CFLAGS="$DALI_TOOLKIT_CFLAGS -DDGETTEXT_ENABLED "
fi

# Tizen Profile options
AC_ARG_ENABLE([profile],
              [AC_HELP_STRING([--enable-profile=UBUNTU,MOBILE,WEARABLE,TV],
                            [Select the variant of tizen])],
              [dali_profile=$enableval],
              [dali_profile=UBUNTU])

# Tizen Style Folder
AC_ARG_WITH(style,
              [AC_HELP_STRING([--with-style],
                            [Select the style folder to use])],
              [dali_style=$withval],
              [dali_style=480x800])

# Ensure valid profile selected
if test "x$dali_profile" != "xUBUNTU" -a "x$dali_profile" != "xMOBILE" -a "x$dali_profile" != "xWEARABLE" -a "x$dali_profile" != "xTV" ; then
  AC_MSG_ERROR([$enable_profile is an invalid profile])
fi

if test x$DALI_DATA_RW_DIR != x; then
  dataReadWriteDir=${DALI_DATA_RW_DIR}/
else
  dataReadWriteDir=${prefix}/share/dali/
fi

if test x$DALI_DATA_RO_DIR != x; then
  dataReadOnlyDir=${DALI_DATA_RO_DIR}/
else
  dataReadOnlyDir=${prefix}/share/dali/
fi

DALI_TOOLKIT_CFLAGS="$DALI_TOOLKIT_CFLAGS -DDALI_PROFILE_${dali_profile}"

# Style folder
STYLE_BASE_DIR=../../../dali-toolkit/styles
STYLE_DIR=$STYLE_BASE_DIR/$dali_style

AC_SUBST(STYLE_BASE_DIR)
AC_SUBST(STYLE_DIR)

# v8 version 4+ requires c++11
PKG_CHECK_MODULES(V8, v8 = 3.32.7, [ pkg_check_v8=yes ],  [ pkg_check_v8=no  ] )

# Rules for building JavaScript plugin
# If enable_javascript=yes and v8 installed = build javascript
# If enable_javascript=automatic and v8 installed = build javascript
# If enable_javascript=yes and v8 not installed = throw an error
build_javascript_plugin=no
if test x$enable_javascript = xyes; then
  if test x$pkg_check_v8 = xno; then
    [build_javascript_plugin=no]
    AC_MSG_ERROR("V8 not found or incorrect version installed")
    AC_MSG_NOTICE("To disable building of JavaScript plugin use --disable-javascript")
  else
    [build_javascript_plugin=yes]
    AC_MSG_NOTICE(V8 library found. Building DALi JavaScript plugin)
  fi
fi
if test x$enable_javascript = xautomatic && test x$pkg_check_v8 = xyes; then
  [build_javascript_plugin=yes]
  AC_MSG_NOTICE( V8 library found. Automatic building of JavaScript plugin. Use  use --disable-javascript to disable)
fi


#set a variable for the makefile to force compile the JAvaSplugin
AM_CONDITIONAL([ENABLE_JAVASCRIPT_PLUGIN], [test x$build_javascript_plugin = xyes])

# Platforms with highp shader support can use vector based text
AM_CONDITIONAL([ENABLE_VECTOR_BASED_TEXT_RENDERING], [test x$dali_profile = xUBUNTU])

AC_SUBST(dataReadWriteDir)
AC_SUBST(dataReadOnlyDir)
AC_SUBST(DALI_TOOLKIT_CFLAGS)


# Specify the include directory for development headers
#devincludepath=${includedir}/dali/internal
devincludepath=${includedir}
AC_SUBST(devincludepath)

# Doxygen paths
DOXYGEN_DOCS_DIR=../../../docs
DOXYGEN_ROOT_DIR=../../..
AC_SUBST(DOXYGEN_DOCS_DIR)
AC_SUBST(DOXYGEN_ROOT_DIR)

# Enable csharp plugin
build_csharp_plugin=no
build_ruby_flag=no
if test x$enable_csharp = xyes; then
  [build_csharp_plugin=yes]
  AC_MSG_NOTICE(Building DALi csharp plugin ...)

  PKG_CHECK_MODULES(DALIADAPTOR, dali-adaptor)
  AC_PATH_PROG([SWIG], [swig])

  # if gbs enable, then only use swig, without ruby or mcs
  if test "x$dali_profile" = "xUBUNTU"; then
    [build_ruby_flag=yes]
    AC_PATH_PROG([RUBY], [ruby])
    AC_PATH_PROGS([MCS], [mcs gmcs gmcs2])
    AC_MSG_NOTICE(swig ruby mcs working ...)
  else
    [build_ruby_flag=no]
    AC_PATH_PROG([RUBY], [ruby])
    #AC_PATH_PROGS([MCS], [mcs gmcs gmcs2])
    #AC_MSG_NOTICE(swig only working ...)
  fi

  # Set varaibles for dali-toolkit
  DALITOOLKIT_CFLAGS="-I${prefix}/include -I${prefix}/include/dali-toolkit"
  DALITOOLKIT_LIBS="-L${prefix}/lib -ldali-toolkit -ldali-core"
  AC_SUBST(DALITOOLKIT_CFLAGS)
  AC_SUBST(DALITOOLKIT_LIBS)
fi

#set a variable for the makefile to force compile the csharp plugin
AM_CONDITIONAL([ENABLE_CSHARP_PLUGIN], [test x$build_csharp_plugin = xyes])
AM_CONDITIONAL([ENABLE_RUBY_FLAG], [test x$build_ruby_flag = xyes])

AC_CONFIG_FILES([
 Makefile
 dali-toolkit/Makefile
 plugins/javascript/Makefile
 plugins/csharp/Makefile
 dali-toolkit.pc
 docs/Makefile
 docs/dali.doxy
 docs-internal/dali-internal.doxy
 ../../automated-tests/CMakeLists.txt
])

AC_OUTPUT

echo "
Configuration
-------------
  Prefix:                           $prefix
  Debug Build:                      $enable_debug
  JavaScript support (V8 required)  $build_javascript_plugin
  CSharp support                    $build_csharp_plugin
  Profile:                          $dali_profile
  Data Dir (Read/Write):            $dataReadWriteDir
  Data Dir (Read Only):             $dataReadOnlyDir
  Style Dir:                        $STYLE_DIR
  Style:                            $dali_style
  i18n:                             $enable_i18n
"
