void HI704_night_mode(struct HI704_device *dev,enum  camera_night_mode_flip_e enable)
{
	struct i2c_client *client = v4l2_get_subdevdata(&dev->sd);
	unsigned char buf[4];
	int i=0;

	//unsigned char  temp_reg;
	//temp_reg=HI704_read_byte(0x22);
	//buf[0]=0x20;
	//temp_reg=i2c_get_byte_add8(client,buf);
	//temp_reg=0xff;
	#if 1
	if (enable) {
		
		struct aml_camera_i2c_fig_s regs[]=
			{
			       {0x03, 0x20}, //Page 20
				{0x83, 0x04}, //EXP Normal 5.00 fps 
				{0x84, 0x93}, 
				{0x85, 0xe0}, 
				{0x86, 0x00}, //EXPMin 6000.00 fps
				{0x87, 0xfa}, 
				{0x88, 0x04}, //EXP Max 5.00 fps 
				{0x89, 0x93}, 
				{0x8a, 0xe0}, 
				{0x8B, 0x3a}, //EXP100 
				{0x8C, 0x98}, 
				{0x8D, 0x30}, //EXP120 
				{0x8E, 0xd4}, 
				{0x9c, 0x08}, //EXP Limit 666.67 fps 
				{0x9d, 0xca}, 
				{0x9e, 0x00}, //EXP Unit 
				{0x9f, 0xfa}, 
		
				{0xff , 0xff},
			};
		i=0;
		while (regs[i].addr!= 0xff && regs[i].val!= 0xff) {
			buf[0]=regs[i].addr;
			buf[1]=regs[i].val;
			i2c_put_byte_add8(client,buf, 2);
			i++;
		}


	} else {
		
		struct aml_camera_i2c_fig_s regs[]=
			{
				{0x03, 0x20}, //Page 20
				{0x83, 0x00}, //EXP Normal 33.33 fps 
				{0x84, 0xaf}, 
				{0x85, 0xc8}, 
				{0x86, 0x00}, //EXPMin 6000.00 fps
				{0x87, 0xfa}, 
				{0x88, 0x03}, //EXP Max 7.14 fps 
				{0x89, 0x34}, 
				{0x8a, 0x50}, 
				{0x8B, 0x3a}, //EXP100 
				{0x8C, 0x98}, 
				{0x8D, 0x30}, //EXP120 
				{0x8E, 0xd4}, 
				{0x9c, 0x08}, //EXP Limit 666.67 fps 
				{0x9d, 0xca}, 
				{0x9e, 0x00}, //EXP Unit 
				{0x9f, 0xfa}, 
				{0xff , 0xff},
			};
		i=0;
		while (regs[i].addr!= 0xff && regs[i].val!= 0xff) {
			buf[0]=regs[i].addr;
			buf[1]=regs[i].val;
			i2c_put_byte_add8(client,buf, 2);
			i++;
		}
	}
#endif
}
