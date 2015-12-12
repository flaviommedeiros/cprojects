switch (srb->cmnd[0]) {
	case READ_10:
	case WRITE_10:
	case READ_6:
	case WRITE_6:
		result = read_write(srb, chip);
#if !defined(LED_AUTO_BLINK) && !defined(REGULAR_BLINK)
		led_shine(srb, chip);
#endif
		break;

	case TEST_UNIT_READY:
		result = test_unit_ready(srb, chip);
		break;

	case INQUIRY:
		result = inquiry(srb, chip);
		break;

	case READ_CAPACITY:
		result = read_capacity(srb, chip);
		break;

	case START_STOP:
		result = start_stop_unit(srb, chip);
		break;

	case ALLOW_MEDIUM_REMOVAL:
		result = allow_medium_removal(srb, chip);
		break;

	case REQUEST_SENSE:
		result = request_sense(srb, chip);
		break;

	case MODE_SENSE:
	case MODE_SENSE_10:
		result = mode_sense(srb, chip);
		break;

	case 0x23:
		result = read_format_capacity(srb, chip);
		break;

	case VENDOR_CMND:
		result = vendor_cmnd(srb, chip);
		break;

	case MS_SP_CMND:
		result = ms_sp_cmnd(srb, chip);
		break;

#ifdef SUPPORT_CPRM
	case SD_PASS_THRU_MODE:
	case SD_EXECUTE_NO_DATA:
	case SD_EXECUTE_READ:
	case SD_EXECUTE_WRITE:
	case SD_GET_RSP:
	case SD_HW_RST:
		result = sd_extention_cmnd(srb, chip);
		break;
#endif

#ifdef SUPPORT_MAGIC_GATE
	case CMD_MSPRO_MG_RKEY:
		result = mg_report_key(srb, chip);
		break;

	case CMD_MSPRO_MG_SKEY:
		result = mg_send_key(srb, chip);
		break;
#endif

	case FORMAT_UNIT:
	case MODE_SELECT:
	case VERIFY:
		result = TRANSPORT_GOOD;
		break;

	default:
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		result = TRANSPORT_FAILED;
	}
