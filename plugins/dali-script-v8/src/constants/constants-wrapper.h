#ifndef __DALI_V8PLUGIN_DALI_CONSTANTS_WRAPPER
#define __DALI_V8PLUGIN_DALI_CONSTANTS_WRAPPER
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


namespace Dali
{

namespace V8Plugin
{

namespace  ConstantsWrapper
{

void AddDaliConstants( v8::Isolate* isolate, v8::Local<v8::Object >& obj  );
} // namespace ConstantsWrapper

} // namespace V8Plugin

} // namespace Dali
#endif
