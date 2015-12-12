if (
#ifdef BCMSDIOH_TXGLOM
				!need_txglom &&
#endif
				TRUE) {
				int align_pkt_len = 0;
				align_pkt_len = sdioh_request_packet_align(pkt_len, write,
					func, blk_size);

				pad = align_pkt_len - pkt_len;
				if (pad > 0) {
					if (func == SDIO_FUNC_2) {
						sd_err(("%s: padding is unexpected! pkt_len %d,"
						" PKTLEN %d lft_len %d %s\n",
						__FUNCTION__, pkt_len, PKTLEN(sd->osh, pnext),
							lft_len, write ? "Write" : "Read"));
					}
					if (PKTTAILROOM(sd->osh, pkt) < pad) {
						sd_info(("%s: insufficient tailroom %d, pad %d,"
						" lft_len %d pktlen %d, func %d %s\n",
						__FUNCTION__, (int)PKTTAILROOM(sd->osh, pkt),
						pad, lft_len, PKTLEN(sd->osh, pnext), func,
						write ? "W" : "R"));
						if (PKTPADTAILROOM(sd->osh, pkt, pad)) {
							sd_err(("%s: padding error size %d.\n",
								__FUNCTION__, pad));
							return SDIOH_API_RC_FAIL;
						}
					}
				}
			}
