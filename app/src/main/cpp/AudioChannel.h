// TODO 专门单独处理音频，解码来播放

#ifndef KEVINPLAYER_AUDIOCHANNEL_H
#define KEVINPLAYER_AUDIOCHANNEL_H


#include "BaseChannel.h"

// 为了播放喇叭
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

extern "C" {
    #include <libswscale/swscale.h>
    #include <libavutil/channel_layout.h>
    #include <libswresample/swresample.h> // 重采样支持
};

class AudioChannel : public BaseChannel
{
public:
    AudioChannel(int stream_index, AVCodecContext *pContext, AVRational rational);

    ~AudioChannel();

    void stop();

    void start();

    void audio_decode();

    void audio_player();

    int getPCM();

    // 定义一个缓冲区
    uint8_t * out_buffers = 0;

    int out_channels;
    int out_sample_size;
    int out_sample_rate;
    int out_buffers_size;

private:
    // 线程ID
    pthread_t pid_audio_decode;
    pthread_t pid_audio_player;

    // 引擎
    SLObjectItf engineObject;
    // 引擎接口
    SLEngineItf engineInterface;
    // 混音器
    SLObjectItf outputMixObject;
    // 播放器的
    SLObjectItf bqPlayerObject;
    // 播放器接口
    SLPlayItf bqPlayerPlay;

    // 获取播放器队列接口
    SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;

    // 音频转换 ==（重采样）
    SwrContext *swr_ctx;
};


#endif //KEVINPLAYER_AUDIOCHANNEL_H
