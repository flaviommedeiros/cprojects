#ifndef DYNAMIC_BUFFERS
if (! rx_in_place)
#endif
					{
						/* Receive buffer allocated, pass receive packet up */

						skb_copy_to_linear_data(skb,
							       p_buff + RCV_BUFF_K_PADDING,
							       pkt_len + 3);
					}
