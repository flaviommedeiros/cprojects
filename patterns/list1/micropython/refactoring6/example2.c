if ( (SL_OPCODE_SOCKET_RECVASYNCRESPONSE == Opcode) || (SL_OPCODE_SOCKET_RECVFROMASYNCRESPONSE == Opcode) 
#ifndef SL_TINY_EXT                      
                    || (SL_OPCODE_SOCKET_RECVFROMASYNCRESPONSE_V6 == Opcode) 
#endif                    
                 ) 
		{
			RxMsgClass = RECV_RESP_CLASS;
		}
		else
		{
            /* This is Async Event class message */
            RxMsgClass = ASYNC_EVT_CLASS;
        
		    /* Despite the fact that 4 bits are allocated in the SILO field, we actually have only 6 SILOs
		      So we can use the 8 options of SILO in look up table */
		    Silo = ((Opcode >> SL_OPCODE_SILO_OFFSET) & 0x7);

            VERIFY_PROTOCOL(Silo < (sizeof(RxMsgClassLUT)/sizeof(_SlSpawnEntryFunc_t)));

            /* Set the async event hander according to the LUT */
            AsyncEvtHandler = RxMsgClassLUT[Silo];
            
            if ((SL_OPCODE_NETAPP_HTTPGETTOKENVALUE == Opcode) || (SL_OPCODE_NETAPP_HTTPPOSTTOKENVALUE == Opcode))
            {
                AsyncEvtHandler = _SlDrvNetAppEventHandler;
            }
#ifndef SL_TINY_EXT            
            else if (SL_OPCODE_NETAPP_PINGREPORTREQUESTRESPONSE == Opcode)
            {
                AsyncEvtHandler = (_SlSpawnEntryFunc_t)_sl_HandleAsync_PingResponse;
            }
#endif
		}
