void gc2015_set_param_banding(struct gc2015_device *dev,enum  camera_banding_flip_e banding)
{
    struct i2c_client *client = v4l2_get_subdevdata(&dev->sd);
	unsigned char buf[4];
	#if 1
	switch(banding)
		{

		case CAM_BANDING_50HZ:

			buf[0]=0xfe;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x05;
			buf[1]=0x01;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x06;
			buf[1]=0xc1;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x07;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);
			
			buf[0]=0x08;
			buf[1]=0x40;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0xfe;
			buf[1]=0x01;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x29;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x2a;
			buf[1]=0x80;  //step
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x2b;
			buf[1]=0x05;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x2c;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x2d;
			buf[1]=0x06;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x2e;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x2f;
			buf[1]=0x08;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x30;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x31;
			buf[1]=0x09;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x32;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0xfe;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);
			break;
		case CAM_BANDING_60HZ:

			buf[0]=0xfe;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x05;
			buf[1]=0x01;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x06;
			buf[1]=0xd9;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x07;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);
			
			buf[0]=0x08;
			buf[1]=0x20;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0xfe;
			buf[1]=0x01;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x29;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x2a;
			buf[1]=0x68;  //step
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x2b;
			buf[1]=0x04;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x2c;
			buf[1]=0xe0;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x2d;
			buf[1]=0x05;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x2e;
			buf[1]=0xb0;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x2f;
			buf[1]=0x06;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x30;
			buf[1]=0xe8;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x31;
			buf[1]=0x08;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0x32;
			buf[1]=0x20;
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0xfe;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);
	             			
			break;
		    default:
		    	break;

		}
	#endif	
}
