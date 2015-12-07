#ifdef ET_INGRESS_QOS
if (et->etc->dma_rx_policy) {
			left = (*chops->activerxbuf)(ch);
			/* Either we recovered or queued too many pkts or chain buffers are full */
			if (left + toss >= et->etc->dma_rx_thresh ||
				processed > (quota << PROC_CAP) || stop_chain) {
				/* we reached quota already */
				if (processed >= quota) {
					/* reschedule et_dpc()/et_poll() */
					et->resched = TRUE;
					break;
				}
			}
		}
		else
#endif /* ET_INGRESS_QOS */
		{
			/* we reached quota already */
			if (processed >= quota) {
				/* reschedule et_dpc()/et_poll() */
				et->resched = TRUE;
				break;
			}
		}
