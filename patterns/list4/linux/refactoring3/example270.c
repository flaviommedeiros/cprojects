switch (cmd) {
	case FSFILT_IOC_GETFLAGS:
	case FSFILT_IOC_SETFLAGS:
		return ll_iocontrol(inode, file, cmd, arg);
	case FSFILT_IOC_GETVERSION_OLD:
	case FSFILT_IOC_GETVERSION:
		return put_user(inode->i_generation, (int *)arg);
	/* We need to special case any other ioctls we want to handle,
	 * to send them to the MDS/OST as appropriate and to properly
	 * network encode the arg field.
	case FSFILT_IOC_SETVERSION_OLD:
	case FSFILT_IOC_SETVERSION:
	*/
	case LL_IOC_GET_MDTIDX: {
		int mdtidx;

		mdtidx = ll_get_mdt_idx(inode);
		if (mdtidx < 0)
			return mdtidx;

		if (put_user((int)mdtidx, (int *)arg))
			return -EFAULT;

		return 0;
	}
	case IOC_MDC_LOOKUP: {
		struct ptlrpc_request *request = NULL;
		int namelen, len = 0;
		char *buf = NULL;
		char *filename;
		struct md_op_data *op_data;

		rc = obd_ioctl_getdata(&buf, &len, (void *)arg);
		if (rc)
			return rc;
		data = (void *)buf;

		filename = data->ioc_inlbuf1;
		namelen = strlen(filename);

		if (namelen < 1) {
			CDEBUG(D_INFO, "IOC_MDC_LOOKUP missing filename\n");
			rc = -EINVAL;
			goto out_free;
		}

		op_data = ll_prep_md_op_data(NULL, inode, NULL, filename, namelen,
					     0, LUSTRE_OPC_ANY, NULL);
		if (IS_ERR(op_data)) {
			rc = PTR_ERR(op_data);
			goto out_free;
		}

		op_data->op_valid = OBD_MD_FLID;
		rc = md_getattr_name(sbi->ll_md_exp, op_data, &request);
		ll_finish_md_op_data(op_data);
		if (rc < 0) {
			CDEBUG(D_INFO, "md_getattr_name: %d\n", rc);
			goto out_free;
		}
		ptlrpc_req_finished(request);
out_free:
		obd_ioctl_freedata(buf, len);
		return rc;
	}
	case LL_IOC_LMV_SETSTRIPE: {
		struct lmv_user_md  *lum;
		char		*buf = NULL;
		char		*filename;
		int		 namelen = 0;
		int		 lumlen = 0;
		int		 len;
		int		 rc;

		rc = obd_ioctl_getdata(&buf, &len, (void *)arg);
		if (rc)
			return rc;

		data = (void *)buf;
		if (data->ioc_inlbuf1 == NULL || data->ioc_inlbuf2 == NULL ||
		    data->ioc_inllen1 == 0 || data->ioc_inllen2 == 0) {
			rc = -EINVAL;
			goto lmv_out_free;
		}

		filename = data->ioc_inlbuf1;
		namelen = data->ioc_inllen1;

		if (namelen < 1) {
			CDEBUG(D_INFO, "IOC_MDC_LOOKUP missing filename\n");
			rc = -EINVAL;
			goto lmv_out_free;
		}
		lum = (struct lmv_user_md *)data->ioc_inlbuf2;
		lumlen = data->ioc_inllen2;

		if (lum->lum_magic != LMV_USER_MAGIC ||
		    lumlen != sizeof(*lum)) {
			CERROR("%s: wrong lum magic %x or size %d: rc = %d\n",
			       filename, lum->lum_magic, lumlen, -EFAULT);
			rc = -EINVAL;
			goto lmv_out_free;
		}

		/**
		 * ll_dir_setdirstripe will be used to set dir stripe
		 *  mdc_create--->mdt_reint_create (with dirstripe)
		 */
		rc = ll_dir_setdirstripe(inode, lum, filename);
lmv_out_free:
		obd_ioctl_freedata(buf, len);
		return rc;

	}
	case LL_IOC_LOV_SETSTRIPE: {
		struct lov_user_md_v3 lumv3;
		struct lov_user_md_v1 *lumv1 = (struct lov_user_md_v1 *)&lumv3;
		struct lov_user_md_v1 *lumv1p = (struct lov_user_md_v1 *)arg;
		struct lov_user_md_v3 *lumv3p = (struct lov_user_md_v3 *)arg;

		int set_default = 0;

		LASSERT(sizeof(lumv3) == sizeof(*lumv3p));
		LASSERT(sizeof(lumv3.lmm_objects[0]) ==
			sizeof(lumv3p->lmm_objects[0]));
		/* first try with v1 which is smaller than v3 */
		if (copy_from_user(lumv1, lumv1p, sizeof(*lumv1)))
			return -EFAULT;

		if (lumv1->lmm_magic == LOV_USER_MAGIC_V3) {
			if (copy_from_user(&lumv3, lumv3p, sizeof(lumv3)))
				return -EFAULT;
		}

		if (is_root_inode(inode))
			set_default = 1;

		/* in v1 and v3 cases lumv1 points to data */
		rc = ll_dir_setstripe(inode, lumv1, set_default);

		return rc;
	}
	case LL_IOC_LMV_GETSTRIPE: {
		struct lmv_user_md *lump = (struct lmv_user_md *)arg;
		struct lmv_user_md lum;
		struct lmv_user_md *tmp;
		int lum_size;
		int rc = 0;
		int mdtindex;

		if (copy_from_user(&lum, lump, sizeof(struct lmv_user_md)))
			return -EFAULT;

		if (lum.lum_magic != LMV_MAGIC_V1)
			return -EINVAL;

		lum_size = lmv_user_md_size(1, LMV_MAGIC_V1);
		tmp = kzalloc(lum_size, GFP_NOFS);
		if (!tmp) {
			rc = -ENOMEM;
			goto free_lmv;
		}

		*tmp = lum;
		tmp->lum_type = LMV_STRIPE_TYPE;
		tmp->lum_stripe_count = 1;
		mdtindex = ll_get_mdt_idx(inode);
		if (mdtindex < 0) {
			rc = -ENOMEM;
			goto free_lmv;
		}

		tmp->lum_stripe_offset = mdtindex;
		tmp->lum_objects[0].lum_mds = mdtindex;
		memcpy(&tmp->lum_objects[0].lum_fid, ll_inode2fid(inode),
		       sizeof(struct lu_fid));
		if (copy_to_user((void *)arg, tmp, lum_size)) {
			rc = -EFAULT;
			goto free_lmv;
		}
free_lmv:
		kfree(tmp);
		return rc;
	}
	case LL_IOC_LOV_SWAP_LAYOUTS:
		return -EPERM;
	case LL_IOC_OBD_STATFS:
		return ll_obd_statfs(inode, (void *)arg);
	case LL_IOC_LOV_GETSTRIPE:
	case LL_IOC_MDC_GETINFO:
	case IOC_MDC_GETFILEINFO:
	case IOC_MDC_GETFILESTRIPE: {
		struct ptlrpc_request *request = NULL;
		struct lov_user_md *lump;
		struct lov_mds_md *lmm = NULL;
		struct mdt_body *body;
		char *filename = NULL;
		int lmmsize;

		if (cmd == IOC_MDC_GETFILEINFO ||
		    cmd == IOC_MDC_GETFILESTRIPE) {
			filename = ll_getname((const char *)arg);
			if (IS_ERR(filename))
				return PTR_ERR(filename);

			rc = ll_lov_getstripe_ea_info(inode, filename, &lmm,
						      &lmmsize, &request);
		} else {
			rc = ll_dir_getstripe(inode, &lmm, &lmmsize, &request);
		}

		if (request) {
			body = req_capsule_server_get(&request->rq_pill,
						      &RMF_MDT_BODY);
			LASSERT(body != NULL);
		} else {
			goto out_req;
		}

		if (rc < 0) {
			if (rc == -ENODATA && (cmd == IOC_MDC_GETFILEINFO ||
					       cmd == LL_IOC_MDC_GETINFO)) {
				rc = 0;
				goto skip_lmm;
			} else
				goto out_req;
		}

		if (cmd == IOC_MDC_GETFILESTRIPE ||
		    cmd == LL_IOC_LOV_GETSTRIPE) {
			lump = (struct lov_user_md *)arg;
		} else {
			struct lov_user_mds_data *lmdp;

			lmdp = (struct lov_user_mds_data *)arg;
			lump = &lmdp->lmd_lmm;
		}
		if (copy_to_user(lump, lmm, lmmsize)) {
			if (copy_to_user(lump, lmm, sizeof(*lump))) {
				rc = -EFAULT;
				goto out_req;
			}
			rc = -EOVERFLOW;
		}
skip_lmm:
		if (cmd == IOC_MDC_GETFILEINFO || cmd == LL_IOC_MDC_GETINFO) {
			struct lov_user_mds_data *lmdp;
			lstat_t st = { 0 };

			st.st_dev     = inode->i_sb->s_dev;
			st.st_mode    = body->mode;
			st.st_nlink   = body->nlink;
			st.st_uid     = body->uid;
			st.st_gid     = body->gid;
			st.st_rdev    = body->rdev;
			st.st_size    = body->size;
			st.st_blksize = PAGE_CACHE_SIZE;
			st.st_blocks  = body->blocks;
			st.st_atime   = body->atime;
			st.st_mtime   = body->mtime;
			st.st_ctime   = body->ctime;
			st.st_ino     = inode->i_ino;

			lmdp = (struct lov_user_mds_data *)arg;
			if (copy_to_user(&lmdp->lmd_st, &st, sizeof(st))) {
				rc = -EFAULT;
				goto out_req;
			}
		}

out_req:
		ptlrpc_req_finished(request);
		if (filename)
			ll_putname(filename);
		return rc;
	}
	case IOC_LOV_GETINFO: {
		struct lov_user_mds_data *lumd;
		struct lov_stripe_md *lsm;
		struct lov_user_md *lum;
		struct lov_mds_md *lmm;
		int lmmsize;
		lstat_t st;

		lumd = (struct lov_user_mds_data *)arg;
		lum = &lumd->lmd_lmm;

		rc = ll_get_max_mdsize(sbi, &lmmsize);
		if (rc)
			return rc;

		lmm = libcfs_kvzalloc(lmmsize, GFP_NOFS);
		if (lmm == NULL)
			return -ENOMEM;
		if (copy_from_user(lmm, lum, lmmsize)) {
			rc = -EFAULT;
			goto free_lmm;
		}

		switch (lmm->lmm_magic) {
		case LOV_USER_MAGIC_V1:
			if (cpu_to_le32(LOV_USER_MAGIC_V1) == LOV_USER_MAGIC_V1)
				break;
			/* swab objects first so that stripes num will be sane */
			lustre_swab_lov_user_md_objects(
				((struct lov_user_md_v1 *)lmm)->lmm_objects,
				((struct lov_user_md_v1 *)lmm)->lmm_stripe_count);
			lustre_swab_lov_user_md_v1((struct lov_user_md_v1 *)lmm);
			break;
		case LOV_USER_MAGIC_V3:
			if (cpu_to_le32(LOV_USER_MAGIC_V3) == LOV_USER_MAGIC_V3)
				break;
			/* swab objects first so that stripes num will be sane */
			lustre_swab_lov_user_md_objects(
				((struct lov_user_md_v3 *)lmm)->lmm_objects,
				((struct lov_user_md_v3 *)lmm)->lmm_stripe_count);
			lustre_swab_lov_user_md_v3((struct lov_user_md_v3 *)lmm);
			break;
		default:
			rc = -EINVAL;
			goto free_lmm;
		}

		rc = obd_unpackmd(sbi->ll_dt_exp, &lsm, lmm, lmmsize);
		if (rc < 0) {
			rc = -ENOMEM;
			goto free_lmm;
		}

		/* Perform glimpse_size operation. */
		memset(&st, 0, sizeof(st));

		rc = ll_glimpse_ioctl(sbi, lsm, &st);
		if (rc)
			goto free_lsm;

		if (copy_to_user(&lumd->lmd_st, &st, sizeof(st))) {
			rc = -EFAULT;
			goto free_lsm;
		}

free_lsm:
		obd_free_memmd(sbi->ll_dt_exp, &lsm);
free_lmm:
		kvfree(lmm);
		return rc;
	}
	case OBD_IOC_LLOG_CATINFO: {
		return -EOPNOTSUPP;
	}
	case OBD_IOC_QUOTACHECK: {
		struct obd_quotactl *oqctl;
		int error = 0;

		if (!capable(CFS_CAP_SYS_ADMIN) ||
		    sbi->ll_flags & LL_SBI_RMT_CLIENT)
			return -EPERM;

		oqctl = kzalloc(sizeof(*oqctl), GFP_NOFS);
		if (!oqctl)
			return -ENOMEM;
		oqctl->qc_type = arg;
		rc = obd_quotacheck(sbi->ll_md_exp, oqctl);
		if (rc < 0) {
			CDEBUG(D_INFO, "md_quotacheck failed: rc %d\n", rc);
			error = rc;
		}

		rc = obd_quotacheck(sbi->ll_dt_exp, oqctl);
		if (rc < 0)
			CDEBUG(D_INFO, "obd_quotacheck failed: rc %d\n", rc);

		kfree(oqctl);
		return error ?: rc;
	}
	case OBD_IOC_POLL_QUOTACHECK: {
		struct if_quotacheck *check;

		if (!capable(CFS_CAP_SYS_ADMIN) ||
		    sbi->ll_flags & LL_SBI_RMT_CLIENT)
			return -EPERM;

		check = kzalloc(sizeof(*check), GFP_NOFS);
		if (!check)
			return -ENOMEM;

		rc = obd_iocontrol(cmd, sbi->ll_md_exp, 0, (void *)check,
				   NULL);
		if (rc) {
			CDEBUG(D_QUOTA, "mdc ioctl %d failed: %d\n", cmd, rc);
			if (copy_to_user((void *)arg, check,
					     sizeof(*check)))
				CDEBUG(D_QUOTA, "copy_to_user failed\n");
			goto out_poll;
		}

		rc = obd_iocontrol(cmd, sbi->ll_dt_exp, 0, (void *)check,
				   NULL);
		if (rc) {
			CDEBUG(D_QUOTA, "osc ioctl %d failed: %d\n", cmd, rc);
			if (copy_to_user((void *)arg, check,
					     sizeof(*check)))
				CDEBUG(D_QUOTA, "copy_to_user failed\n");
			goto out_poll;
		}
out_poll:
		kfree(check);
		return rc;
	}
	case LL_IOC_QUOTACTL: {
		struct if_quotactl *qctl;

		qctl = kzalloc(sizeof(*qctl), GFP_NOFS);
		if (!qctl)
			return -ENOMEM;

		if (copy_from_user(qctl, (void *)arg, sizeof(*qctl))) {
			rc = -EFAULT;
			goto out_quotactl;
		}

		rc = quotactl_ioctl(sbi, qctl);

		if (rc == 0 && copy_to_user((void *)arg, qctl, sizeof(*qctl)))
			rc = -EFAULT;

out_quotactl:
		kfree(qctl);
		return rc;
	}
	case OBD_IOC_GETDTNAME:
	case OBD_IOC_GETMDNAME:
		return ll_get_obd_name(inode, cmd, arg);
	case LL_IOC_FLUSHCTX:
		return ll_flush_ctx(inode);
#ifdef CONFIG_FS_POSIX_ACL
	case LL_IOC_RMTACL: {
	    if (sbi->ll_flags & LL_SBI_RMT_CLIENT && is_root_inode(inode)) {
		struct ll_file_data *fd = LUSTRE_FPRIVATE(file);

		LASSERT(fd != NULL);
		rc = rct_add(&sbi->ll_rct, current_pid(), arg);
		if (!rc)
			fd->fd_flags |= LL_FILE_RMTACL;
		return rc;
	    } else
		return 0;
	}
#endif
	case LL_IOC_GETOBDCOUNT: {
		int count, vallen;
		struct obd_export *exp;

		if (copy_from_user(&count, (int *)arg, sizeof(int)))
			return -EFAULT;

		/* get ost count when count is zero, get mdt count otherwise */
		exp = count ? sbi->ll_md_exp : sbi->ll_dt_exp;
		vallen = sizeof(count);
		rc = obd_get_info(NULL, exp, sizeof(KEY_TGT_COUNT),
				  KEY_TGT_COUNT, &vallen, &count, NULL);
		if (rc) {
			CERROR("get target count failed: %d\n", rc);
			return rc;
		}

		if (copy_to_user((int *)arg, &count, sizeof(int)))
			return -EFAULT;

		return 0;
	}
	case LL_IOC_PATH2FID:
		if (copy_to_user((void *)arg, ll_inode2fid(inode),
				     sizeof(struct lu_fid)))
			return -EFAULT;
		return 0;
	case LL_IOC_GET_CONNECT_FLAGS: {
		return obd_iocontrol(cmd, sbi->ll_md_exp, 0, NULL, (void *)arg);
	}
	case OBD_IOC_CHANGELOG_SEND:
	case OBD_IOC_CHANGELOG_CLEAR:
		if (!capable(CFS_CAP_SYS_ADMIN))
			return -EPERM;

		rc = copy_and_ioctl(cmd, sbi->ll_md_exp, (void *)arg,
				    sizeof(struct ioc_changelog));
		return rc;
	case OBD_IOC_FID2PATH:
		return ll_fid2path(inode, (void *)arg);
	case LL_IOC_HSM_REQUEST: {
		struct hsm_user_request	*hur;
		ssize_t			 totalsize;

		hur = memdup_user((void *)arg, sizeof(*hur));
		if (IS_ERR(hur))
			return PTR_ERR(hur);

		/* Compute the whole struct size */
		totalsize = hur_len(hur);
		kfree(hur);
		if (totalsize < 0)
			return -E2BIG;

		/* Final size will be more than double totalsize */
		if (totalsize >= MDS_MAXREQSIZE / 3)
			return -E2BIG;

		hur = libcfs_kvzalloc(totalsize, GFP_NOFS);
		if (hur == NULL)
			return -ENOMEM;

		/* Copy the whole struct */
		if (copy_from_user(hur, (void *)arg, totalsize)) {
			kvfree(hur);
			return -EFAULT;
		}

		if (hur->hur_request.hr_action == HUA_RELEASE) {
			const struct lu_fid *fid;
			struct inode *f;
			int i;

			for (i = 0; i < hur->hur_request.hr_itemcount; i++) {
				fid = &hur->hur_user_item[i].hui_fid;
				f = search_inode_for_lustre(inode->i_sb, fid);
				if (IS_ERR(f)) {
					rc = PTR_ERR(f);
					break;
				}

				rc = ll_hsm_release(f);
				iput(f);
				if (rc != 0)
					break;
			}
		} else {
			rc = obd_iocontrol(cmd, ll_i2mdexp(inode), totalsize,
					   hur, NULL);
		}

		kvfree(hur);

		return rc;
	}
	case LL_IOC_HSM_PROGRESS: {
		struct hsm_progress_kernel	hpk;
		struct hsm_progress		hp;

		if (copy_from_user(&hp, (void *)arg, sizeof(hp)))
			return -EFAULT;

		hpk.hpk_fid = hp.hp_fid;
		hpk.hpk_cookie = hp.hp_cookie;
		hpk.hpk_extent = hp.hp_extent;
		hpk.hpk_flags = hp.hp_flags;
		hpk.hpk_errval = hp.hp_errval;
		hpk.hpk_data_version = 0;

		/* File may not exist in Lustre; all progress
		 * reported to Lustre root */
		rc = obd_iocontrol(cmd, sbi->ll_md_exp, sizeof(hpk), &hpk,
				   NULL);
		return rc;
	}
	case LL_IOC_HSM_CT_START:
		rc = copy_and_ioctl(cmd, sbi->ll_md_exp, (void *)arg,
				    sizeof(struct lustre_kernelcomm));
		return rc;

	case LL_IOC_HSM_COPY_START: {
		struct hsm_copy	*copy;
		int		 rc;

		copy = memdup_user((char *)arg, sizeof(*copy));
		if (IS_ERR(copy))
			return PTR_ERR(copy);

		rc = ll_ioc_copy_start(inode->i_sb, copy);
		if (copy_to_user((char *)arg, copy, sizeof(*copy)))
			rc = -EFAULT;

		kfree(copy);
		return rc;
	}
	case LL_IOC_HSM_COPY_END: {
		struct hsm_copy	*copy;
		int		 rc;

		copy = memdup_user((char *)arg, sizeof(*copy));
		if (IS_ERR(copy))
			return PTR_ERR(copy);

		rc = ll_ioc_copy_end(inode->i_sb, copy);
		if (copy_to_user((char *)arg, copy, sizeof(*copy)))
			rc = -EFAULT;

		kfree(copy);
		return rc;
	}
	default:
		return obd_iocontrol(cmd, sbi->ll_dt_exp, 0, NULL, (void *)arg);
	}
