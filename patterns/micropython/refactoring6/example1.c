if (
#ifndef SL_TINY_EXT               
                (SL_OPCODE_SOCKET_ACCEPTASYNCRESPONSE == OpCode) || 
                (SL_OPCODE_SOCKET_ACCEPTASYNCRESPONSE_V6 == OpCode) || 
#endif                
                (SL_OPCODE_SOCKET_CONNECTASYNCRESPONSE == OpCode)
               )
			{
				/* go over the active list if exist to find obj waiting for this Async event */
				sd = ((((_SocketResponse_t *)(pAsyncBuf + _SL_RESP_HDR_SIZE))->sd) & BSD_SOCKET_ID_MASK);
			}
