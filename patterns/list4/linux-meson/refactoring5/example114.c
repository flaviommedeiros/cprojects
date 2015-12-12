#ifdef CONFIG_RTL_92D_SUPPORT
if (GET_CHIP_VER(priv)==VERSION_8192D){
			tx_power_tracking_92D(priv);
		} else 
#endif
		{
#ifdef CONFIG_RTL_92C_SUPPORT			
			tx_power_tracking(priv);
#endif
		}
