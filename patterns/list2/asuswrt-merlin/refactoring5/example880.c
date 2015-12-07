#ifdef CONFIG_PC300_MLPPP
if (chan->conf.proto == PC300_PROTO_MLPPP) {
							/* verify if driver is TTY */
							if ((cpc_readb(scabase + DSR_RX(ch)) & DSR_DE)) {
								rx_dma_stop(card, ch);
							}
							cpc_tty_receive(d);
							rx_dma_start(card, ch);
						} else 
#endif
						{
							if ((cpc_readb(scabase + DSR_RX(ch)) & DSR_DE)) {
								rx_dma_stop(card, ch);
							}
							cpc_net_rx(dev);
							/* Discard invalid frames */
							hdlc_stats(dev)->rx_errors++;
							hdlc_stats(dev)->rx_over_errors++;
							chan->rx_first_bd = 0;
							chan->rx_last_bd = N_DMA_RX_BUF - 1;
							rx_dma_start(card, ch);
						}
