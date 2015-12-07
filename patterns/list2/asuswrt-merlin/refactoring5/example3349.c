#ifdef CTFPOOL
if (PKTISFAST(osh, skb)) {
			if (atomic_read(&skb->users) == 1)
				smp_rmb();
			else if (!atomic_dec_and_test(&skb->users))
				goto next_skb;
			osl_pktfastfree(osh, skb);
		} else
#endif
		{
			if (skb->destructor)
				/* cannot kfree_skb() on hard IRQ (net/core/skbuff.c) if
				 * destructor exists
				 */
				dev_kfree_skb_any(skb);
			else
				/* can free immediately (even in_irq()) if destructor
				 * does not exist
				 */
				dev_kfree_skb(skb);
		}
