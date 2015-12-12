extern int set_select_jobinfo(select_jobinfo_t *jobinfo,
			      enum select_jobdata_type data_type, void *data)
{
	int i, rc = SLURM_SUCCESS;
	uint16_t *uint16 = (uint16_t *) data;
	uint32_t *uint32 = (uint32_t *) data;
	uid_t *uid = (uid_t *)data;
	char *tmp_char = (char *) data;
	bg_record_t *bg_record = (bg_record_t *) data;
	uint32_t new_size;

	if (!jobinfo) {
		error("set_select_jobinfo: jobinfo is NULL");
		return SLURM_ERROR;
	} else if (jobinfo->magic != JOBINFO_MAGIC) {
		error("set_select_jobinfo: jobinfo magic bad");
		return SLURM_ERROR;
	}

	if (!jobinfo->dim_cnt)
		jobinfo->dim_cnt = SYSTEM_DIMENSIONS;

	switch (data_type) {
	case SELECT_JOBDATA_DIM_CNT:
		jobinfo->dim_cnt = *uint16;
		break;
	case SELECT_JOBDATA_GEOMETRY:
		new_size = 1;
		for (i=0; i<jobinfo->dim_cnt; i++) {
			/* If geo[i] is NO_VAL then we know this
			   doesn't need to be reset.
			*/
			if (jobinfo->geometry[i] != (uint16_t) NO_VAL) {
				/* Make sure the conn type is correct with the
				 * new count (if Geometry is requested it
				 * can't be small) */
				jobinfo->conn_type[i] =	SELECT_NAV;
			}
			jobinfo->geometry[i] = uint16[i];
			new_size *= uint16[i];
		}

		break;
	case SELECT_JOBDATA_REBOOT:
		jobinfo->reboot = *uint16;
		break;
	case SELECT_JOBDATA_ROTATE:
		jobinfo->rotate = *uint16;
		break;
	case SELECT_JOBDATA_CONN_TYPE:
		for (i=0; i<jobinfo->dim_cnt; i++)
			jobinfo->conn_type[i] = uint16[i];
		break;
	case SELECT_JOBDATA_BLOCK_ID:
		/* we xfree() any preset value to avoid a memory leak */
		xfree(jobinfo->bg_block_id);
		jobinfo->bg_block_id = xstrdup(tmp_char);
		break;
	case SELECT_JOBDATA_BLOCK_NODE_CNT:
		jobinfo->block_cnode_cnt = *uint32;
		break;
	case SELECT_JOBDATA_BLOCK_PTR:
		jobinfo->bg_record = bg_record;
		xfree(jobinfo->bg_block_id);
		if (bg_record) {
			jobinfo->bg_block_id = xstrdup(bg_record->bg_block_id);
			jobinfo->block_cnode_cnt = bg_record->cnode_cnt;
		} else {
			jobinfo->bg_block_id = xstrdup("unassigned");
			jobinfo->block_cnode_cnt = 0;
		}
		break;
	case SELECT_JOBDATA_NODES:
		xfree(jobinfo->mp_str);
		jobinfo->mp_str = xstrdup(tmp_char);
		break;
	case SELECT_JOBDATA_IONODES:
		xfree(jobinfo->ionode_str);
		if (tmp_char) {
#ifdef HAVE_BGQ
			jobinfo->dim_cnt = 5;
			for (i=0; i<jobinfo->dim_cnt; i++) {
				jobinfo->start_loc[i] =
					select_char2coord(tmp_char[i]);
			}
#else
			jobinfo->dim_cnt = SYSTEM_DIMENSIONS;
#endif
			jobinfo->ionode_str = xstrdup(tmp_char);
		} else
			jobinfo->dim_cnt = SYSTEM_DIMENSIONS;

		break;
	case SELECT_JOBDATA_NODE_CNT:
		jobinfo->cnode_cnt = *uint32;
		/* Make sure the conn type is correct with the new count */
		if (bg_conf->sub_mp_sys
		    || (jobinfo->cnode_cnt < bg_conf->mp_cnode_cnt)) {
			if (jobinfo->conn_type[0] < SELECT_SMALL)
				jobinfo->conn_type[0] = SELECT_SMALL;
		} else if (jobinfo->conn_type[0] >= SELECT_SMALL) {
			for (i=0; i<SYSTEM_DIMENSIONS; i++)
				jobinfo->conn_type[i] = SELECT_NAV;
		}
		break;
	case SELECT_JOBDATA_ALTERED:
		jobinfo->altered = *uint16;
		break;
	case SELECT_JOBDATA_BLRTS_IMAGE:
		/* we xfree() any preset value to avoid a memory leak */
		xfree(jobinfo->blrtsimage);
		jobinfo->blrtsimage = xstrdup(tmp_char);
		break;
	case SELECT_JOBDATA_LINUX_IMAGE:
		/* we xfree() any preset value to avoid a memory leak */
		xfree(jobinfo->linuximage);
		jobinfo->linuximage = xstrdup(tmp_char);
		break;
	case SELECT_JOBDATA_MLOADER_IMAGE:
		/* we xfree() any preset value to avoid a memory leak */
		xfree(jobinfo->mloaderimage);
		jobinfo->mloaderimage = xstrdup(tmp_char);
		break;
	case SELECT_JOBDATA_RAMDISK_IMAGE:
		/* we xfree() any preset value to avoid a memory leak */
		xfree(jobinfo->ramdiskimage);
		jobinfo->ramdiskimage = xstrdup(tmp_char);
		break;
	case SELECT_JOBDATA_START_LOC:
		for (i=0; i<jobinfo->dim_cnt; i++)
			jobinfo->start_loc[i] = uint16[i];
		break;
	case SELECT_JOBDATA_USER_NAME:
		xfree(jobinfo->user_name);
		jobinfo->user_name = uid_to_string(*uid);
		break;
	default:
		debug3("set_select_jobinfo: data_type %d invalid",
		       data_type);
	}

	return rc;
}
