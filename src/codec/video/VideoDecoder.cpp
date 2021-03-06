/******************************************************************************
    QtAV:  Media play library based on Qt and FFmpeg
    Copyright (C) 2012-2015 Wang Bin <wbsecg1@gmail.com>

*   This file is part of QtAV

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/

#include "QtAV/VideoDecoder.h"
#include "QtAV/private/AVDecoder_p.h"
#include "QtAV/private/factory.h"
#include "utils/Logger.h"

namespace QtAV {
FACTORY_DEFINE(VideoDecoder)

void VideoDecoder_RegisterAll()
{
    extern bool RegisterVideoDecoderFFmpeg_Man();
    RegisterVideoDecoderFFmpeg_Man();
#if QTAV_HAVE(DXVA)
    extern bool RegisterVideoDecoderDXVA_Man();
    RegisterVideoDecoderDXVA_Man();
#endif //QTAV_HAVE(DXVA)
#if QTAV_HAVE(CUDA)
    extern bool RegisterVideoDecoderCUDA_Man();
    RegisterVideoDecoderCUDA_Man();
#endif //QTAV_HAVE(CUDA)
#if QTAV_HAVE(VAAPI)
    extern bool RegisterVideoDecoderVAAPI_Man();
    RegisterVideoDecoderVAAPI_Man();
#endif //QTAV_HAVE(VAAPI)
#if QTAV_HAVE(VIDEOTOOLBOX)
    extern bool RegisterVideoDecoderVideoToolbox_Man();
    RegisterVideoDecoderVideoToolbox_Man();
#endif //QTAV_HAVE(VIDEOTOOLBOX)
#if QTAV_HAVE(VDA)
    extern bool RegisterVideoDecoderVDA_Man();
    RegisterVideoDecoderVDA_Man();
#endif //QTAV_HAVE(VDA)
#if QTAV_HAVE(CEDARV)
    extern bool RegisterVideoDecoderCedarv_Man();
    RegisterVideoDecoderCedarv_Man();
#endif //QTAV_HAVE(CEDARV)
}
QVector<VideoDecoderId> VideoDecoder::registered()
{
    return QVector<VideoDecoderId>::fromStdVector(VideoDecoderFactory::Instance().registeredIds());
}

QStringList VideoDecoder::supportedCodecs()
{
    static QStringList codecs;
    if (!codecs.isEmpty())
        return codecs;
    avcodec_register_all();
    AVCodec* c = NULL;
    while ((c=av_codec_next(c))) {
        if (!av_codec_is_decoder(c) || c->type != AVMEDIA_TYPE_VIDEO)
            continue;
        codecs.append(QString::fromLatin1(c->name));
    }
    return codecs;
}

VideoDecoder::VideoDecoder(VideoDecoderPrivate &d):
    AVDecoder(d)
{
}

QString VideoDecoder::name() const
{
    return QLatin1String(VideoDecoder::name(id()));
}
} //namespace QtAV
