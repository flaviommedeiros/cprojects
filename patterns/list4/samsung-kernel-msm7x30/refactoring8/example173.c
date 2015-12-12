int dcd_get_object_def(struct dcd_manager *hdcd_mgr,
			      struct dsp_uuid *obj_uuid,
			      enum dsp_dcdobjtype obj_type,
			      struct dcd_genericobj *obj_def)
{
	struct dcd_manager *dcd_mgr_obj = hdcd_mgr;	/* ptr to DCD mgr */
	struct cod_libraryobj *lib = NULL;
	int status = 0;
	u32 ul_addr = 0;	/* Used by cod_get_section */
	u32 ul_len = 0;		/* Used by cod_get_section */
	u32 dw_buf_size;	/* Used by REG functions */
	char sz_reg_key[DCD_MAXPATHLENGTH];
	char *sz_uuid;		/*[MAXUUIDLEN]; */
	struct dcd_key_elem *dcd_key = NULL;
	char sz_sect_name[MAXUUIDLEN + 2];	/* ".[UUID]\0" */
	char *psz_coff_buf;
	u32 dw_key_len;		/* Len of REG key. */
	char sz_obj_type[MAX_INT2CHAR_LENGTH];	/* str. rep. of obj_type. */

	sz_uuid = kzalloc(MAXUUIDLEN, GFP_KERNEL);
	if (!sz_uuid) {
		status = -ENOMEM;
		goto func_end;
	}

	if (!hdcd_mgr) {
		status = -EFAULT;
		goto func_end;
	}

	/* Pre-determine final key length. It's length of DCD_REGKEY +
	 *  "_\0" + length of sz_obj_type string + terminating NULL */
	dw_key_len = strlen(DCD_REGKEY) + 1 + sizeof(sz_obj_type) + 1;

	/* Create proper REG key; concatenate DCD_REGKEY with obj_type. */
	strncpy(sz_reg_key, DCD_REGKEY, strlen(DCD_REGKEY) + 1);

	if ((strlen(sz_reg_key) + strlen("_\0")) < DCD_MAXPATHLENGTH)
		strncat(sz_reg_key, "_\0", 2);
	else
		status = -EPERM;

	status = snprintf(sz_obj_type, MAX_INT2CHAR_LENGTH, "%d", obj_type);
	if (status == -1) {
		status = -EPERM;
	} else {
		status = 0;

		if ((strlen(sz_reg_key) + strlen(sz_obj_type)) <
		    DCD_MAXPATHLENGTH) {
			strncat(sz_reg_key, sz_obj_type,
				strlen(sz_obj_type) + 1);
		} else {
			status = -EPERM;
		}

		/* Create UUID value to set in registry. */
		uuid_uuid_to_string(obj_uuid, sz_uuid, MAXUUIDLEN);

		if ((strlen(sz_reg_key) + MAXUUIDLEN) < DCD_MAXPATHLENGTH)
			strncat(sz_reg_key, sz_uuid, MAXUUIDLEN);
		else
			status = -EPERM;

		/* Retrieve paths from the registry based on struct dsp_uuid */
		dw_buf_size = DCD_MAXPATHLENGTH;
	}
	if (!status) {
		spin_lock(&dbdcd_lock);
		list_for_each_entry(dcd_key, &reg_key_list, link) {
			if (!strncmp(dcd_key->name, sz_reg_key,
						strlen(sz_reg_key) + 1))
				break;
		}
		spin_unlock(&dbdcd_lock);
		if (&dcd_key->link == &reg_key_list) {
			status = -ENOKEY;
			goto func_end;
		}
	}


	/* Open COFF file. */
	status = cod_open(dcd_mgr_obj->cod_mgr, dcd_key->path,
							COD_NOLOAD, &lib);
	if (status) {
		status = -EACCES;
		goto func_end;
	}

	/* Ensure sz_uuid + 1 is not greater than sizeof sz_sect_name. */

	/* Create section name based on node UUID. A period is
	 * pre-pended to the UUID string to form the section name.
	 * I.e. ".24BC8D90_BB45_11d4_B756_006008BDB66F" */
	strncpy(sz_sect_name, ".", 2);
	strncat(sz_sect_name, sz_uuid, strlen(sz_uuid));

	/* Get section information. */
	status = cod_get_section(lib, sz_sect_name, &ul_addr, &ul_len);
	if (status) {
		status = -EACCES;
		goto func_end;
	}

	/* Allocate zeroed buffer. */
	psz_coff_buf = kzalloc(ul_len + 4, GFP_KERNEL);
	if (psz_coff_buf == NULL) {
		status = -ENOMEM;
		goto func_end;
	}
#ifdef _DB_TIOMAP
	if (strstr(dcd_key->path, "iva") == NULL) {
		/* Locate section by objectID and read its content. */
		status =
		    cod_read_section(lib, sz_sect_name, psz_coff_buf, ul_len);
	} else {
		status =
		    cod_read_section(lib, sz_sect_name, psz_coff_buf, ul_len);
		dev_dbg(bridge, "%s: Skipped Byte swap for IVA!!\n", __func__);
	}
#else
	status = cod_read_section(lib, sz_sect_name, psz_coff_buf, ul_len);
#endif
	if (!status) {
		/* Compres DSP buffer to conform to PC format. */
		if (strstr(dcd_key->path, "iva") == NULL) {
			compress_buf(psz_coff_buf, ul_len, DSPWORDSIZE);
		} else {
			compress_buf(psz_coff_buf, ul_len, 1);
			dev_dbg(bridge, "%s: Compressing IVA COFF buffer by 1 "
				"for IVA!!\n", __func__);
		}

		/* Parse the content of the COFF buffer. */
		status =
		    get_attrs_from_buf(psz_coff_buf, ul_len, obj_type, obj_def);
		if (status)
			status = -EACCES;
	} else {
		status = -EACCES;
	}

	/* Free the previously allocated dynamic buffer. */
	kfree(psz_coff_buf);
func_end:
	if (lib)
		cod_close(lib);

	kfree(sz_uuid);

	return status;
}
