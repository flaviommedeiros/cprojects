switch (cmd) {
	case MFB_SET_PIXFMT_OLD:
		dev_warn(info->dev,
			 "MFB_SET_PIXFMT value of 0x%08x is deprecated.\n",
			 MFB_SET_PIXFMT_OLD);
	case MFB_SET_PIXFMT:
		if (copy_from_user(&pix_fmt, buf, sizeof(pix_fmt)))
			return -EFAULT;
		ad->pix_fmt = pix_fmt;
		break;
	case MFB_GET_PIXFMT_OLD:
		dev_warn(info->dev,
			 "MFB_GET_PIXFMT value of 0x%08x is deprecated.\n",
			 MFB_GET_PIXFMT_OLD);
	case MFB_GET_PIXFMT:
		pix_fmt = ad->pix_fmt;
		if (copy_to_user(buf, &pix_fmt, sizeof(pix_fmt)))
			return -EFAULT;
		break;
	case MFB_SET_AOID:
		if (copy_from_user(&aoi_d, buf, sizeof(aoi_d)))
			return -EFAULT;
		mfbi->x_aoi_d = aoi_d.x_aoi_d;
		mfbi->y_aoi_d = aoi_d.y_aoi_d;
		fsl_diu_check_var(&info->var, info);
		fsl_diu_set_aoi(info);
		break;
	case MFB_GET_AOID:
		aoi_d.x_aoi_d = mfbi->x_aoi_d;
		aoi_d.y_aoi_d = mfbi->y_aoi_d;
		if (copy_to_user(buf, &aoi_d, sizeof(aoi_d)))
			return -EFAULT;
		break;
	case MFB_GET_ALPHA:
		global_alpha = mfbi->g_alpha;
		if (copy_to_user(buf, &global_alpha, sizeof(global_alpha)))
			return -EFAULT;
		break;
	case MFB_SET_ALPHA:
		/* set panel information */
		if (copy_from_user(&global_alpha, buf, sizeof(global_alpha)))
			return -EFAULT;
		ad->src_size_g_alpha = (ad->src_size_g_alpha & (~0xff)) |
							(global_alpha & 0xff);
		mfbi->g_alpha = global_alpha;
		break;
	case MFB_SET_CHROMA_KEY:
		/* set panel winformation */
		if (copy_from_user(&ck, buf, sizeof(ck)))
			return -EFAULT;

		if (ck.enable &&
		   (ck.red_max < ck.red_min ||
		    ck.green_max < ck.green_min ||
		    ck.blue_max < ck.blue_min))
			return -EINVAL;

		if (!ck.enable) {
			ad->ckmax_r = 0;
			ad->ckmax_g = 0;
			ad->ckmax_b = 0;
			ad->ckmin_r = 255;
			ad->ckmin_g = 255;
			ad->ckmin_b = 255;
		} else {
			ad->ckmax_r = ck.red_max;
			ad->ckmax_g = ck.green_max;
			ad->ckmax_b = ck.blue_max;
			ad->ckmin_r = ck.red_min;
			ad->ckmin_g = ck.green_min;
			ad->ckmin_b = ck.blue_min;
		}
		break;
#ifdef CONFIG_PPC_MPC512x
	case MFB_SET_GAMMA: {
		struct fsl_diu_data *data = mfbi->parent;

		if (copy_from_user(data->gamma, buf, sizeof(data->gamma)))
			return -EFAULT;
		setbits32(&data->diu_reg->gamma, 0); /* Force table reload */
		break;
	}
	case MFB_GET_GAMMA: {
		struct fsl_diu_data *data = mfbi->parent;

		if (copy_to_user(buf, data->gamma, sizeof(data->gamma)))
			return -EFAULT;
		break;
	}
#endif
	default:
		dev_err(info->dev, "unknown ioctl command (0x%08X)\n", cmd);
		return -ENOIOCTLCMD;
	}
