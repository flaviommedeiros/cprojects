switch (chip_select) {
	case 0:
		gpio_set_value(MCFQSPI_CS0, cs_high);
		break;
	case 1:
		gpio_set_value(MCFQSPI_CS1, cs_high);
		break;
	case 2:
		gpio_set_value(MCFQSPI_CS2, cs_high);
		break;
#ifdef MCFQSPI_CS3
	case 3:
		gpio_set_value(MCFQSPI_CS3, cs_high);
		break;
#endif
	}
