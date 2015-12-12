void HI253_set_param_wb(struct hi253_device *dev,enum  camera_wb_flip_e para)//white balance
{
	struct i2c_client *client = v4l2_get_subdevdata(&dev->sd);

	#if 1	

	switch (para)
	{
	
		
		case CAM_WB_AUTO://auto
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						/*{0x03 , 0x22},
						{0x11 , 0x2e},
						{0x80 , 0x30},
						{0x81 , 0x28},
						{0x82 , 0x30},
						{0x83 , 0x55},
						{0x84 , 0x16},
						{0x85 , 0x53},
						{0x86 , 0x53},
						{0xff , 0xff},*/
						{0x03 , 0x22},
						{0x11 , 0x2e},
						{0x80 , 0x30},
						{0x81 , 0x20},
						{0x82 , 0x3e},
						{0x83 , 0x53},
						{0x84 , 0x16},
						{0x85 , 0x5A},
						{0x86 , 0x25},
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

		case CAM_WB_CLOUD: //cloud
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x22},
						{0x11 , 0x28},
						{0x80 , 0x71},
						//{0x81 , 0x28},
						{0x82 , 0x2b},
						{0x83 , 0x72},
						{0x84 , 0x70},
						{0x85 , 0x2b},
						{0x86 , 0x28},
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

		case CAM_WB_DAYLIGHT: //
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x22},
						{0x11 , 0x28},
						{0x80 , 0x59},
						//{0x81 , 0x28},
						{0x82 , 0x29},
						{0x83 , 0x60},
						{0x84 , 0x50},
						{0x85 , 0x2f},
						{0x86 , 0x23},
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

		case CAM_WB_INCANDESCENCE: 
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x22},
						{0x11 , 0x28},
						{0x80 , 0x29},
						//{0x81 , 0x28},
						{0x82 , 0x54},
						{0x83 , 0x2e},
						{0x84 , 0x23},
						{0x85 , 0x58},
						{0x86 , 0x4f},
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
			
		case CAM_WB_TUNGSTEN: 
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x22},
						//{0x11 , 0x28},
						{0x80 , 0x24},
						{0x81 , 0x20},
						{0x82 , 0x58},
						{0x83 , 0x27},
						{0x84 , 0x22},
						{0x85 , 0x58},
						{0x86 , 0x52},
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

      	case CAM_WB_FLUORESCENT:
			{
				struct aml_camera_i2c_fig_s regs[]=
					{
						{0x03 , 0x22},
						{0x11 , 0x28},
						{0x80 , 0x41},
						//{0x81 , 0x20},
						{0x82 , 0x42},
						{0x83 , 0x44},
						{0x84 , 0x34},
						{0x85 , 0x46},
						{0x86 , 0x3a},
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

		case CAM_WB_MANUAL:
		    	// TODO
			break;
		default:
			break;
	}
	
#endif
}
