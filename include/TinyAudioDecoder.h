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

#ifndef __TinyAudioDecoder__
#define __TinyAudioDecoder__

struct TinyAudioDecoderBuffer {
    void *leftChannelData;
    void *rightChannelData;
    int channelDataSize;
};

typedef unsigned int TINYAD_RESULT;

#define TINYAD_VERSION 0x00000903 // 0x00 HI ME LO

#define TINYAD_RESULT_SUCCESS               ((TINYAD_RESULT) 0x0000)
#define TINYAD_RESULT_EOF                   ((TINYAD_RESULT) 0x0001)
#define TINYAD_RESULT_INVALID_FILE          ((TINYAD_RESULT) 0x0002)
#define TINYAD_RESULT_INVALID_DST_BUFFER    ((TINYAD_RESULT) 0x0003)
#define TINYAD_RESULT_MALLOC_FAILURE        ((TINYAD_RESULT) 0x0004)
#define TINYAD_RESULT_DECODING_FAILURE      ((TINYAD_RESULT) 0x0005)
#define TINYAD_RESULT_NOT_INITIALIZED       ((TINYAD_RESULT) 0x0006)
#define TINYAD_RESULT_ALREADY_INITIALIZED	((TINYAD_RESULT) 0x0007)

class TinyAudioDecoder {
public:
    TinyAudioDecoder();
    ~TinyAudioDecoder();

    TINYAD_RESULT Initialize(const char* file, int sampleRate, bool stereo, TinyAudioDecoderBuffer *dstBuffer, void *platformExtras);
    TINYAD_RESULT ReadFrames(int &readFrameCount);
private:
    void *core;
};

#endif /* defined(__TinyAudioDecoder__) */
