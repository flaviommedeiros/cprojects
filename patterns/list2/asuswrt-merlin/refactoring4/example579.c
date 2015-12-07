#ifdef SndEvt_ToAPI
if((((PSCmdRequest)rq)->wCmdCode !=WLAN_CMD_SET_EVT) &&
		       !(pDevice->flags & DEVICE_FLAGS_OPENED))
	      #else
		if (!(pDevice->flags & DEVICE_FLAGS_OPENED) &&
		       (((PSCmdRequest)rq)->wCmdCode !=WLAN_CMD_SET_WPA))
	      #endif
		{
		    rc = -EFAULT;
		    break;
		} else {
		    rc = 0;
		}
