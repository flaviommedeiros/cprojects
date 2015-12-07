#ifdef CTFPOOL
if ((PKTISFAST(osh, skb)) && (atomic_read(&skb->users) == 1))
			osl_pktfastfree(osh, skb);
		else {
#else /* CTFPOOL */
		{
#endif /* CTFPOOL */

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
		atomic_dec(&osh->pktalloced);
		skb = nskb;
	}
