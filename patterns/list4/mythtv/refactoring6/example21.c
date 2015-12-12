if (ret == 0 && new_pkt.data != pkt->data
#if FF_API_DESTRUCT_PACKET
            && new_pkt.destruct
#endif
            ) {
FF_ENABLE_DEPRECATION_WARNINGS
            if ((ret = av_copy_packet(&new_pkt, pkt)) < 0)
                break;
            ret = 1;
        }
