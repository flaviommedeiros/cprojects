void set_HI704_param_effect(struct HI704_device *dev,enum camera_effect_flip_e para)//ÌØÐ§ÉèÖÃ
{
	struct i2c_client *client = v4l2_get_subdevdata(&dev->sd);
	unsigned char buf[4];
	int i;
	#if 1
	switch (para) {
	case CAM_EFFECT_ENC_NORMAL:
		{
			struct aml_camera_i2c_fig_s regs[]=
				{
					{0x03,0x10},
					{0x11,0x43},
					{0x12,0X30},                           
					{0x13,0x00},                            
					{0x44,0x80},                                        
					{0x45,0x80},                                    
					{0x47,0x7f}, 
					{0xff,0xff},
				};
				i=0;
			while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
			{
				buf[0]=regs[i].addr;
				buf[1]=regs[i].val;
				i2c_put_byte_add8(client,buf, 2);
				i++;
			}
		}

		break;
	case CAM_EFFECT_ENC_GRAYSCALE:
		{
			struct aml_camera_i2c_fig_s regs[]=
				{
					{0x03 , 0x10},
					{0x11 , 0x03},
					{0x12 , 0x03},
					{0x13 , 0x02},
					{0x40 , 0x00},
					{0x44 , 0x80},
					{0x45 , 0x80},
					{0xff , 0xff},
				};
				i=0;
			while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
			{
				buf[0]=regs[i].addr;
				buf[1]=regs[i].val;
				i2c_put_byte_add8(client,buf, 2);
				i++;
			}
		}
	    
	  

		break;
	case CAM_EFFECT_ENC_SEPIA:
		{
			struct aml_camera_i2c_fig_s regs[]=
				{
					{0x03 , 0x10},
					{0x11 , 0x03},
					{0x12 , 0x33},
					{0x13 , 0x02},
					{0x44 , 0x70},
					{0x45 , 0x98},
					{0xff , 0xff},
				};
				i=0;
			while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
			{
				buf[0]=regs[i].addr;
				buf[1]=regs[i].val;
				i2c_put_byte_add8(client,buf, 2);
				i++;
			}
		}

		break;
	case CAM_EFFECT_ENC_COLORINV:
		{
			struct aml_camera_i2c_fig_s regs[]=
				{
					{0x03 , 0x10},
					{0x11 , 0x03},
					{0x12 , 0x08},
					{0x13 , 0x02},
					{0x14 , 0x00},
					{0xff , 0xff},
				};
				i=0;
			while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
			{
				buf[0]=regs[i].addr;
				buf[1]=regs[i].val;
				i2c_put_byte_add8(client,buf, 2);
				i++;
			}
		}
		
		break;
	case CAM_EFFECT_ENC_SEPIAGREEN:
		{
			struct aml_camera_i2c_fig_s regs[]=
				{
					{0x03 , 0x10},
					{0x11 , 0x03},
					{0x12 , 0x03},
					{0x40 , 0x00},
					{0x13 , 0x02},
					{0x44 , 0x30},
					{0x45 , 0x50},
					{0xff , 0xff},
				};
				i=0;
			while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
			{
				buf[0]=regs[i].addr;
				buf[1]=regs[i].val;
				i2c_put_byte_add8(client,buf, 2);
				i++;
			}
		}
		break;
	case CAM_EFFECT_ENC_SEPIABLUE:
		{
			struct aml_camera_i2c_fig_s regs[]=
				{
					{0x03 , 0x10},
					{0x11 , 0x03},
					{0x12 , 0x03},
					{0x40 , 0x00},
					{0x13 , 0x02},
					{0x44 , 0xb0},
					{0x45 , 0x40},
					{0xff , 0xff},
				};
				i=0;
			while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
			{
				buf[0]=regs[i].addr;
				buf[1]=regs[i].val;
				i2c_put_byte_add8(client,buf, 2);
				i++;
			}
		}

		break;
	default:
		break;
	}
#endif
}
