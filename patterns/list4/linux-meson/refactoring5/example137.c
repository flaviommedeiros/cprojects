#ifdef CONFIG_MP_INCLUDED
if (padapter->registrypriv.mp_mode == 1 || padapter->mppriv.bRTWSmbCfg ==_TRUE)
	{
		mp_recv_frame(padapter,rframe);
		ret = _FAIL;
		goto exit;
        }
	else
#endif
	{
	//check the frame crtl field and decache
	ret = validate_recv_frame(padapter, rframe);
	if (ret != _SUCCESS)
	{
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("recv_func: validate_recv_frame fail! drop pkt\n"));
		rtw_free_recvframe(rframe, pfree_recv_queue);//free this recv_frame
		goto exit;
	}
	}
