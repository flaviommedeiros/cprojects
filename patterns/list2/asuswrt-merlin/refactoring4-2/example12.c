#ifdef TC35815_USE_PACKEDBUFFER
while (lp->fbl_curid != id)
#else
			while (lp->fbl_count < RX_BUF_NUM)
#endif
			{
#ifdef TC35815_USE_PACKEDBUFFER
				unsigned char curid = lp->fbl_curid;
#else
				unsigned char curid =
					(id + 1 + lp->fbl_count) % RX_BUF_NUM;
#endif
				struct BDesc *bd = &lp->fbl_ptr->bd[curid];
#ifdef DEBUG
				bdctl = le32_to_cpu(bd->BDCtl);
				if (bdctl & BD_CownsBD) {
					printk("%s: Freeing invalid BD.\n",
					       dev->name);
					panic_queues(dev);
				}
#endif
				/* pass BD to controler */
#ifndef TC35815_USE_PACKEDBUFFER
				if (!lp->rx_skbs[curid].skb) {
					lp->rx_skbs[curid].skb =
						alloc_rxbuf_skb(dev,
								lp->pci_dev,
								&lp->rx_skbs[curid].skb_dma);
					if (!lp->rx_skbs[curid].skb)
						break; /* try on next reception */
					bd->BuffData = cpu_to_le32(lp->rx_skbs[curid].skb_dma);
				}
#endif /* TC35815_USE_PACKEDBUFFER */
				/* Note: BDLength was modified by chip. */
				bd->BDCtl = cpu_to_le32(BD_CownsBD |
							(curid << BD_RxBDID_SHIFT) |
							RX_BUF_SIZE);
#ifdef TC35815_USE_PACKEDBUFFER
				lp->fbl_curid = (curid + 1) % RX_BUF_NUM;
				if (netif_msg_rx_status(lp)) {
					printk("%s: Entering new FBD %d\n",
					       dev->name, lp->fbl_curid);
					dump_frfd(lp->fbl_ptr);
				}
#else
				lp->fbl_count++;
#endif
				buf_free_count++;
			}
