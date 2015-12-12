#ifdef V4L2_BUF_FLAG_ERROR
if (buf.flags & V4L2_BUF_FLAG_ERROR) {
        av_log(ctx, AV_LOG_WARNING,
               "Dequeued v4l2 buffer contains corrupted data (%d bytes).\n",
               buf.bytesused);
        buf.bytesused = 0;
    } else
#endif
    {
        /* CPIA is a compressed format and we don't know the exact number of bytes
         * used by a frame, so set it here as the driver announces it. */
        if (ctx->video_codec_id == AV_CODEC_ID_CPIA)
            s->frame_size = buf.bytesused;

        if (s->frame_size > 0 && buf.bytesused != s->frame_size) {
            av_log(ctx, AV_LOG_ERROR,
                   "Dequeued v4l2 buffer contains %d bytes, but %d were expected. Flags: 0x%08X.\n",
                   buf.bytesused, s->frame_size, buf.flags);
            enqueue_buffer(s, &buf);
            return AVERROR_INVALIDDATA;
        }
    }
