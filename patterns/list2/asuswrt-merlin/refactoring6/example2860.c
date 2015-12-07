if (
#ifdef USE_FBR0
	    (ri == 0 && bi < rx_local->Fbr0NumEntries) ||
#endif
	    (ri == 1 && bi < rx_local->Fbr1NumEntries)) {
		spin_lock_irqsave(&etdev->FbrLock, flags);

		if (ri == 1) {
			struct fbr_desc *next =
			    (struct fbr_desc *) (rx_local->pFbr1RingVa) +
					 INDEX10(rx_local->local_Fbr1_full);

			/* Handle the Free Buffer Ring advancement here. Write
			 * the PA / Buffer Index for the returned buffer into
			 * the oldest (next to be freed)FBR entry
			 */
			next->addr_hi = rx_local->fbr[1]->bus_high[bi];
			next->addr_lo = rx_local->fbr[1]->bus_low[bi];
			next->word2 = bi;

			writel(bump_fbr(&rx_local->local_Fbr1_full,
				rx_local->Fbr1NumEntries - 1),
				&rx_dma->fbr1_full_offset);
		}
#ifdef USE_FBR0
		else {
			struct fbr_desc *next = (struct fbr_desc *)
				rx_local->pFbr0RingVa +
					INDEX10(rx_local->local_Fbr0_full);

			/* Handle the Free Buffer Ring advancement here. Write
			 * the PA / Buffer Index for the returned buffer into
			 * the oldest (next to be freed) FBR entry
			 */
			next->addr_hi = rx_local->fbr[0]->bus_high[bi];
			next->addr_lo = rx_local->fbr[0]->bus_low[bi];
			next->word2 = bi;

			writel(bump_fbr(&rx_local->local_Fbr0_full,
					rx_local->Fbr0NumEntries - 1),
			       &rx_dma->fbr0_full_offset);
		}
#endif
		spin_unlock_irqrestore(&etdev->FbrLock, flags);
	} else {
		dev_err(&etdev->pdev->dev,
			  "NICReturnRFD illegal Buffer Index returned\n");
	}
