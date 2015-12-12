#ifdef _SUPPORT_TOUCH_AMPLITUDE_
if(read_mem(message_processor_address, 7, quantum_msg) == READ_MEM_OK)
    #else
        if(read_mem(message_processor_address, 6, quantum_msg) == READ_MEM_OK)
    #endif
        {
            /* Call the main application to handle the message. */

#if defined(CONFIG_MACH_ANCORA) || defined(CONFIG_MACH_GODART)
            if( quantum_msg[0] == 0xC ){
				if(quantum_msg[2] == 0x2 ){
					touch_key_value = SET_TOUCH_KEY_MENU;
					input_report_key(qt602240->input_dev, KEY_MENU, 1);
					}
				else if(quantum_msg[2] == 0x1){
					touch_key_value = SET_TOUCH_KEY_BACK;
					input_report_key(qt602240->input_dev, KEY_BACK, 1);
					}
				else{
					if ( touch_key_value == SET_TOUCH_KEY_MENU)
						input_report_key(qt602240->input_dev, KEY_MENU, 0);
					else if ( touch_key_value == SET_TOUCH_KEY_BACK )
						input_report_key(qt602240->input_dev, KEY_BACK, 0);
					touch_key_value = 0;
					}
            	}
#endif

            //20102017 julia			
            if( quantum_msg[0] == 14 ) {
                if((quantum_msg[1]&0x01) == 0x00) { 
                    for ( i= 0; i<MAX_USING_FINGER_NUM; ++i ) {
                        if ( fingerInfo[i].pressure == -1 ) continue;

                        if(i == 0) {
                            touch_state_val=0;
                        }
                        fingerInfo[i].pressure= 0;

                        input_report_abs(qt602240->input_dev, ABS_MT_POSITION_X, fingerInfo[i].x);
                        input_report_abs(qt602240->input_dev, ABS_MT_POSITION_Y, fingerInfo[i].y);
                        input_report_abs(qt602240->input_dev, ABS_MT_PRESSURE, fingerInfo[i].pressure);    // 0ÀÌ¸é Release, ¾Æ´Ï¸é Press »óÅÂ(Down or Move)
                        input_report_abs(qt602240->input_dev, ABS_MT_TOUCH_MAJOR, fingerInfo[i].size);
                        input_report_abs(qt602240->input_dev, ABS_MT_TRACKING_ID, i); // i = Finger ID
                        input_mt_sync(qt602240->input_dev);

                        if ( fingerInfo[i].pressure == 0 ) fingerInfo[i].pressure= -1;
                        else if( fingerInfo[i].pressure > 0 ) one_touch_input_flag++;//hugh 0312
                    }

                    input_report_key(qt602240->input_dev, BTN_TOUCH, one_touch_input_flag > 0);
                    input_sync(qt602240->input_dev);
                } else {
                    touch_message_flag = 1;
                    one_touch_input_flag = 1; //hugh 0312
                }
            }    

            if(quantum_msg[0] < 2  || quantum_msg[0] >= 12) {
            
                printk(KERN_DEBUG "[TSP] msg id =  %x %x %x %x %x %x %x %x %x\n", quantum_msg[0], quantum_msg[1], quantum_msg[2],\
                     quantum_msg[3], quantum_msg[4], quantum_msg[5], quantum_msg[6], quantum_msg[7], quantum_msg[8]);

                if((quantum_msg[0] == 1)&&((quantum_msg[1]&0x10) == 0x10)) {
                    printk(" [TSP] quantum_msg[0] = 1 and quantum_msg[1] = 0x10  cal_check_flag=1\n");
                }
                else if((quantum_msg[0] == 1) && ((quantum_msg[1]&0x10)==0)) {
                    printk(" [TSP] quantum_msg[0] = 1 and quantum_msg[1] = 0x00  cal_check_flag=2\n");
                    if(touch_message_flag && (cal_check_flag/*==2*/)) {
                        check_chip_calibration(1);
                    }
                }

                if ((quantum_msg[0] ==  14) ||(quantum_msg[0] == 0) ||(quantum_msg[0] == 0xFF)) {
                    if(touch_message_flag && (cal_check_flag/*==2*/)) {
                        check_chip_calibration(one_touch_input_flag);
                    }
                }
				enable_irq(qt602240->client->irq);
                return ;
            } 
            
#ifdef _SUPPORT_MULTITOUCH_
            id= quantum_msg[0] - 2;
#endif

#if defined(CONFIG_MACH_ANCORA) || defined(CONFIG_MACH_GODART)
	     y = quantum_msg[2];
            y = y << 2;
            y = y | quantum_msg[4] >> 6;

            x = quantum_msg[3];
            x = x << 2;
            x = x | ((quantum_msg[4] & 0x0C)  >> 2);

	     x = 480-(int16_t)x;
#else
            x = quantum_msg[2];
            x = x << 2;
            x = x | quantum_msg[4] >> 6;

            y = quantum_msg[3];
            y = y << 2;
            y = y | ((quantum_msg[4] & 0x0C)  >> 2);

#if defined(CONFIG_MACH_APACHE)	
            x = 480-(int16_t)x;
            y = 800-(int16_t)y;
#endif

#endif

            size = quantum_msg[5];
            /* 
             * quantum_msg[1] & 0x80 : 10000000 -> DETECT 
             * quantum_msg[1] & 0x40 : 01000000 -> PRESS
             * quantum_msg[1] & 0x20 : 00100000 -> RELEASE
             * quantum_msg[1] & 0x10 : 00010000 -> MOVE
             * quantum_msg[1] & 0x08 : 00001000 -> VECTOR
             * quantum_msg[1] & 0x04 : 00000100 -> AMP
             * quantum_msg[1] & 0x02 : 00000010 -> SUPPRESS
             */
#ifdef _SUPPORT_MULTITOUCH_
            if ( (quantum_msg[1] & 0x20 )) {    // Release
                fingerInfo[id].size= size;
                fingerInfo[id].pressure= 0;
                bChangeUpDn= 1;
		   touch_state_val = 0;
            }
            else if ( (quantum_msg[1] & 0x80) && (quantum_msg[1] & 0x40) ) {   // Detect & Press
                touch_message_flag = 1; //20100217 julia
                touch_state_val=1;
                fingerInfo[id].size= size;
#ifdef _SUPPORT_TOUCH_AMPLITUDE_
                fingerInfo[id].pressure= quantum_msg[6];
#else
                fingerInfo[id].pressure= 40;
#endif
                
				fingerInfo[id].x= (int16_t)x;
				fingerInfo[id].y= (int16_t)y;
#ifdef KERNEL_DEBUG_SEC
				printk("[TSP] x=%d, y=%d\n", fingerInfo[id].x, fingerInfo[id].y );
#endif
                bChangeUpDn= 1;
            }
            else if ( (quantum_msg[1] & 0x80) && (quantum_msg[1] & 0x10) ) {    // Detect & Move
                touch_message_flag = 1;
                fingerInfo[id].size= size;
#ifdef _SUPPORT_TOUCH_AMPLITUDE_
                fingerInfo[id].pressure= quantum_msg[6];
#endif
                fingerInfo[id].x= (int16_t)x;
                fingerInfo[id].y= (int16_t)y;
            }
#else             
            if( ((quantum_msg[1] & 0x80) == 0x80 ) && ((quantum_msg[1] & 0x40) == 0x40) ) {    // case 11000000 -> DETECT & PRESS
                press = 1;
                btn_report = 1;
                print_msg();
            }
            else if( ((quantum_msg[1] & 0x80) == 0x80 ) && ((quantum_msg[1] & 0x10) == 0x10) ) {    // case 10010000 -> DETECT & MOVE
                press = 1;
                print_msg();

            }
#if defined(CONFIG_MACH_ANCORA) || defined(CONFIG_MACH_GODART)
	     else if( ((quantum_msg[1] & 0x80) == 0x80 ) && ((quantum_msg[1] & 0x4) == 0x4) ) {    // case 10000100 -> DETECT & AMP
                press = 1;
                print_msg();

            }

	     else if( ((quantum_msg[1] & 0x80) == 0x80 ) && ((quantum_msg[1] & 0x8) == 0x8) ) {    // case 10001000 -> DETECT & VECTOR
                press = 1;
                print_msg();

            }
#endif
            else if( ((quantum_msg[1] & 0x20 ) == 0x20)) {  // case 00100000 -> RELEASE
                press = 0;
                print_msg();
                input_report_key(qt602240->input_dev, BTN_TOUCH, 0);
            }
#endif      

            else {
                press = 3;
                printk("[TSP]Unknown state 0x%x 0x%x!\n ", quantum_msg[0], quantum_msg[1]);
                //print_msg();
                //printk("\n");
            }

//printk("[TSP Key] x=%d, y=%d\n", x, y);


            ret_val = MESSAGE_READ_OK;
        }

        else
            printk("\n [TSP] read_mem is failed -- check your TSP chip!!\n\n");
