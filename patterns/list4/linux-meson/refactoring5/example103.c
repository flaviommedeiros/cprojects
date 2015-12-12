#ifdef CONFIG_CONCURRENT_MODE
if (rtw_buddy_adapter_up(padapter))
					{
						if (pre_recv_entry(precvframe, precvbuf, ptr) != _SUCCESS) {
							RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,
								("recvbuf2recvframe: recv_entry(precvframe) != _SUCCESS\n"));
						}
					}
					else
#endif
					{
						if (pattrib->physt)
							rx_query_phy_status(precvframe, ptr);

						if (rtw_recv_entry(precvframe) != _SUCCESS)
						{
							RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("rtl8723bs_recv_tasklet: rtw_recv_entry(precvframe) != _SUCCESS\n"));
						}
					}
