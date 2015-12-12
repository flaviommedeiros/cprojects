if (!pkt->buf && pkt->data
#if FF_API_DESTRUCT_PACKET
        && !pkt->destruct
#endif
        ) {
FF_ENABLE_DEPRECATION_WARNINGS
        tmp_pkt = *pkt;
        return copy_packet_data(pkt, &tmp_pkt, 1);
    }
