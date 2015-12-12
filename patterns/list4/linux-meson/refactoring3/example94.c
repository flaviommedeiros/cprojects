switch (cmd)
  	{
   		case  FBIOPUT_OSD_SRCKEY_ENABLE:
			ret=copy_from_user(&srckey_enable,argp,sizeof(u32));
			break;
   		case  FBIOPUT_OSD_SRCCOLORKEY:
			ret=copy_from_user(&src_colorkey,argp,sizeof(u32));
			break ;
		case FBIOPUT_OSD_SET_GBL_ALPHA:
			ret=copy_from_user(&gbl_alpha,argp,sizeof(u32));
			break;
		case FBIOPUT_OSD_SCALE_AXIS:
			ret=copy_from_user(&osd_axis, argp, 4 * sizeof(s32));
			break;
		case FBIOPUT_OSD_SYNC_ADD:
			ret=copy_from_user(&sync_request,argp,sizeof(fb_sync_request_t));
			//printk("osd_mai request offset:%d\n", sync_request.offset);
			break;
		case FBIO_WAITFORVSYNC:
		case FBIOGET_OSD_SCALE_AXIS:
		case FBIOPUT_OSD_ORDER:
		case FBIOGET_OSD_ORDER:
		case FBIOGET_OSD_GET_GBL_ALPHA:
		case FBIOPUT_OSD_2X_SCALE:	
		case FBIOPUT_OSD_ENABLE_3D_MODE:
		case FBIOPUT_OSD_FREE_SCALE_ENABLE:
		case FBIOPUT_OSD_FREE_SCALE_MODE:
		case FBIOPUT_OSD_FREE_SCALE_WIDTH:
		case FBIOPUT_OSD_FREE_SCALE_HEIGHT:
		case FBIOGET_OSD_BLOCK_WINDOWS:
		case FBIOGET_OSD_BLOCK_MODE:
		case FBIOGET_OSD_FREE_SCALE_AXIS:
		case FBIOGET_OSD_WINDOW_AXIS:
		case FBIOPUT_OSD_REVERSE:
		case FBIOPUT_OSD_ROTATE_ON:
		case FBIOPUT_OSD_ROTATE_ANGLE:
			break;
		case FBIOPUT_OSD_BLOCK_MODE:
			block_mode = (u32)argp;
			break;
		case FBIOPUT_OSD_BLOCK_WINDOWS:
			ret=copy_from_user(&block_windows, argp, 8 * sizeof(u32));
			break;
		case FBIOPUT_OSD_FREE_SCALE_AXIS:
			ret=copy_from_user(&osd_axis, argp, 4 * sizeof(s32));
			break;
		case FBIOPUT_OSD_WINDOW_AXIS:
			ret=copy_from_user(&osd_dst_axis, argp, 4 * sizeof(s32));
			break;
#ifdef CONFIG_FB_AMLOGIC_UMP
		case GET_UMP_SECURE_ID_BUF2:	/* flow trough */
		{
			secure_id_buf_num = 1;
			if (!disp_get_ump_secure_id)
				request_module("osd_ump");
			if (disp_get_ump_secure_id)
				return disp_get_ump_secure_id(info, fbdev, arg,
							      secure_id_buf_num);
			else
				return -ENOTSUPP;
		}
		break;
		case GET_UMP_SECURE_ID_BUF1:	/* flow trough */
		{
			secure_id_buf_num = 0;
			if (!disp_get_ump_secure_id)
				request_module("osd_ump");
			if (disp_get_ump_secure_id)
				return disp_get_ump_secure_id(info, fbdev, arg,
							      secure_id_buf_num);
			else
				return -ENOTSUPP;
		}
		break;
#endif
		case FBIOPUT_OSD2_CURSOR_DATA:
		{
			if (copy_from_user(&karg, argp, sizeof(unsigned int))) {
				return -EFAULT;
			}
			aml_hwc_addr_t para;
			if (copy_from_user(&para, (void __user *)karg, sizeof(aml_hwc_addr_t))) {
				return -EFAULT;
			}
			ret = osddev_copy_data_tocursor(fbdev, &para);
		}
		break;
		default :
			amlog_mask_level(LOG_MASK_IOCTL,LOG_LEVEL_HIGH,"command not supported\r\n ");
			return -1;
	}
