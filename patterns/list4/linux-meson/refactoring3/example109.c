switch (para)
		{
		/*case EXPOSURE_N4_STEP:
			i2c_put_byte(client,0x3376, 0x02);
			break;
		case EXPOSURE_N3_STEP:
			i2c_put_byte(client,0x3376, 0x03);

			break;
		case EXPOSURE_N2_STEP:
			i2c_put_byte(client,0x3376, 0x04);

			break;
		case EXPOSURE_N1_STEP:
			i2c_put_byte(client,0x3376, 0x05);

			break;
		case EXPOSURE_0_STEP:
			i2c_put_byte(client,0x3376, 0x06);

			break;
		case EXPOSURE_P1_STEP:
			i2c_put_byte(client,0x3376, 0x07);

			break;
		case EXPOSURE_P2_STEP:
			i2c_put_byte(client,0x3376, 0x08);

			break;
		case EXPOSURE_P3_STEP:
			i2c_put_byte(client,0x3376, 0x09);

			break;
		case EXPOSURE_P4_STEP:
			i2c_put_byte(client,0x3376, 0x0a);

			break;
		default:
			i2c_put_byte(client,0x3376, 0x06);

			break;
		*/
		#if 1
		case EXPOSURE_N4_STEP:
			i2c_put_byte(client,0x3391, 0x06);
			i2c_put_byte(client,0x3390, 0x49);
			i2c_put_byte(client,0x339a, 0x30);
			break;
		case EXPOSURE_N3_STEP:
			i2c_put_byte(client,0x3391, 0x06);
			i2c_put_byte(client,0x3390, 0x49);
			i2c_put_byte(client,0x339a, 0x20);
			break;
		case EXPOSURE_N2_STEP:
			i2c_put_byte(client,0x3391, 0x06);
			i2c_put_byte(client,0x3390, 0x49);
			i2c_put_byte(client,0x339a, 0x10);
			break;
		case EXPOSURE_N1_STEP:
			i2c_put_byte(client,0x3391, 0x06);
			i2c_put_byte(client,0x3390, 0x49);
			i2c_put_byte(client,0x339a, 0x00);
			break;
		case EXPOSURE_0_STEP:
			i2c_put_byte(client,0x3391, 0x06);
			i2c_put_byte(client,0x3390, 0x41);
			i2c_put_byte(client,0x339a, 0x10);
			break;
		case EXPOSURE_P1_STEP:
			i2c_put_byte(client,0x3391, 0x06);
			i2c_put_byte(client,0x3390, 0x41);
			i2c_put_byte(client,0x339a, 0x20);
			break;
		case EXPOSURE_P2_STEP:
			i2c_put_byte(client,0x3391, 0x06);
			i2c_put_byte(client,0x3390, 0x41);
			i2c_put_byte(client,0x339a, 0x30);
			break;
		case EXPOSURE_P3_STEP:
			i2c_put_byte(client,0x3391, 0x06);
			i2c_put_byte(client,0x3390, 0x41);
			i2c_put_byte(client,0x339a, 0x40);
			break;
		case EXPOSURE_P4_STEP:
			i2c_put_byte(client,0x3391, 0x06);
			i2c_put_byte(client,0x3390, 0x41);
			i2c_put_byte(client,0x339a, 0x50);
			break;
		default:
			i2c_put_byte(client,0x3391, 0x06);
			i2c_put_byte(client,0x3390, 0x41);
			i2c_put_byte(client,0x339a, 0x14);
			break;
		#else
		case EXPOSURE_N4_STEP:
			i2c_put_byte(client,0x3018, 0x40);
			i2c_put_byte(client,0x3019, 0x30);
			i2c_put_byte(client,0x301a, 0x71);
			break;
		case EXPOSURE_N3_STEP:
			i2c_put_byte(client,0x3018, 0x40);
			i2c_put_byte(client,0x3019, 0x30);
			i2c_put_byte(client,0x301a, 0x71);
			break;
		case EXPOSURE_N2_STEP:
			i2c_put_byte(client,0x3018, 0x5a);
			i2c_put_byte(client,0x3019, 0x4a);
			i2c_put_byte(client,0x301a, 0xc2);
			break;
		case EXPOSURE_N1_STEP:
			i2c_put_byte(client,0x3018, 0x6a);
			i2c_put_byte(client,0x3019, 0x5a);
			i2c_put_byte(client,0x301a, 0xd4);
			break;
		case EXPOSURE_0_STEP:
			i2c_put_byte(client,0x3018, 0x78);
			i2c_put_byte(client,0x3019, 0x68);
			i2c_put_byte(client,0x301a, 0xd4);
			break;
		case EXPOSURE_P1_STEP:
			i2c_put_byte(client,0x3018, 0x88);
			i2c_put_byte(client,0x3019, 0x78);
			i2c_put_byte(client,0x301a, 0xd5);
			break;
		case EXPOSURE_P2_STEP:
			i2c_put_byte(client,0x3018, 0xa8);
			i2c_put_byte(client,0x3019, 0x98);
			i2c_put_byte(client,0x301a, 0xe6);
			break;
		case EXPOSURE_P3_STEP:
			i2c_put_byte(client,0x3018, 0xc8);
			i2c_put_byte(client,0x3019, 0xb8);
			i2c_put_byte(client,0x301a, 0xf7);

			break;
		case EXPOSURE_P4_STEP:
			i2c_put_byte(client,0x3018, 0xc8);
			i2c_put_byte(client,0x3019, 0xb8);
			i2c_put_byte(client,0x301a, 0xf7);
			break;
		default:
			i2c_put_byte(client,0x3018, 0x78);
			i2c_put_byte(client,0x3019, 0x68);
			i2c_put_byte(client,0x301a, 0xd4);
			break;
		#endif

	}
