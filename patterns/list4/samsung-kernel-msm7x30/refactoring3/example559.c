switch (cmd) {
#ifdef CONFIG_FB_MSM_OVERLAY
	case MSMFB_OVERLAY_GET:
		ret = msmfb_overlay_get(info, argp);
		break;
	case MSMFB_OVERLAY_SET:
		ret = msmfb_overlay_set(info, argp);
		break;
	case MSMFB_OVERLAY_UNSET:
		ret = msmfb_overlay_unset(info, argp);
		break;
	case MSMFB_OVERLAY_PLAY:
		ret = msmfb_overlay_play(info, argp);
		break;
	case MSMFB_OVERLAY_PLAY_ENABLE:
		ret = msmfb_overlay_play_enable(info, argp);
		break;
	case MSMFB_OVERLAY_PLAY_WAIT:
		ret = msmfb_overlay_play_wait(info, argp);
		break;
	case MSMFB_OVERLAY_BLT:
		ret = msmfb_overlay_blt(info, argp);
		break;
	case MSMFB_OVERLAY_3D:
		ret = msmfb_overlay_3d_sbys(info, argp);
		break;
	case MSMFB_MIXER_INFO:
		ret = msmfb_mixer_info(info, argp);
		break;
	case MSMFB_WRITEBACK_INIT:
		ret = msmfb_overlay_ioctl_writeback_init(info);
		break;
	case MSMFB_WRITEBACK_START:
		ret = msmfb_overlay_ioctl_writeback_start(
				info);
		break;
	case MSMFB_WRITEBACK_STOP:
		ret = msmfb_overlay_ioctl_writeback_stop(
				info);
		break;
	case MSMFB_WRITEBACK_QUEUE_BUFFER:
		ret = msmfb_overlay_ioctl_writeback_queue_buffer(
				info, argp);
		break;
	case MSMFB_WRITEBACK_DEQUEUE_BUFFER:
		ret = msmfb_overlay_ioctl_writeback_dequeue_buffer(
				info, argp);
		break;
	case MSMFB_WRITEBACK_TERMINATE:
		ret = msmfb_overlay_ioctl_writeback_terminate(info);
		break;
	case MSMFB_WRITEBACK_SET_MIRRORING_HINT:
		ret = msmfb_overlay_ioctl_writeback_set_mirr_hint(
				info, argp);
		break;
#endif
	case MSMFB_VSYNC_CTRL:
	case MSMFB_OVERLAY_VSYNC_CTRL:
		down(&msm_fb_ioctl_ppp_sem);
		if (mdp_rev >= MDP_REV_40)
			ret = msmfb_overlay_vsync_ctrl(info, argp);
		else
			ret = msmfb_vsync_ctrl(info, argp);
		up(&msm_fb_ioctl_ppp_sem);
		break;
	case MSMFB_BLIT:
		down(&msm_fb_ioctl_ppp_sem);
		ret = msmfb_blit(info, argp);
		up(&msm_fb_ioctl_ppp_sem);

		break;

	/* Ioctl for setting ccs matrix from user space */
	case MSMFB_SET_CCS_MATRIX:
#ifndef CONFIG_FB_MSM_MDP40
		ret = copy_from_user(&ccs_matrix, argp, sizeof(ccs_matrix));
		if (ret) {
			printk(KERN_ERR
				"%s:MSMFB_SET_CCS_MATRIX ioctl failed \n",
				__func__);
			return ret;
		}

		down(&msm_fb_ioctl_ppp_sem);
		if (ccs_matrix.direction == MDP_CCS_RGB2YUV)
			mdp_ccs_rgb2yuv = ccs_matrix;
		else
			mdp_ccs_yuv2rgb = ccs_matrix;

		msmfb_set_color_conv(&ccs_matrix) ;
		up(&msm_fb_ioctl_ppp_sem);
#else
		ret = copy_from_user(&csc_matrix, argp, sizeof(csc_matrix));
		if (ret) {
			pr_err("%s:MSMFB_SET_CSC_MATRIX ioctl failed\n",
				__func__);
			return ret;
		}
		down(&msm_fb_ioctl_ppp_sem);
		msmfb_set_color_conv(&csc_matrix);
		up(&msm_fb_ioctl_ppp_sem);

#endif

		break;

	/* Ioctl for getting ccs matrix to user space */
	case MSMFB_GET_CCS_MATRIX:
#ifndef CONFIG_FB_MSM_MDP40
		ret = copy_from_user(&ccs_matrix, argp, sizeof(ccs_matrix)) ;
		if (ret) {
			printk(KERN_ERR
				"%s:MSMFB_GET_CCS_MATRIX ioctl failed \n",
				 __func__);
			return ret;
		}

		down(&msm_fb_ioctl_ppp_sem);
		if (ccs_matrix.direction == MDP_CCS_RGB2YUV)
			ccs_matrix = mdp_ccs_rgb2yuv;
		 else
			ccs_matrix =  mdp_ccs_yuv2rgb;

		ret = copy_to_user(argp, &ccs_matrix, sizeof(ccs_matrix));

		if (ret)	{
			printk(KERN_ERR
				"%s:MSMFB_GET_CCS_MATRIX ioctl failed \n",
				 __func__);
			return ret ;
		}
		up(&msm_fb_ioctl_ppp_sem);
#else
		ret = -EINVAL;
#endif

		break;

	case MSMFB_GRP_DISP:
#ifdef CONFIG_FB_MSM_MDP22
		{
			unsigned long grp_id;

			ret = copy_from_user(&grp_id, argp, sizeof(grp_id));
			if (ret)
				return ret;

			mdp_pipe_ctrl(MDP_CMD_BLOCK, MDP_BLOCK_POWER_ON, FALSE);
			writel(grp_id, MDP_FULL_BYPASS_WORD43);
			mdp_pipe_ctrl(MDP_CMD_BLOCK, MDP_BLOCK_POWER_OFF,
				      FALSE);
			break;
		}
#else
		return -EFAULT;
#endif
	case MSMFB_SUSPEND_SW_REFRESHER:
		if (!mfd->panel_power_on)
			return -EPERM;

		mfd->sw_refreshing_enable = FALSE;
		ret = msm_fb_stop_sw_refresher(mfd);
		break;

	case MSMFB_RESUME_SW_REFRESHER:
		if (!mfd->panel_power_on)
			return -EPERM;

		mfd->sw_refreshing_enable = TRUE;
		ret = msm_fb_resume_sw_refresher(mfd);
		break;

	case MSMFB_CURSOR:
		ret = copy_from_user(&cursor, argp, sizeof(cursor));
		if (ret)
			return ret;

		ret = msm_fb_cursor(info, &cursor);
		break;

	case MSMFB_SET_LUT:
		ret = copy_from_user(&cmap, argp, sizeof(cmap));
		if (ret)
			return ret;

		mutex_lock(&msm_fb_ioctl_lut_sem);
		ret = msm_fb_set_lut(&cmap, info);
		mutex_unlock(&msm_fb_ioctl_lut_sem);
		break;

	case MSMFB_HISTOGRAM:
		if (!mfd->panel_power_on)
			return -EPERM;

		if (!mfd->do_histogram)
			return -ENODEV;

		ret = copy_from_user(&hist, argp, sizeof(hist));
		if (ret)
			return ret;

		ret = mfd->do_histogram(info, &hist);
		break;

	case MSMFB_HISTOGRAM_START:
		if (!mfd->panel_power_on)
			return -EPERM;

		if (!mfd->start_histogram)
			return -ENODEV;

		ret = copy_from_user(&hist_req, argp, sizeof(hist_req));
		if (ret)
			return ret;

		ret = msmfb_validate_start_req(&hist_req);
		if (ret)
			return ret;

		ret = mfd->start_histogram(&hist_req);
		break;

	case MSMFB_HISTOGRAM_STOP:
		if (!mfd->stop_histogram)
			return -ENODEV;

		ret = copy_from_user(&block, argp, sizeof(int));
		if (ret)
			return ret;

		ret = mfd->stop_histogram(info, block);
		break;


	case MSMFB_GET_PAGE_PROTECTION:
		fb_page_protection.page_protection
			= mfd->mdp_fb_page_protection;
		ret = copy_to_user(argp, &fb_page_protection,
				sizeof(fb_page_protection));
		if (ret)
				return ret;
		break;

	case MSMFB_NOTIFY_UPDATE:
		ret = msmfb_notify_update(info, argp);
		break;

	case MSMFB_SET_PAGE_PROTECTION:
#if defined CONFIG_ARCH_QSD8X50 || defined CONFIG_ARCH_MSM8X60
		ret = copy_from_user(&fb_page_protection, argp,
				sizeof(fb_page_protection));
		if (ret)
				return ret;

		/* Validate the proposed page protection settings. */
		switch (fb_page_protection.page_protection)	{
		case MDP_FB_PAGE_PROTECTION_NONCACHED:
		case MDP_FB_PAGE_PROTECTION_WRITECOMBINE:
		case MDP_FB_PAGE_PROTECTION_WRITETHROUGHCACHE:
		/* Write-back cache (read allocate)  */
		case MDP_FB_PAGE_PROTECTION_WRITEBACKCACHE:
		/* Write-back cache (write allocate) */
		case MDP_FB_PAGE_PROTECTION_WRITEBACKWACACHE:
			mfd->mdp_fb_page_protection =
				fb_page_protection.page_protection;
			break;
		default:
			ret = -EINVAL;
			break;
		}
#else
		/*
		 * Don't allow caching until 7k DMA cache operations are
		 * available.
		 */
		ret = -EINVAL;
#endif
		break;

	case MSMFB_MDP_PP:
		ret = copy_from_user(&mdp_pp, argp, sizeof(mdp_pp));
		if (ret)
			return ret;

		ret = msmfb_handle_pp_ioctl(mfd, &mdp_pp);
		if (ret == 1)
			ret = copy_to_user(argp, &mdp_pp, sizeof(mdp_pp));
		break;
	case MSMFB_BUFFER_SYNC:
		ret = copy_from_user(&buf_sync, argp, sizeof(buf_sync));
		if (ret)
			return ret;

		ret = msmfb_handle_buf_sync_ioctl(mfd, &buf_sync);

		if (!ret)
			ret = copy_to_user(argp, &buf_sync, sizeof(buf_sync));
		break;

	case MSMFB_DISPLAY_COMMIT:
		ret = msmfb_display_commit(info, argp);
		break;

	case MSMFB_METADATA_GET:
		ret = copy_from_user(&mdp_metadata, argp, sizeof(mdp_metadata));
		if (ret)
			return ret;
		ret = msmfb_get_metadata(mfd, &mdp_metadata);
		if (!ret)
			ret = copy_to_user(argp, &mdp_metadata,
				sizeof(mdp_metadata));

		break;

	default:
		MSM_FB_INFO("MDP: unknown ioctl (cmd=%x) received!\n", cmd);
		ret = -EINVAL;
		break;
	}
