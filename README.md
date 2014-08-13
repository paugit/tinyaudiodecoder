## Tiny Audio Decoder

Tiny Audio Decoder provides a simple way to uncompress wav (8-bit, 16-bit, ulaw, alaw), mp3 and aac files into a PCM memory buffer through C++ on iOS and Android platforms. The audio frames can be read all at once or by reading a certain amount of frames at a time. Tiny Audio Decoder is written in C and C++ so you don’t need to write a single line of Objective-C or Java to use it.

### Requirements

Tiny Audio Decoder utilizes OpenSL ES library on Android and CoreFoundation and AudioToolbox frameworks on iOS. These are provided by the OS so no additional downloads are needed. However on Android API level 14 or higher is required.

### Limitations

Only one or two channel audio files are supported (mono/stereo). Audio resampling is currently only available on iOS. So on Android you should have the files already in the desired sample rate.

### Thread safety

Tiny Audio Decoder is not thread safe. You should not access it from multiple threads at the same time.

### Testing

Basic functionality has been tested with the following Android devices.

Device | Android version | Result
--- | --- | ---
Samsung Galaxy S5, SAMSUNG-SM-G900A | 4.4.2 | OK
LG Nexus 5 | 4.4 | OK
Sony XPERIA C6604 | 4.1.2 | OK
LG LG-E975 | 4.1.2 | OK
Samsung S ADVANCE, GT-I9070 | 4.1.2 | OK
Samsung DUOS, GT-S7562 | 4.0.4 | OK
LG Google, Galaxy Nexus | 4.3 | OK
Samsung, GT-I9100 | 4.1.2 | OK
Pantech VEGA, IM-A870L | 4.1.2 | OK
Samsung Galaxy Note, GT-N7000 | 4.1.2 | OK
Samsung GT-I8160 | 4.1.2 | OK

### Usage

Both platforms share the same TinyAudioDecoder.h header file. However to access audio files from the resources on Android and from a bundle on iOS a platform specific extras structure must be provided. The platform specific extras are specified in TinyAudioDecoder_Android.h and TinyAudioDecoder_iOS.h header files. Since Android application may only have one OpenSL ES engine instance you must also provide this in the extras structure incase your app has already initialized one. Incase NULL engine is defined, a new OpenSL ES engine instance will be created.

1. Create a TinyAudioDecoder instance and initialize it. Provide the destination decoding buffer and the platform specific extras. You should also set if you want the decoded audio to be in stereo or mono. You may also resample the audio to another sample rate however, this feature is not yet available on Android. On successful initialization, TINYAD_RESULT_SUCCESS is returned.

``` cpp
TINYAD_RESULT Initialize(const char* file, int sampleRate, bool stereo, TinyAudioDecoderBuffer *dstBuffer, void *platormExtras);
```

**Android extras:**

``` cpp
struct TinyAudioDecoderAndroidExtras {
	AAssetManager *assetManager;
	SLObjectItf engineObject;
	SLEngineItf engine;
};
```

**iOS extras:**

``` cpp
struct TinyAudioDecoderIosExtras {
	CFBundleRef bundle;
};
```

**Destination buffer:**

``` cpp
struct TinyAudioDecoderBuffer {
    void *leftChannelData;
    void *rightChannelData;
    int channelDataSize;
};
```

If you want to read all frames at once you should set the channel data pointers to NULL and channel data size to 0. In case you are streaming from a file, you must provide preallocated channel buffers and set their size in bytes, e.g. sizeof(TinyAudioDecoderSampleType) * 1024. 

2. Read frames from the file. On success the readFrameCount parameter will hold the read frame count and TINYAD_RESULT_SUCCESS is returned. When the end of the file is reached, TINYAD_RESULT_EOF is returned. On successful read operation the destination buffer is filled with the decoded data. The sample type is 32-bit signed integer (native endian) on iOS and 16-bit signed integer (little endian) on Android.

``` cpp
TINYAD_RESULT ReadFrames(int &readFrameCount);
```

3. Free the decoder

Platform independent error codes are defined in the TinyAudioDecoder.h and platform specific errors in TinyAudioDecoder_Android.h and TinyAudioDecoder_iOS.h.

### Example, read all frames at once

``` cpp
// Use the main bundle
TinyAudioDecoderIosExtras platformExtras;
platformExtras.bundle = CFBundleGetMainBundle();

// Set channel data size to 0 to read all frames at once
TinyAudioDecoderBuffer dstBuffer;
dstBuffer.channelDataSize = 0;
dstBuffer.leftChannelData = NULL;
dstBuffer.rightChannelData = NULL;

TinyAudioDecoder *decoder = new TinyAudioDecoder();

int frameCount = 0;

if(decoder->Initialize(file, 44100, true, &dstBuffer, &platformExtras) == TINYAD_RESULT_SUCCESS) {
    // Read all frames at once
    if(decoder->ReadFrames(frameCount) == TINYAD_RESULT_SUCCESS) {
        for(int i=0; i<frameCount; i++) {
            // do something with dstBuffer.leftChannelData[i]
            // do something with dstBuffer.rightChannelData[i]
        }

        // Free the data when finished
        if(dstBuffer.leftChannelData != NULL) {
            free(dstBuffer.leftChannelData);
            dstBuffer.leftChannelData = NULL;
        }

        if(dstBuffer.rightChannelData != NULL) {
            free(dstBuffer.rightChannelData);
            dstBuffer.rightChannelData = NULL;
        }
    }
}

delete decoder;
```

### Example, read 2048 frames at a time

``` cpp
TinyAudioDecoderIosExtras platformExtras;
platformExtras.bundle = CFBundleGetMainBundle();

TinyAudioDecoderBuffer dstBuffer;
int channelDataSize = sizeof(TinyAudioDecoderSampleType) * 2048;

dstBuffer.channelDataSize = channelDataSize;
dstBuffer.leftChannelData = malloc(channelDataSize);
dstBuffer.rightChannelData = malloc(channelDataSize);

TinyAudioDecoder *decoder = new TinyAudioDecoder();

if(decoder->Initialize(file, 44100, true, &dstBuffer, &platformExtras) == TINYAD_RESULT_SUCCESS) {
    int frameCount = 0;
    do {
        TINYAD_RESULT result = decoder->ReadFrames(frameCount);

        if(result == TINYAD_RESULT_SUCCESS) {
            // Copy frames to a circular buffer or do something with the data
            // dstBuffer.leftChannelData and dstBuffer.rightChannelData
            LOGD("Got %d frames of audio data", frameCount);
        }
        else {
            if(result == TINYAD_RESULT_EOF) {
                LOGD("End of file reached");
            }
            else {
                LOGD("Error %d occured", result);
            }
            break;
        }
    } while(frameCount > 0);
}

free(dstBuffer.leftChannelData);
free(dstBuffer.rightChannelData);

delete decoder;
```
