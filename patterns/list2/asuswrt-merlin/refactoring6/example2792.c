if((priv->rfa_txpowertrackingindex < 36)
#ifdef RTL8190P
					&&(priv->rfc_txpowertrackingindex < 36)
#endif
					)
				{
					priv->rfa_txpowertrackingindex++;
					priv->rfa_txpowertrackingindex_real++;
					rtl8192_setBBreg(dev, rOFDM0_XATxIQImbalance, bMaskDWord, priv->txbbgain_table[priv->rfa_txpowertrackingindex_real].txbbgain_value);

#ifdef RTL8190P
					priv->rfc_txpowertrackingindex++;
					priv->rfc_txpowertrackingindex_real++;
					rtl8192_setBBreg(dev, rOFDM0_XCTxIQImbalance, bMaskDWord, priv->txbbgain_table[priv->rfc_txpowertrackingindex_real].txbbgain_value);
#endif
				}
