#ifdef RTCONFIG_QTN
if (radio == 5)
					temperature = get_qtn_temperature();
				else
#endif
					temperature = get_phy_temperature(radio);
