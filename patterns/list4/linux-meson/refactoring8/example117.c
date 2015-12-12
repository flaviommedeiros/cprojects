void HI704_set_param_banding(struct HI704_device *dev,enum  camera_banding_flip_e banding)
{
	struct i2c_client *client = v4l2_get_subdevdata(&dev->sd);
	int i;
	unsigned char buf[2];
	#if 1
	switch (banding) {
	case CAM_BANDING_60HZ:
		i=0;
		while (regs60hz[i].addr!= 0xff && regs60hz[i].val!= 0xff)
		{
			buf[0]=regs60hz[i].addr;
			buf[1]=regs60hz[i].val;
			i2c_put_byte_add8(client,buf, 2);
			i++;
		}
		break;
	case CAM_BANDING_50HZ:
		i=0;
		while (regs50hz[i].addr!= 0xff && regs50hz[i].val!= 0xff)
		{
			buf[0]=regs50hz[i].addr;
			buf[1]=regs50hz[i].val;
			i2c_put_byte_add8(client,buf, 2);
			i++;
		}
		break;
	default:
		break;

	}
	#endif
}
