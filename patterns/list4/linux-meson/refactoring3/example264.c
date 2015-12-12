switch(minor_cmd)
			{
				#ifdef CONFIG_IOL
				case 0x04: //LLT table initialization test
				{
					u8 page_boundary = 0xf9;
					{
						struct xmit_frame	*xmit_frame;

						if((xmit_frame=rtw_IOL_accquire_xmit_frame(padapter)) == NULL) {
							ret = -ENOMEM;	
							break;
						}
						
						rtw_IOL_append_LLT_cmd(xmit_frame, page_boundary);


						if(_SUCCESS != rtw_IOL_exec_cmds_sync(padapter, xmit_frame, 500,0) )
							ret = -EPERM;
					}
				}
					break;
				case 0x05: //blink LED test
				{
					u16 reg = 0x4c;
					u32 blink_num = 50;
					u32 blink_delay_ms = 200;
					int i;
					
					{
						struct xmit_frame	*xmit_frame;

						if((xmit_frame=rtw_IOL_accquire_xmit_frame(padapter)) == NULL) {
							ret = -ENOMEM;	
							break;
						}

						for(i=0;i<blink_num;i++){
							#ifdef CONFIG_IOL_NEW_GENERATION
							rtw_IOL_append_WB_cmd(xmit_frame, reg, 0x00,0xff);
							rtw_IOL_append_DELAY_MS_cmd(xmit_frame, blink_delay_ms);
							rtw_IOL_append_WB_cmd(xmit_frame, reg, 0x08,0xff);
							rtw_IOL_append_DELAY_MS_cmd(xmit_frame, blink_delay_ms);
							#else
							rtw_IOL_append_WB_cmd(xmit_frame, reg, 0x00);
							rtw_IOL_append_DELAY_MS_cmd(xmit_frame, blink_delay_ms);
							rtw_IOL_append_WB_cmd(xmit_frame, reg, 0x08);
							rtw_IOL_append_DELAY_MS_cmd(xmit_frame, blink_delay_ms);
							#endif
						}
						if(_SUCCESS != rtw_IOL_exec_cmds_sync(padapter, xmit_frame, (blink_delay_ms*blink_num*2)+200,0) )
							ret = -EPERM;
					}
				}
					break;
					
				case 0x06: //continuous wirte byte test
				{
					u16 reg = arg;
					u16 start_value = 0;
					u32 write_num = extra_arg;
					int i;
					u8 final;
					
					{
						struct xmit_frame	*xmit_frame;

						if((xmit_frame=rtw_IOL_accquire_xmit_frame(padapter)) == NULL) {
							ret = -ENOMEM;	
							break;
						}

						for(i=0;i<write_num;i++){
							#ifdef CONFIG_IOL_NEW_GENERATION
							rtw_IOL_append_WB_cmd(xmit_frame, reg, i+start_value,0xFF);
							#else
							rtw_IOL_append_WB_cmd(xmit_frame, reg, i+start_value);
							#endif
						}
						if(_SUCCESS != rtw_IOL_exec_cmds_sync(padapter, xmit_frame, 5000,0))
							ret = -EPERM;
					}

					if(start_value+write_num-1 == (final=rtw_read8(padapter, reg)) ) {
						DBG_871X("continuous IOL_CMD_WB_REG to 0x%x %u times Success, start:%u, final:%u\n", reg, write_num, start_value, final);
					} else {
						DBG_871X("continuous IOL_CMD_WB_REG to 0x%x %u times Fail, start:%u, final:%u\n", reg, write_num, start_value, final);
					}
				}
					break;
					
				case 0x07: //continuous wirte word test
				{
					u16 reg = arg;
					u16 start_value = 200;
					u32 write_num = extra_arg;
				
					int i;
					u16 final;

					{
						struct xmit_frame	*xmit_frame;

						if((xmit_frame=rtw_IOL_accquire_xmit_frame(padapter)) == NULL) {
							ret = -ENOMEM;	
							break;
						}

						for(i=0;i<write_num;i++){
							#ifdef CONFIG_IOL_NEW_GENERATION
							rtw_IOL_append_WW_cmd(xmit_frame, reg, i+start_value,0xFFFF);
							#else
							rtw_IOL_append_WW_cmd(xmit_frame, reg, i+start_value);
							#endif
						}
						if(_SUCCESS !=rtw_IOL_exec_cmds_sync(padapter, xmit_frame, 5000,0))
							ret = -EPERM;
					}

					if(start_value+write_num-1 == (final=rtw_read16(padapter, reg)) ) {
						DBG_871X("continuous IOL_CMD_WW_REG to 0x%x %u times Success, start:%u, final:%u\n", reg, write_num, start_value, final);
					} else {
						DBG_871X("continuous IOL_CMD_WW_REG to 0x%x %u times Fail, start:%u, final:%u\n", reg, write_num, start_value, final);
					}
				}
					break;
					
				case 0x08: //continuous wirte dword test
				{
					u16 reg = arg;
					u32 start_value = 0x110000c7;
					u32 write_num = extra_arg;
				
					int i;
					u32 final;

					{
						struct xmit_frame	*xmit_frame;

						if((xmit_frame=rtw_IOL_accquire_xmit_frame(padapter)) == NULL) {
							ret = -ENOMEM;	
							break;
						}

						for(i=0;i<write_num;i++){
							#ifdef CONFIG_IOL_NEW_GENERATION
							rtw_IOL_append_WD_cmd(xmit_frame, reg, i+start_value,0xFFFFFFFF);
							#else
							rtw_IOL_append_WD_cmd(xmit_frame, reg, i+start_value);
							#endif
						}
						if(_SUCCESS !=rtw_IOL_exec_cmds_sync(padapter, xmit_frame, 5000,0))
							ret = -EPERM;
							
					}

					if(start_value+write_num-1 == (final=rtw_read32(padapter, reg)) ) {
						DBG_871X("continuous IOL_CMD_WD_REG to 0x%x %u times Success, start:%u, final:%u\n", reg, write_num, start_value, final);
					} else {
						DBG_871X("continuous IOL_CMD_WD_REG to 0x%x %u times Fail, start:%u, final:%u\n", reg, write_num, start_value, final);
					}
				}
					break;
				#endif //CONFIG_IOL
			}
