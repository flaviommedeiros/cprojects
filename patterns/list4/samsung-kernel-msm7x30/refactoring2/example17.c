#if defined(SOFTAP)
if (ap_fw_loaded == FALSE)
#endif 
		if (!(dhd->op_mode & DHD_FLAG_HOSTAP_MODE)) {
			if ((res = dhd_keep_alive_onoff(dhd)) < 0)
				DHD_ERROR(("%s set keeplive failed %d\n",
				__FUNCTION__, res));
		}
