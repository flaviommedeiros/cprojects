#ifdef NET_SKBUFF_DATA_USES_OFFSET
if (pkt->vp_tail != skb->tail)
#else
            if (pkt->vp_tail != (skb->tail - skb->head))
                goto error;
