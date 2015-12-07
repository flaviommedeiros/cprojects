#ifdef PLC
if (et_plc_pkt(et, evh)) {
				if (et_plc_recv(et, p) == BCME_ERROR)
					return 0;
				if (cd[i].chead == p) {
					evh = PKTDATA(et->osh, p);
					cd[i].h_da = evh;
					cd[i].h_sa = evh + ETHER_ADDR_LEN;
					cd[i].h_prio = prio;
				}
			} else
#endif /* PLC */
			{
				/* update header for non-first frames */
				if (cd[i].chead != p)
					CTF_HOTBRC_L2HDR_PREP(et->osh, et->brc_hot, prio,
					                      PKTDATA(et->osh, p), p);
			}
