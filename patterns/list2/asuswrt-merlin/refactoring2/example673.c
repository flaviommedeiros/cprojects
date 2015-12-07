#if defined(D11_SPLIT_RX_FD)
if (!di->sep_rxhdr)
#endif
		{
			/* reset flags for each descriptor */
			flags = 0;
			if (DMA64_ENAB(di) && DMA64_MODE(di)) {
				if (rxout == (di->nrxd - 1))
					flags = D64_CTRL1_EOT;
				dma64_dd_upd(di, di->rxd64, pa, rxout, &flags, di->rxbufsize);
			} else if (DMA32_ENAB(di)) {
				if (rxout == (di->nrxd - 1))
					flags = CTRL_EOT;

				ASSERT(PHYSADDRHI(pa) == 0);
				dma32_dd_upd(di, di->rxd32, pa, rxout, &flags, di->rxbufsize);
			} else
				ASSERT(0);
			rxout = NEXTRXD(rxout);

		}
#if defined(D11_SPLIT_RX_FD)
		else {
			/* TCM Descriptor */
			flags = 0;
			pktlen = PKTLEN(di->osh, p);
			if (rxout == (di->nrxd - 1))
				flags = D64_CTRL1_EOT;

			/* MAR SOF, so start frame will go to this descriptor */
			flags |= D64_CTRL1_SOF;
			dma64_dd_upd(di, di->rxd64, pa, rxout, &flags, pktlen);
			rxout = NEXTRXD(rxout);		/* update rxout */

			/* Now program host descriptor */
			/* Mark up this descriptor that its a host descriptor */
			/* store 0x80000000 so that dma_rx need'nt process this descriptor */
			di->rxp[rxout] = (void*)PCI64ADDR_HIGH;
			flags = 0;	/* Reset the flags */

			if (rxout == (di->nrxd - 1))
				flags = D64_CTRL1_EOT;

			/* Extract out host length */
			pktlen = PKTFRAGLEN(di->osh, p, 1);

			/* Extract out host addresses */
			pa64.loaddr = PKTFRAGDATA_LO(di->osh, p, 1);
			pa64.hiaddr = PKTFRAGDATA_HI(di->osh, p, 1);

			/* load the descriptor */
			dma64_dd_upd_64(di, di->rxd64, pa64, rxout, &flags, pktlen);
			rxout = NEXTRXD(rxout);	/* update rxout */
		}
