#ifdef CONFIG_MP_INCLUDED
if (padapter->registrypriv.mp_mode == 1)
				{
					if ((check_fwstate(&padapter->mlmepriv, WIFI_MP_STATE) == _TRUE))//&&(padapter->mppriv.check_mp_pkt == 0))
					{
						if (pattrib->crc_err == 1)
							padapter->mppriv.rx_crcerrpktcount++;
					}
				}
				else
#endif
				{
					DBG_8192C("%s: crc_err=%d icv_err=%d, skip!\n", __FUNCTION__, pattrib->crc_err, pattrib->icv_err);
				}
