#ifdef PLC
if (et_plc_pkt(et, evh)) {
					if (PLC_PKT_CHAINABLE(et, p, evh, prio, cd[i].h_sa,
					                  cd[i].h_da, cd[i].h_prio))
						break;
					else if ((i + 1 < PKTCMC) && (cd[i + 1].h_da == NULL)) {
						cidx++;
						cd[cidx].h_da = evh;
						cd[cidx].h_sa = evh + ETHER_ADDR_LEN;
						cd[cidx].h_prio = prio;
					}
				} else
#endif /* PLC */
				{
					if (PKT_CHAINABLE(et, p, evh, prio, cd[i].h_sa,
					                  cd[i].h_da, cd[i].h_prio))
						break;
					else if ((i + 1 < PKTCMC) && (cd[i + 1].h_da == NULL)) {
						cidx++;
						cd[cidx].h_da = evh;
						cd[cidx].h_sa = evh + ETHER_ADDR_LEN;
						cd[cidx].h_prio = prio;
					}
				}
