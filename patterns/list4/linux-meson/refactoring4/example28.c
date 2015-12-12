#ifdef CONFIG_P2P
if ((pmgntframe = rtw_alloc_bcnxmitframe(pxmitpriv)) == NULL)
#else
	if ((pmgntframe = alloc_mgtxmitframe(pxmitpriv)) == NULL)
#endif
	{
		DBG_871X("%s, alloc mgnt frame fail\n", __FUNCTION__);
		return;
	}
