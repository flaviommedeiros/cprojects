#ifdef DYNAMIC_BUFFERS
if (pkt_len > SKBUFF_RX_COPYBREAK) {
					struct sk_buff *newskb;

					newskb = dev_alloc_skb(NEW_SKB_SIZE);
					if (newskb){
						rx_in_place = 1;

						my_skb_align(newskb, 128);
						skb = (struct sk_buff *)bp->p_rcv_buff_va[entry];
						dma_unmap_single(bp->bus_dev,
							bp->descr_block_virt->rcv_data[entry].long_1,
							NEW_SKB_SIZE,
							DMA_FROM_DEVICE);
						skb_reserve(skb, RCV_BUFF_K_PADDING);
						bp->p_rcv_buff_va[entry] = (char *)newskb;
						bp->descr_block_virt->rcv_data[entry].long_1 =
							(u32)dma_map_single(bp->bus_dev,
								newskb->data,
								NEW_SKB_SIZE,
								DMA_FROM_DEVICE);
					} else
						skb = NULL;
				} else
#endif
					skb = dev_alloc_skb(pkt_len+3);
