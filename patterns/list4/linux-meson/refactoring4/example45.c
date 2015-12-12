#ifdef RLD_TRANS_DEBUG
if (1 || cxt1e1_log_level >= LOG_MONITOR)
#else
		    if (cxt1e1_log_level >= LOG_MONITOR)
#endif
		    {
			pr_info("%s: TX buffer underflow [ONR] on channel %d, mode %x QStopped %x free %d\n",
				ci->devname, ch->channum, ch->p.chan_mode, sd_queue_stopped(ch->user), ch->txd_free);
#ifdef RLD_DEBUG
			if (ch->p.chan_mode == 2) {     /* problem = ONR on HDLC
							 * mode */
			    pr_info("++ Failed Last %x Next %x QStopped %x, start_tx %x tx_full %d txd_free %d mode %x\n",
				    (u_int32_t) ch->txd_irq_srv, (u_int32_t) ch->txd_usr_add,
				    sd_queue_stopped(ch->user),
				    ch->ch_start_tx, ch->tx_full, ch->txd_free, ch->p.chan_mode);
			    musycc_dump_txbuffer_ring(ch, 0);
			}
#endif
		    }
