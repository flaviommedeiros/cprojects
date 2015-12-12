#ifdef CONFIG_P2P
if(rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE))
#endif //CONFIG_P2P
		{
			ret = -EBUSY;
			printk("Android hasn't attached yet!\n");
			goto exit;
		}
