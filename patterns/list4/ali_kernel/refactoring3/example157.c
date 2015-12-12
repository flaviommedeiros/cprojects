switch (opcode & ~HW_OWNER) {
		case OP_RXSTAT:
			total_packets[port]++;
			total_bytes[port] += length;
			skb = sky2_receive(dev, length, status);
			if (unlikely(!skb)) {
				dev->stats.rx_dropped++;
				break;
			}

			/* This chip reports checksum status differently */
			if (hw->flags & SKY2_HW_NEW_LE) {
				if ((sky2->flags & SKY2_FLAG_RX_CHECKSUM) &&
				    (le->css & (CSS_ISIPV4 | CSS_ISIPV6)) &&
				    (le->css & CSS_TCPUDPCSOK))
					skb->ip_summed = CHECKSUM_UNNECESSARY;
				else
					skb->ip_summed = CHECKSUM_NONE;
			}

			skb->protocol = eth_type_trans(skb, dev);

			sky2_skb_rx(sky2, status, skb);

			/* Stop after net poll weight */
			if (++work_done >= to_do)
				goto exit_loop;
			break;

#ifdef SKY2_VLAN_TAG_USED
		case OP_RXVLAN:
			sky2->rx_tag = length;
			break;

		case OP_RXCHKSVLAN:
			sky2->rx_tag = length;
			/* fall through */
#endif
		case OP_RXCHKS:
			if (!(sky2->flags & SKY2_FLAG_RX_CHECKSUM))
				break;

			/* If this happens then driver assuming wrong format */
			if (unlikely(hw->flags & SKY2_HW_NEW_LE)) {
				if (net_ratelimit())
					printk(KERN_NOTICE "%s: unexpected"
					       " checksum status\n",
					       dev->name);
				break;
			}

			/* Both checksum counters are programmed to start at
			 * the same offset, so unless there is a problem they
			 * should match. This failure is an early indication that
			 * hardware receive checksumming won't work.
			 */
			if (likely(status >> 16 == (status & 0xffff))) {
				skb = sky2->rx_ring[sky2->rx_next].skb;
				skb->ip_summed = CHECKSUM_COMPLETE;
				skb->csum = le16_to_cpu(status);
			} else {
				printk(KERN_NOTICE PFX "%s: hardware receive "
				       "checksum problem (status = %#x)\n",
				       dev->name, status);
				sky2->flags &= ~SKY2_FLAG_RX_CHECKSUM;

				sky2_write32(sky2->hw,
					     Q_ADDR(rxqaddr[port], Q_CSR),
					     BMU_DIS_RX_CHKSUM);
			}
			break;

		case OP_TXINDEXLE:
			/* TX index reports status for both ports */
			sky2_tx_done(hw->dev[0], status & 0xfff);
			if (hw->dev[1])
				sky2_tx_done(hw->dev[1],
				     ((status >> 24) & 0xff)
					     | (u16)(length & 0xf) << 8);
			break;

		default:
			if (net_ratelimit())
				printk(KERN_WARNING PFX
				       "unknown status opcode 0x%x\n", opcode);
		}
