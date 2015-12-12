#ifdef CONFIG_BT_COEXIST
if (rtw_btcoex_IsBtControlLps(padapter) == _TRUE)
		{
			PowerState = rtw_btcoex_RpwmVal(padapter);
			byte5 = rtw_btcoex_LpsVal(padapter);

			if ((rlbm == 2) && (byte5 & BIT(4)))
			{
				// Keep awake interval to 1 to prevent from
				// decreasing coex performance
				awake_intvl = 2;
				rlbm = 2;
			}
		}
		else
#endif // CONFIG_BT_COEXIST
		{
			PowerState = 0x00;// AllON(0x0C), RFON(0x04), RFOFF(0x00)
			byte5 = 0x40;
		}
