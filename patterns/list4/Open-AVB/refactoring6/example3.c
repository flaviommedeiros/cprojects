if (data_len == 0 ||
		    data_len > IGB_CB(lro_skb)->mss ||
		    data_len > IGB_CB(lro_skb)->free ||
#ifndef CONFIG_IGB_DISABLE_PACKET_SPLIT
		    data_len != new_skb->data_len ||
		    skb_shinfo(new_skb)->nr_frags >=
		    (MAX_SKB_FRAGS - skb_shinfo(lro_skb)->nr_frags) ||
#endif
		    igb_lro_hdr(lro_skb)->th.ack_seq != lroh->th.ack_seq ||
		    igb_lro_hdr(lro_skb)->th.window != lroh->th.window) {
			igb_lro_flush(q_vector, lro_skb);
			break;
		}
