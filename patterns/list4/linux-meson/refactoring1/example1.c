if(r_buf[0] == STK_ACC_CALI_VER0 && r_buf[1] == STK_ACC_CALI_VER1)
		{
			offset[0] = r_buf[2];
			offset[1] = r_buf[3];
			offset[2] = r_buf[4];
			mode = r_buf[5];
			STK831x_SetOffset(offset);
#ifdef STK_TUNE			
			stk_tune_offset_record[0] = offset[0];
			stk_tune_offset_record[1] = offset[1];
			stk_tune_offset_record[2] = offset[2];
#endif 			
			printk(KERN_INFO "%s: set offset:%d,%d,%d, mode=%d\n", __func__, offset[0], offset[1], offset[2], mode);
			atomic_set(&stk->cali_status, mode);								
		}
		else
		{
			printk(KERN_ERR "%s: cali version number error! r_buf=0x%x,0x%x,0x%x,0x%x,0x%x\n", 
				__func__, r_buf[0], r_buf[1], r_buf[2], r_buf[3], r_buf[4]);						
			//return -EINVAL;
		}
#endif
