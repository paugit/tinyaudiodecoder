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

#ifndef __TinyAudioDecoder_Android__
#define __TinyAudioDecoder_Android__

#ifdef ANDROID

#include <SLES/OpenSLES.h>
#include <android/asset_manager.h>

struct TinyAudioDecoderAndroidExtras {
    AAssetManager *assetManager;
    SLObjectItf engineObject;
    SLEngineItf engine;
};

typedef SLint16 TinyAudioDecoderSampleType;

#define TINYAD_RESULT_ASSETMANAGER_INVALID			((TINYAD_RESULT) 0x0101)
#define TINYAD_RESULT_ASSET_OPEN_FAILED				((TINYAD_RESULT) 0x0102)
#define TINYAD_RESULT_ASSET_SL_ENGINE_INIT_FAILED	((TINYAD_RESULT) 0x0103)
#define TINYAD_RESULT_ASSET_SL_PLAYER_INIT_FAILED	((TINYAD_RESULT) 0x0104)

#endif /* defined(ANDROID) */

#endif /* defined(__TinyAudioDecoder_Android__) */
