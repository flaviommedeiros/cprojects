#ifdef VGM_USE_MPEG
if (vgmstream->layout_type==layout_fake_mpeg||
        vgmstream->layout_type==layout_mpeg) {
        mpeg_codec_data *data = vgmstream->codec_data;

        if (data) {
            mpg123_delete(data->m);
            free(vgmstream->codec_data);
            vgmstream->codec_data = NULL;
            /* The astute reader will note that a call to mpg123_exit is never
             * made. While is is evilly breaking our contract with mpg123, it
             * doesn't actually do anything except set the "initialized" flag
             * to 0. And if we exit we run the risk of turning it off when
             * someone else in another thread is using it. */
        }
    }
