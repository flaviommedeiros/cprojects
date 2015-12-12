static int
ctrl_lock_status(struct drx_demod_instance *demod, enum drx_lock_status *lock_stat)
{
	enum drx_standard standard = DRX_STANDARD_UNKNOWN;
	struct drxj_data *ext_attr = NULL;
	struct i2c_device_addr *dev_addr = NULL;
	struct drxjscu_cmd cmd_scu = { /* command      */ 0,
		/* parameter_len */ 0,
		/* result_len    */ 0,
		/* *parameter   */ NULL,
		/* *result      */ NULL
	};
	int rc;
	u16 cmd_result[2] = { 0, 0 };
	u16 demod_lock = SCU_RAM_PARAM_1_RES_DEMOD_GET_LOCK_DEMOD_LOCKED;

	/* check arguments */
	if ((demod == NULL) || (lock_stat == NULL))
		return -EINVAL;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (struct drxj_data *) demod->my_ext_attr;
	standard = ext_attr->standard;

	*lock_stat = DRX_NOT_LOCKED;

	/* define the SCU command code */
	switch (standard) {
	case DRX_STANDARD_8VSB:
		cmd_scu.command = SCU_RAM_COMMAND_STANDARD_VSB |
		    SCU_RAM_COMMAND_CMD_DEMOD_GET_LOCK;
		demod_lock |= 0x6;
		break;
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:
	case DRX_STANDARD_ITU_B:
	case DRX_STANDARD_ITU_C:
		cmd_scu.command = SCU_RAM_COMMAND_STANDARD_QAM |
		    SCU_RAM_COMMAND_CMD_DEMOD_GET_LOCK;
		break;
#endif
	case DRX_STANDARD_UNKNOWN:	/* fallthrough */
	default:
		return -EIO;
	}

	/* define the SCU command parameters and execute the command */
	cmd_scu.parameter_len = 0;
	cmd_scu.result_len = 2;
	cmd_scu.parameter = NULL;
	cmd_scu.result = cmd_result;
	rc = scu_command(dev_addr, &cmd_scu);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	/* set the lock status */
	if (cmd_scu.result[1] < demod_lock) {
		/* 0x0000 NOT LOCKED */
		*lock_stat = DRX_NOT_LOCKED;
	} else if (cmd_scu.result[1] < SCU_RAM_PARAM_1_RES_DEMOD_GET_LOCK_LOCKED) {
		*lock_stat = DRXJ_DEMOD_LOCK;
	} else if (cmd_scu.result[1] <
		   SCU_RAM_PARAM_1_RES_DEMOD_GET_LOCK_NEVER_LOCK) {
		/* 0x8000 DEMOD + FEC LOCKED (system lock) */
		*lock_stat = DRX_LOCKED;
	} else {
		/* 0xC000 NEVER LOCKED */
		/* (system will never be able to lock to the signal) */
		*lock_stat = DRX_NEVER_LOCK;
	}

	return 0;
rw_error:
	return rc;
}
