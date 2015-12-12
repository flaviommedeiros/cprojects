#ifdef CONFIG_RTL_8812_SUPPORT
if (GET_CHIP_VER(priv) == VERSION_8812E)
						UpdateHalRAMask8812(priv, pstat, 3);
					else
#endif
#ifdef CONFIG_RTL_88E_SUPPORT
						if (GET_CHIP_VER(priv) == VERSION_8188E) {
#ifdef TXREPORT
							add_RATid(priv, pstat);
#endif
						} else
#endif
						{
#if defined(CONFIG_RTL_92D_SUPPORT) || defined(CONFIG_RTL_92C_SUPPORT)
							add_update_RATid(priv, pstat);
#endif
						}
