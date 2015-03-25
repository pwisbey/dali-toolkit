#ifndef __DALI_V8PLUGIN_PATH_CONSTRAINT_WRAPPER_H__
#define __DALI_V8PLUGIN_PATH_CONSTRAINT_WRAPPER_H__

/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// EXTERNAL INCLUDES
#include <v8.h>
#include <dali/public-api/animation/path-constraint.h>

// INTERNAL INCLUDES
#include <object/handle-wrapper.h>


namespace Dali
{

namespace V8Plugin
{

/**
 * Wraps a Path.
 */
class PathConstraintWrapper : public HandleWrapper
{

public:

  /**
   * Constructor
   */
  PathConstraintWrapper( PathConstraint pathConstraint, GarbageCollectorInterface& gc );

  /**
   * Virtual destructor
   */
  virtual ~PathConstraintWrapper(){};

  /**
   * Creates a new PathConstraint wrapped inside a Javascript Object.
   * @param[in] args v8 function call arguments interpreted
   */
  static void NewPathConstraint( const v8::FunctionCallbackInfo< v8::Value >& args);

  /**
   * Wraps a PathConstraint inside a Javascript object
   */
  static v8::Handle<v8::Object> WrapPathConstraint(v8::Isolate* isolate, PathConstraint pathConstraint );

  /*
   * Get the wrapped PathConstraint
   */
  PathConstraint GetPathConstraint();

private:

  /**
   * Create a v8 object template for the PathConstraint
   */
  static v8::Handle<v8::ObjectTemplate> MakePathConstraintTemplate( v8::Isolate* isolate );

  PathConstraint mPathConstraint;
};

} // namespace V8Plugin

} // namespace Dali

#endif // header
