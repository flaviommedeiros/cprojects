void set_HI704_param_wb(struct HI704_device *dev,enum  camera_wb_flip_e para)
{
//	kal_uint16 rgain=0x80, ggain=0x80, bgain=0x80;
	struct i2c_client *client = v4l2_get_subdevdata(&dev->sd);

	unsigned char buf[4];
	int i=0;

	//unsigned char  temp_reg;
	//temp_reg=HI704_read_byte(0x22);
	//buf[0]=0x22;
	//temp_reg=i2c_get_byte_add8(client,buf);

	printk(" camera set_HI704_param_wb=%d. \n ",para);
	
	#if 1
	switch (para) {
	case CAM_WB_AUTO:
		{
			struct aml_camera_i2c_fig_s regs[]=
				{
					{0x03 , 0x22},
					{0x10 , 0xea},
					{0x80 , 0x30},
					{0x81 , 0x28},
					{0x82 , 0x30},
					{0x83 , 0x55},
					{0x84 , 0x16},
					{0x85 , 0x53},
					{0x86 , 0x25},
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

	case CAM_WB_CLOUD:
		{
			struct aml_camera_i2c_fig_s regs[]=
				{
					{0x03, 0x22},  									   
					{0x10, 0x6a},
					{0x80, 0x50},
					{0x81, 0x20}, 
					{0x82, 0x24}, 
					{0x83, 0x6d},
					{0x84, 0x65}, 
					{0x85, 0x24}, 
					{0x86, 0x1c},   
					{0xff, 0xff}    
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

	case CAM_WB_DAYLIGHT:   
		{
			struct aml_camera_i2c_fig_s regs[]=
				{
					{0x03, 0x22},  									   
					{0x10, 0x6a},
					{0x80, 0x40},
					{0x81, 0x20}, 
					{0x82, 0x28}, 
					{0x83, 0x45},
					{0x84, 0x35}, 
					{0x85, 0x2d}, 
					{0x86, 0x1c},   
					{0xff, 0xff}    
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

	case CAM_WB_INCANDESCENCE:   // bai re guang
		{
			struct aml_camera_i2c_fig_s regs[]=
				{
					{0x03, 0x22},									   
					{0x10, 0x6a},
					{0x80, 0x35},
					{0x81, 0x20}, 
					{0x82, 0x32}, 
					{0x83, 0x3c},
					{0x84, 0x2c}, 
					{0x85, 0x45}, 
					{0x86, 0x35}, 
					{0xff, 0xff}    
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

	case CAM_WB_FLUORESCENT:  
		{
			struct aml_camera_i2c_fig_s regs[]=
				{
					{0x03, 0x22}, 									   
					{0x10, 0x6a},
					{0x80, 0x23},
					{0x81, 0x20}, 
					{0x82, 0x3d}, 
					{0x83, 0x2e},
					{0x84, 0x24}, 
					{0x85, 0x43}, 
					{0x86, 0x3d},   
					{0xff, 0xff}    
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

	case CAM_WB_TUNGSTEN:   
		{
			struct aml_camera_i2c_fig_s regs[]=
				{
					{0x03, 0x22},  		//U30							   
					{0x10, 0x6a},
					{0x80, 0x58},
					{0x81, 0x10}, 
					{0x82, 0x70}, 
					{0x83, 0x58},
					{0x84, 0x10}, 
					{0x85, 0x70}, 
					{0x86, 0x10},   
					{0xff, 0xff}  
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

	case CAM_WB_MANUAL:
		// TODO
		break;
	default:
		break;
	}
	#endif
//	kal_sleep_task(20);
}
