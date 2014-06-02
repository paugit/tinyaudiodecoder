Tiny Audio Decoder

Tiny Audio Decoder provides a simple way to uncompress wav (8-bit, 16-bit, ulaw, alaw), mp3 and aac files into a PCM memory buffer through C++ on iOS and Android platforms. The audio frames can be read all at once or by reading a certain amount of frames at a time. Tiny Audio Decoder is written in C and C++ so you don’t need to write a single line of Objective-C or Java to use it.

Requirements

Tiny Audio Decoder utilizes OpenSL ES library on Android and CoreFoundation and AudioToolbox frameworks on iOS. These are provided by the OS so no additional downloads are needed. However on Android API level 14 or higher is required.

Limitations

Only one or two channel audio files are supported (mono/stereo). Audio resampling is currently only available on iOS. So on Android you should have the files already in the desired sample rate.

Thread safety

Tiny Audio Decoder is not thread safe. You should not access it from multiple threads at the same time.

Testing

This is the first very poorly tested public beta. :)

Usage

Both platforms share the same TinyAudioDecoder.h header file. However to access audio files from the resources on Android and from a bundle on iOS a platform specific extras structure must be provided. The platform specific extras are specified in TinyAudioDecoder_Android.h and TinyAudioDecoder_iOS.h header files. Since Android application may only have one OpenSL ES engine instance you must also provide this in the extras structure incase your app has already initialized one. Incase NULL engine is defined, a new OpenSL ES engine instance will be created.

1. Create a TinyAudioDecoder instance and initialize it. Provide the destination decoding buffer and the platform specific extras. You should also set if you want the decoded audio to be in stereo or mono. You may also resample the audio to another sample rate however, this feature is not yet available on Android. On successful initialization, TINYAD_RESULT_SUCCESS is returned.

``` cpp
TINYAD_RESULT Initialize(const char* file, int sampleRate, bool stereo, TinyAudioDecoderBuffer *dstBuffer, void *platormExtras);
```

Android extras:

``` cpp
struct TinyAudioDecoderAndroidExtras {
	AAssetManager *assetManager;
	SLObjectItf engineObject;
	SLEngineItf engine;
};
```

iOS extras:

``` cpp
struct TinyAudioDecoderIosExtras {
	CFBundleRef bundle;
};
```

Destination buffer:

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
