void HI253_set_param_exposure(struct hi253_device *dev,enum camera_exposure_e para)
{
	struct i2c_client *client = v4l2_get_subdevdata(&dev->sd);
   #if 1

    switch (para)
	{
		

		case EXPOSURE_N4_STEP:	
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x10},
						{0x40 , 0xc0},
						{0xff , 0xff},
					};
				int i=0;
				unsigned char buf[2];
				while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
				{
					buf[0]=regs[i].addr;
					buf[1]=regs[i].val;
					i2c_put_byte_add8(client,buf, 2);
					i++;
				}
			}
			break;
			
		case EXPOSURE_N3_STEP:
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x10},
						{0x40 , 0xa0},
						{0xff , 0xff},
					};
				int i=0;
				unsigned char buf[2];
				while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
				{
					buf[0]=regs[i].addr;
					buf[1]=regs[i].val;
					i2c_put_byte_add8(client,buf, 2);
					i++;
				}
			}
			break;
			
		case EXPOSURE_N2_STEP:
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x10},
						{0x40 , 0x90},
						{0xff , 0xff},
					};
				int i=0;
				unsigned char buf[2];
				while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
				{
					buf[0]=regs[i].addr;
					buf[1]=regs[i].val;
					i2c_put_byte_add8(client,buf, 2);
					i++;
				}
			}
			break;
			
		case EXPOSURE_N1_STEP:
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x10},
						{0x40 , 0x88},
						{0xff , 0xff},
					};
				int i=0;
				unsigned char buf[2];
				while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
				{
					buf[0]=regs[i].addr;
					buf[1]=regs[i].val;
					i2c_put_byte_add8(client,buf, 2);
					i++;
				}
			}
			break;
			
		case EXPOSURE_0_STEP:
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x10},
						{0x40 , 0x80},
						{0xff , 0xff},
					};
				int i=0;
				unsigned char buf[2];
				while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
				{
					buf[0]=regs[i].addr;
					buf[1]=regs[i].val;
					i2c_put_byte_add8(client,buf, 2);
					i++;
				}
			}
			break;
			
		case EXPOSURE_P1_STEP:
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x10},
						{0x40 , 0x08},
						{0xff , 0xff},
					};
				int i=0;
				unsigned char buf[2];
				while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
				{
					buf[0]=regs[i].addr;
					buf[1]=regs[i].val;
					i2c_put_byte_add8(client,buf, 2);
					i++;
				}
			}
			break;
			
		case EXPOSURE_P2_STEP:
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x10},
						{0x40 , 0x10},
						{0xff , 0xff},
					};
				int i=0;
				unsigned char buf[2];
				while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
				{
					buf[0]=regs[i].addr;
					buf[1]=regs[i].val;
					i2c_put_byte_add8(client,buf, 2);
					i++;
				}
			}
			break;
			
		case EXPOSURE_P3_STEP:
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x10},
						{0x40 , 0x20},
						{0xff , 0xff},
					};
				int i=0;
				unsigned char buf[2];
				while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
				{
					buf[0]=regs[i].addr;
					buf[1]=regs[i].val;
					i2c_put_byte_add8(client,buf, 2);
					i++;
				}
			}
			break;
			
		case EXPOSURE_P4_STEP:	
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x10},
						{0x40 , 0x30},
						{0xff , 0xff},
					};
				int i=0;
				unsigned char buf[2];
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
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x10},
						{0x40 , 0x40},
						{0xff , 0xff},
					};
				int i=0;
				unsigned char buf[2];
				while (regs[i].addr!= 0xff && regs[i].val!= 0xff)
				{
					buf[0]=regs[i].addr;
					buf[1]=regs[i].val;
					i2c_put_byte_add8(client,buf, 2);
					i++;
				}
			}
			break;


		
	}
#endif

}
