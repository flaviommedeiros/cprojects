void set_GC0328_param_wb(struct gc0328_device *dev,enum  camera_wb_flip_e para)
{
//	kal_uint16 rgain=0x80, ggain=0x80, bgain=0x80;
	struct i2c_client *client = v4l2_get_subdevdata(&dev->sd);

	unsigned char buf[4];

	unsigned char  temp_reg;
	//temp_reg=gc0328_read_byte(0x22);
	buf[0]=0x42;
	temp_reg=i2c_get_byte_add8(client,0x42);

	printk(" camera set_GC0328_param_wb=%d. \n ",para);
	switch (para)
	{
		case CAM_WB_AUTO:
		    #if 0
		    buf[0]=0x77;
		    buf[1]=0x60;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x78;
		    buf[1]=0x40;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x79;
		    buf[1]=0x60;
		    i2c_put_byte_add8(client,buf,2);
		    #endif
		    buf[0]=0x42;
		    buf[1]=temp_reg|0x02;
		    i2c_put_byte_add8(client,buf,2);
		    break;

		case CAM_WB_CLOUD:
                    buf[0]=0x42;
        	    buf[1]=temp_reg&~0x02;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x77;
		    buf[1]=0x58;//0x8c;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x78;
		    buf[1]=0x40;//0x50;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x79;
		    buf[1]=0x58;//0x40;
		    i2c_put_byte_add8(client,buf,2);
		    break;

		case CAM_WB_DAYLIGHT:   // tai yang guang
                    buf[0]=0x42;
		    buf[1]=temp_reg&~0x02;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x77;
		    buf[1]=0x70;//0x74;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x78;
		    buf[1]=0x40;//0x52;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x79;
		    buf[1]=0x50;//0x40;
		    i2c_put_byte_add8(client,buf,2);
		    break;

		case CAM_WB_INCANDESCENCE:   // bai re guang
                    buf[0]=0x42;
		    buf[1]=temp_reg&~0x02;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x77;
		    buf[1]=0x50;//0x48;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x78;
		    buf[1]=0x40;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x79;
		    buf[1]=0xa8;//0x5c;
		    i2c_put_byte_add8(client,buf,2);
		    break;

		case CAM_WB_FLUORESCENT:   //ri guang deng
                    buf[0]=0x42;
		    buf[1]=temp_reg&~0x02;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x77;
		    buf[1]=0x72;//0x40;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x78;
		    buf[1]=0x40;//0x42;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x79;
		    buf[1]=0x5b;//0x50;
		    i2c_put_byte_add8(client,buf,2);
		    break;

	       /*case CAM_WB_WARM_FLUORESCENT://CAM_WB_TUNGSTEN:   // wu si deng
		    buf[0]=0x42;
		    buf[1]=temp_reg&~0x02;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x77;
		    buf[1]=0x40;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x78;
		    buf[1]=0x54;
		    i2c_put_byte_add8(client,buf,2);
		    buf[0]=0x79;
		    buf[1]=0x70;
		    i2c_put_byte_add8(client,buf,2);
		    break;

		case CAM_WB_MANUAL:
			// TODO
			break;

		case CAM_WB_SHADE:
			// TODO
			break;

		case CAM_WB_TWILIGHT:
			// TODO
			break;*/
		default:
			break;
	}
//	kal_sleep_task(20);
}
