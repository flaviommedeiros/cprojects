switch (srb->cmnd[1]) {
	case READ_STATUS:
		result = read_status(srb, chip);
		break;

	case READ_MEM:
		result = read_mem(srb, chip);
		break;

	case WRITE_MEM:
		result = write_mem(srb, chip);
		break;

	case READ_EEPROM:
		result = read_eeprom(srb, chip);
		break;

	case WRITE_EEPROM:
		result = write_eeprom(srb, chip);
		break;

	case TOGGLE_GPIO:
		result = toggle_gpio_cmd(srb, chip);
		break;

	case GET_SD_CSD:
		result = get_sd_csd(srb, chip);
		break;

	case GET_BUS_WIDTH:
		result = get_card_bus_width(srb, chip);
		break;

#ifdef _MSG_TRACE
	case TRACE_MSG:
		result = trace_msg_cmd(srb, chip);
		break;
#endif

	case SCSI_APP_CMD:
		result = app_cmd(srb, chip);
		break;

	case SPI_VENDOR_COMMAND:
		result = spi_vendor_cmd(srb, chip);
		break;

	default:
		set_sense_type(chip, SCSI_LUN(srb), SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		TRACE_RET(chip, TRANSPORT_FAILED);
	}
