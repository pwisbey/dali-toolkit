//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.9
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace Dali {

public enum PropertyRanges {
  DEFAULT_OBJECT_PROPERTY_START_INDEX = 0,
  DEFAULT_ACTOR_PROPERTY_START_INDEX = DEFAULT_OBJECT_PROPERTY_START_INDEX,
  DEFAULT_ACTOR_PROPERTY_MAX_COUNT = 10000,
  DEFAULT_DERIVED_ACTOR_PROPERTY_START_INDEX = DEFAULT_ACTOR_PROPERTY_START_INDEX+DEFAULT_ACTOR_PROPERTY_MAX_COUNT,
  DEFAULT_PROPERTY_MAX_COUNT_PER_DERIVATION = 10000,
  DEFAULT_GESTURE_DETECTOR_PROPERTY_START_INDEX = DEFAULT_DERIVED_ACTOR_PROPERTY_START_INDEX,
  DEFAULT_RENDERER_PROPERTY_START_INDEX = 9000000,
  DEFAULT_RENDERER_PROPERTY_MAX_INDEX = DEFAULT_RENDERER_PROPERTY_START_INDEX+100000,
  PROPERTY_REGISTRATION_START_INDEX = 10000000,
  DEFAULT_PROPERTY_MAX_COUNT = PROPERTY_REGISTRATION_START_INDEX,
  PROPERTY_REGISTRATION_MAX_INDEX = 19999999,
  ANIMATABLE_PROPERTY_REGISTRATION_START_INDEX = 20000000,
  ANIMATABLE_PROPERTY_REGISTRATION_MAX_INDEX = 29999999,
  CHILD_PROPERTY_REGISTRATION_START_INDEX = 45000000,
  CHILD_PROPERTY_REGISTRATION_MAX_INDEX = 49999999,
  PROPERTY_CUSTOM_START_INDEX = 50000000,
  PROPERTY_CUSTOM_MAX_INDEX = 59999999,
  CORE_PROPERTY_MAX_INDEX = PROPERTY_CUSTOM_MAX_INDEX
}

}
