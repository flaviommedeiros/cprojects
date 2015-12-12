#ifdef CONFIG_SDIO_HCI
if (GET_PWR_CFG_BASE(PwrCfgCmd) == PWR_BASEADDR_SDIO)
							value = SdioLocalCmd52Read1Byte(padapter, offset);
						else
#endif
							value = rtw_read8(padapter, offset);
