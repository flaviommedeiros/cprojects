switch (para)
	{
#if 1
		case CAM_WB_AUTO://auto
			buf[0]=0xfe;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);	
		    	printk("CAM_WB_AUTO       \n");
			buf[0]=0xb3;
			buf[1]=0x61;
			i2c_put_byte_add8(client,buf,2);		

			buf[0]=0xb4;
			buf[1]=0x40;
			i2c_put_byte_add8(client,buf,2);	

			buf[0]=0xb5;
			buf[1]=0x61;
			i2c_put_byte_add8(client,buf,2);	

		    buf[0]=0x82;
			buf[1]=temp | 0x02;
			i2c_put_byte_add8(client,buf,2);	
			break;

		case CAM_WB_CLOUD: //cloud

			buf[0]=0xfe;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);	
			
			printk("CAM_WB_CLOUD       \n");
			buf[0]=0x82;
			buf[1]=temp & (~0x02);
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0xb3;
			buf[1]=0x58;
			i2c_put_byte_add8(client,buf,2);		

			buf[0]=0xb4;
			buf[1]=0x40;
			i2c_put_byte_add8(client,buf,2);	

			buf[0]=0xb5;
			buf[1]=0x50;
			i2c_put_byte_add8(client,buf,2);			
			break;

		case CAM_WB_DAYLIGHT: //
			buf[0]=0xfe;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);	
			printk("CAM_WB_DAYLIGHT       \n");
			buf[0]=0x82;
			buf[1]=temp & (~0x02);
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0xb3;
			buf[1]=0x78;
			i2c_put_byte_add8(client,buf,2);		

			buf[0]=0xb4;
			buf[1]=0x40;
			i2c_put_byte_add8(client,buf,2);	

			buf[0]=0xb5;
			buf[1]=0x50;
			i2c_put_byte_add8(client,buf,2);
			break;

		case CAM_WB_INCANDESCENCE:
			buf[0]=0xfe;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);	
			
			printk("CAM_WB_INCANDESCENCE       \n");
			buf[0]=0x82;
			buf[1]=temp & (~0x02);
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0xb3;
			buf[1]=0x50;
			i2c_put_byte_add8(client,buf,2);		

			buf[0]=0xb4;
			buf[1]=0x40;
			i2c_put_byte_add8(client,buf,2);	

			buf[0]=0xb5;
			buf[1]=0xa8;
			i2c_put_byte_add8(client,buf,2);
			break;

		case CAM_WB_TUNGSTEN:
			buf[0]=0xfe;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);	
                     printk("CAM_WB_TUNGSTEN       \n");
			buf[0]=0x82;
			buf[1]=temp & (~0x02);
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0xb3;
			buf[1]=0xa0;
			i2c_put_byte_add8(client,buf,2);		

			buf[0]=0xb4;
			buf[1]=0x45;
			i2c_put_byte_add8(client,buf,2);	

			buf[0]=0xb5;
			buf[1]=0x40;
			i2c_put_byte_add8(client,buf,2);	
			break;

      	case CAM_WB_FLUORESCENT:

			buf[0]=0xfe;
			buf[1]=0x00;
			i2c_put_byte_add8(client,buf,2);	
			printk("CAM_WB_FLUORESCENT       \n");
 			buf[0]=0x82;
			buf[1]=temp & (~0x02);
			i2c_put_byte_add8(client,buf,2);

			buf[0]=0xb3;
			buf[1]=0x72;
			i2c_put_byte_add8(client,buf,2);		

			buf[0]=0xb4;
			buf[1]=0x40;
			i2c_put_byte_add8(client,buf,2);	

			buf[0]=0xb5;
			buf[1]=0x5b;
			i2c_put_byte_add8(client,buf,2);
			break;
#endif
		case CAM_WB_MANUAL:
		    	                      // TODO
			break;
			
		default:
			break;
	}
