switch (sense_type) {
	case SENSE_TYPE_MEDIA_CHANGE:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0x06, 0, 0x28, 0, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_NOT_PRESENT:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0x02, 0, 0x3A, 0, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_LBA_OVER_RANGE:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0x05, 0, 0x21, 0, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0x05, 0, 0x25, 0, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_WRITE_PROTECT:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0x07, 0, 0x27, 0, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0x03, 0, 0x11, 0, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_WRITE_ERR:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0x03, 0, 0x0C, 0x02, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_INVALID_CMD_FIELD:
		rts51x_set_sense_data(chip, lun, CUR_ERR, ILGAL_REQ, 0,
			       ASC_INVLD_CDB, ASCQ_INVLD_CDB, CDB_ILLEGAL, 1);
		break;

	case SENSE_TYPE_FORMAT_CMD_FAILED:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0x03, 0, 0x31, 0x01, 0, 0);
		break;

#ifdef SUPPORT_MAGIC_GATE
	case SENSE_TYPE_MG_KEY_FAIL_NOT_ESTAB:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0x05, 0, 0x6F, 0x02, 0, 0);
		break;

	case SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0x05, 0, 0x6F, 0x00, 0, 0);
		break;

	case SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0x02, 0, 0x30, 0x00, 0, 0);
		break;

	case SENSE_TYPE_MG_WRITE_ERR:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0x03, 0, 0x0C, 0x00, 0, 0);
		break;
#endif

	case SENSE_TYPE_NO_SENSE:
	default:
		rts51x_set_sense_data(chip, lun, CUR_ERR, 0, 0, 0, 0, 0, 0);
		break;
	}
