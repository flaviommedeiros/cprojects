if (
#ifdef USE_FBR0
	    (ring_index == 0 && buff_index < rx_local->fbr[1]->num_entries) ||
#endif
	    (ring_index == 1 && buff_index < rx_local->fbr[0]->num_entries)) {
		spin_lock_irqsave(&adapter->fbr_lock, flags);

		if (ring_index == 1) {
			struct fbr_desc *next = (struct fbr_desc *)
					(rx_local->fbr[0]->ring_virtaddr) +
					INDEX10(rx_local->fbr[0]->local_full);

			/* Handle the Free Buffer Ring advancement here. Write
			 * the PA / Buffer Index for the returned buffer into
			 * the oldest (next to be freed)FBR entry
			 */
			next->addr_hi = rx_local->fbr[0]->bus_high[buff_index];
			next->addr_lo = rx_local->fbr[0]->bus_low[buff_index];
			next->word2 = buff_index;

			writel(bump_free_buff_ring(
					&rx_local->fbr[0]->local_full,
					rx_local->fbr[0]->num_entries - 1),
					&rx_dma->fbr1_full_offset);
		}
#ifdef USE_FBR0
		else {
			struct fbr_desc *next = (struct fbr_desc *)
				rx_local->fbr[1]->ring_virtaddr +
				    INDEX10(rx_local->fbr[1]->local_full);

			/* Handle the Free Buffer Ring advancement here. Write
			 * the PA / Buffer Index for the returned buffer into
			 * the oldest (next to be freed) FBR entry
			 */
			next->addr_hi = rx_local->fbr[1]->bus_high[buff_index];
			next->addr_lo = rx_local->fbr[1]->bus_low[buff_index];
			next->word2 = buff_index;

			writel(bump_free_buff_ring(
					&rx_local->fbr[1]->local_full,
					rx_local->fbr[1]->num_entries - 1),
			       &rx_dma->fbr0_full_offset);
		}
#endif
		spin_unlock_irqrestore(&adapter->fbr_lock, flags);
	} else {
		dev_err(&adapter->pdev->dev,
			  "%s illegal Buffer Index returned\n", __func__);
	}
