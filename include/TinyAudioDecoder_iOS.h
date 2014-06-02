/*
 * Copyright 2014 Pauli Ojanen
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __TinyAudioDecoder_iOS__
#define __TinyAudioDecoder_iOS__

#ifdef __APPLE__

#include <CoreFoundation/CoreFoundation.h>

struct TinyAudioDecoderIosExtras {
	CFBundleRef bundle;
};

//typedef signed long TinyAudioDecoderSampleType;
typedef signed int TinyAudioDecoderSampleType;

#define TINYAD_RESULT_INVALID_BUNDLE            ((TINYAD_RESULT) 0x0101)
#define TINYAD_RESULT_SET_FORMAT_FAILED         ((TINYAD_RESULT) 0x0102)
#define TINYAD_RESULT_GET_FRAME_COUNT_FAILED    ((TINYAD_RESULT) 0x0103)

#endif /* defined(__APPLE__) */

#endif /* defined(__TinyAudioDecoder_iOS__) */
