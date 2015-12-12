if(a == 0 && new_pkt.data != pkt->data
#if FF_API_DESTRUCT_PACKET
           && new_pkt.destruct
#endif
           ) {
FF_ENABLE_DEPRECATION_WARNINGS
            uint8_t *t = av_malloc(new_pkt.size + AV_INPUT_BUFFER_PADDING_SIZE); //the new should be a subset of the old so cannot overflow
            if(t) {
                memcpy(t, new_pkt.data, new_pkt.size);
                memset(t + new_pkt.size, 0, AV_INPUT_BUFFER_PADDING_SIZE);
                new_pkt.data = t;
                new_pkt.buf = NULL;
                a = 1;
            } else
                a = AVERROR(ENOMEM);
        }
