switch (cmd) {
	case MEMGETREGIONCOUNT:
		if (copy_to_user(argp, &(mtd->numeraseregions), sizeof(int)))
			return -EFAULT;
		break;

	case MEMGETREGIONINFO:
	{
		uint32_t ur_idx;
		struct mtd_erase_region_info *kr;
		struct region_info_user __user *ur = argp;

		if (get_user(ur_idx, &(ur->regionindex)))
			return -EFAULT;

		if (ur_idx >= mtd->numeraseregions)
			return -EINVAL;

		kr = &(mtd->eraseregions[ur_idx]);

		if (put_user(kr->offset, &(ur->offset))
		    || put_user(kr->erasesize, &(ur->erasesize))
		    || put_user(kr->numblocks, &(ur->numblocks)))
			return -EFAULT;

		break;
	}

	case MEMGETINFO:
		memset(&info, 0, sizeof(info));
		info.type	= mtd->type;
		info.flags	= mtd->flags;
		info.size	= mtd->size;
		info.erasesize	= mtd->erasesize;
		info.writesize	= mtd->writesize;
		info.oobsize	= mtd->oobsize;
		/* The below field is obsolete */
		info.padding	= 0;
		if (copy_to_user(argp, &info, sizeof(struct mtd_info_user)))
			return -EFAULT;
		break;

	case MEMERASE:
	case MEMERASE64:
	{
		struct erase_info *erase;

		if(!(file->f_mode & FMODE_WRITE))
			return -EPERM;

		erase=kzalloc(sizeof(struct erase_info),GFP_KERNEL);
		if (!erase)
			ret = -ENOMEM;
		else {
			wait_queue_head_t waitq;
			DECLARE_WAITQUEUE(wait, current);

			init_waitqueue_head(&waitq);

			if (cmd == MEMERASE64) {
				struct erase_info_user64 einfo64;

				if (copy_from_user(&einfo64, argp,
					    sizeof(struct erase_info_user64))) {
					kfree(erase);
					return -EFAULT;
				}
				erase->addr = einfo64.start;
				erase->len = einfo64.length;
			} else {
				struct erase_info_user einfo32;

				if (copy_from_user(&einfo32, argp,
					    sizeof(struct erase_info_user))) {
					kfree(erase);
					return -EFAULT;
				}
				erase->addr = einfo32.start;
				erase->len = einfo32.length;
			}
			erase->mtd = mtd;
			erase->callback = mtdchar_erase_callback;
			erase->priv = (unsigned long)&waitq;

			/*
			  FIXME: Allow INTERRUPTIBLE. Which means
			  not having the wait_queue head on the stack.

			  If the wq_head is on the stack, and we
			  leave because we got interrupted, then the
			  wq_head is no longer there when the
			  callback routine tries to wake us up.
			*/
			ret = mtd_erase(mtd, erase);
			if (!ret) {
				set_current_state(TASK_UNINTERRUPTIBLE);
				add_wait_queue(&waitq, &wait);
				if (erase->state != MTD_ERASE_DONE &&
				    erase->state != MTD_ERASE_FAILED)
					schedule();
				remove_wait_queue(&waitq, &wait);
				set_current_state(TASK_RUNNING);

				ret = (erase->state == MTD_ERASE_FAILED)?-EIO:0;
			}
			kfree(erase);
		}
		break;
	}

	case MEMWRITEOOB:
	{
		struct mtd_oob_buf buf;
		struct mtd_oob_buf __user *buf_user = argp;

		/* NOTE: writes return length to buf_user->length */
		if (copy_from_user(&buf, argp, sizeof(buf)))
			ret = -EFAULT;
		else
			ret = mtdchar_writeoob(file, mtd, buf.start, buf.length,
				buf.ptr, &buf_user->length);
		break;
	}

	case MEMREADOOB:
	{
		struct mtd_oob_buf buf;
		struct mtd_oob_buf __user *buf_user = argp;

		/* NOTE: writes return length to buf_user->start */
		if (copy_from_user(&buf, argp, sizeof(buf)))
			ret = -EFAULT;
		else
			ret = mtdchar_readoob(file, mtd, buf.start, buf.length,
				buf.ptr, &buf_user->start);
		break;
	}

	case MEMWRITEOOB64:
	{
		struct mtd_oob_buf64 buf;
		struct mtd_oob_buf64 __user *buf_user = argp;

		if (copy_from_user(&buf, argp, sizeof(buf)))
			ret = -EFAULT;
		else
			ret = mtdchar_writeoob(file, mtd, buf.start, buf.length,
				(void __user *)(uintptr_t)buf.usr_ptr,
				&buf_user->length);
		break;
	}

	case MEMREADOOB64:
	{
		struct mtd_oob_buf64 buf;
		struct mtd_oob_buf64 __user *buf_user = argp;

		if (copy_from_user(&buf, argp, sizeof(buf)))
			ret = -EFAULT;
		else
			ret = mtdchar_readoob(file, mtd, buf.start, buf.length,
				(void __user *)(uintptr_t)buf.usr_ptr,
				&buf_user->length);
		break;
	}

	case MEMWRITE:
	{
		ret = mtdchar_write_ioctl(mtd,
		      (struct mtd_write_req __user *)arg);
		break;
	}

	case MEMLOCK:
	{
		struct erase_info_user einfo;

		if (copy_from_user(&einfo, argp, sizeof(einfo)))
			return -EFAULT;

		ret = mtd_lock(mtd, einfo.start, einfo.length);
		break;
	}

	case MEMUNLOCK:
	{
		struct erase_info_user einfo;

		if (copy_from_user(&einfo, argp, sizeof(einfo)))
			return -EFAULT;

		ret = mtd_unlock(mtd, einfo.start, einfo.length);
		break;
	}

	case MEMISLOCKED:
	{
		struct erase_info_user einfo;

		if (copy_from_user(&einfo, argp, sizeof(einfo)))
			return -EFAULT;

		ret = mtd_is_locked(mtd, einfo.start, einfo.length);
		break;
	}

	/* Legacy interface */
	case MEMGETOOBSEL:
	{
		struct nand_oobinfo oi;

		if (!mtd->ecclayout)
			return -EOPNOTSUPP;
		if (mtd->ecclayout->eccbytes > ARRAY_SIZE(oi.eccpos))
			return -EINVAL;

		oi.useecc = MTD_NANDECC_AUTOPLACE;
		memcpy(&oi.eccpos, mtd->ecclayout->eccpos, sizeof(oi.eccpos));
		memcpy(&oi.oobfree, mtd->ecclayout->oobfree,
		       sizeof(oi.oobfree));
		oi.eccbytes = mtd->ecclayout->eccbytes;

		if (copy_to_user(argp, &oi, sizeof(struct nand_oobinfo)))
			return -EFAULT;
		break;
	}

	case MEMGETBADBLOCK:
	{
		loff_t offs;

		if (copy_from_user(&offs, argp, sizeof(loff_t)))
			return -EFAULT;
		return mtd_block_isbad(mtd, offs);
		break;
	}

	case MEMSETBADBLOCK:
	{
		loff_t offs;

		if (copy_from_user(&offs, argp, sizeof(loff_t)))
			return -EFAULT;
		return mtd_block_markbad(mtd, offs);
		break;
	}

#ifdef CONFIG_HAVE_MTD_OTP
	case OTPSELECT:
	{
		int mode;
		if (copy_from_user(&mode, argp, sizeof(int)))
			return -EFAULT;

		mfi->mode = MTD_FILE_MODE_NORMAL;

		ret = otp_select_filemode(mfi, mode);

		file->f_pos = 0;
		break;
	}

	case OTPGETREGIONCOUNT:
	case OTPGETREGIONINFO:
	{
		struct otp_info *buf = kmalloc(4096, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;
		switch (mfi->mode) {
		case MTD_FILE_MODE_OTP_FACTORY:
			ret = mtd_get_fact_prot_info(mtd, buf, 4096);
			break;
		case MTD_FILE_MODE_OTP_USER:
			ret = mtd_get_user_prot_info(mtd, buf, 4096);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		if (ret >= 0) {
			if (cmd == OTPGETREGIONCOUNT) {
				int nbr = ret / sizeof(struct otp_info);
				ret = copy_to_user(argp, &nbr, sizeof(int));
			} else
				ret = copy_to_user(argp, buf, ret);
			if (ret)
				ret = -EFAULT;
		}
		kfree(buf);
		break;
	}

	case OTPLOCK:
	{
		struct otp_info oinfo;

		if (mfi->mode != MTD_FILE_MODE_OTP_USER)
			return -EINVAL;
		if (copy_from_user(&oinfo, argp, sizeof(oinfo)))
			return -EFAULT;
		ret = mtd_lock_user_prot_reg(mtd, oinfo.start, oinfo.length);
		break;
	}
#endif

	/* This ioctl is being deprecated - it truncates the ECC layout */
	case ECCGETLAYOUT:
	{
		struct nand_ecclayout_user *usrlay;

		if (!mtd->ecclayout)
			return -EOPNOTSUPP;

		usrlay = kmalloc(sizeof(*usrlay), GFP_KERNEL);
		if (!usrlay)
			return -ENOMEM;

		shrink_ecclayout(mtd->ecclayout, usrlay);

		if (copy_to_user(argp, usrlay, sizeof(*usrlay)))
			ret = -EFAULT;
		kfree(usrlay);
		break;
	}

	case ECCGETSTATS:
	{
#ifdef CONFIG_MTD_LAZYECCSTATS
		part_fill_badblockstats(mtd);
#endif
		if (copy_to_user(argp, &mtd->ecc_stats,
				 sizeof(struct mtd_ecc_stats)))
			return -EFAULT;
		break;
	}

	case MTDFILEMODE:
	{
		mfi->mode = 0;

		switch(arg) {
		case MTD_FILE_MODE_OTP_FACTORY:
		case MTD_FILE_MODE_OTP_USER:
			ret = otp_select_filemode(mfi, arg);
			break;

		case MTD_FILE_MODE_RAW:
			if (!mtd_has_oob(mtd))
				return -EOPNOTSUPP;
			mfi->mode = arg;

		case MTD_FILE_MODE_NORMAL:
			break;
		default:
			ret = -EINVAL;
		}
		file->f_pos = 0;
		break;
	}

	case BLKPG:
	{
		ret = mtdchar_blkpg_ioctl(mtd,
		      (struct blkpg_ioctl_arg __user *)arg);
		break;
	}

	case BLKRRPART:
	{
		/* No reread partition feature. Just return ok */
		ret = 0;
		break;
	}

	default:
		ret = -ENOTTY;
	}
