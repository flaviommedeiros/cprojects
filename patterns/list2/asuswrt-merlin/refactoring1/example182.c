if (adapter->flags & IXGBE_FLAG_FCOE_ENABLED) {
			txq &= (adapter->ring_feature[RING_F_FCOE].indices - 1);
			txq += adapter->ring_feature[RING_F_FCOE].mask;
			return txq;
#ifdef CONFIG_IXGBE_DCB
		} else if (adapter->flags & IXGBE_FLAG_DCB_ENABLED) {
			txq = adapter->fcoe.up;
			return txq;
#endif
		}
#endif
