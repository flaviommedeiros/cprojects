#ifdef BCMSDIOH_TXGLOM
if (bus->glom_enable) {
				bus->tx_seq = (bus->tx_seq + bus->glom_cnt) % SDPCM_SEQUENCE_WRAP;
			} else
#endif
			{
			bus->tx_seq = (bus->tx_seq + 1) % SDPCM_SEQUENCE_WRAP;
		}
