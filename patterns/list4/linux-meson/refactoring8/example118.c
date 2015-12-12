void set_HI704_param_exposure(struct HI704_device *dev,enum camera_exposure_e para)//ÆØ¹âµ÷½Ú
{
	struct i2c_client *client = v4l2_get_subdevdata(&dev->sd);

	unsigned char buf1[2];
	unsigned char buf2[2];
#if 1
	switch (para) {
	case EXPOSURE_N4_STEP:
		buf1[0]=0x03;
		buf1[1]=0x10;
		buf2[0]=0x40;
		buf2[1]=0xc0;
		break;
	case EXPOSURE_N3_STEP:
		buf1[0]=0x03;
		buf1[1]=0x10;
		buf2[0]=0x40;
		buf2[1]=0xb0;
		break;
	case EXPOSURE_N2_STEP:
		buf1[0]=0x03;
		buf1[1]=0x10;
		buf2[0]=0x40;
		buf2[1]=0xa0;
		break;
	case EXPOSURE_N1_STEP:
		buf1[0]=0x03;
		buf1[1]=0x10;
		buf2[0]=0x40;
		buf2[1]=0x98;
		break;
	case EXPOSURE_0_STEP:
		buf1[0]=0x03;
		buf1[1]=0x10;
		buf2[0]=0x40;
		buf2[1]=0x80;
		break;
	case EXPOSURE_P1_STEP:
		buf1[0]=0x03;
		buf1[1]=0x10;
		buf2[0]=0x40;
		buf2[1]=0x10;
		break;
	case EXPOSURE_P2_STEP:
		buf1[0]=0x03;
		buf1[1]=0x10;
		buf2[0]=0x40;
		buf2[1]=0x20;
		break;
	case EXPOSURE_P3_STEP:
		buf1[0]=0x03;
		buf1[1]=0x10;
		buf2[0]=0x40;
		buf2[1]=0x30;
		break;
	case EXPOSURE_P4_STEP:
		buf1[0]=0x03;
		buf1[1]=0x10;
		buf2[0]=0x40;
		buf2[1]=0x40;
		break;
	default:
		buf1[0]=0x03;
		buf1[1]=0x10;
		buf2[0]=0x40;
		buf2[1]=0x50;
		break;
	}
	//msleep(300);
	i2c_put_byte_add8(client,buf1,2);
	i2c_put_byte_add8(client,buf2,2);
#endif
}
