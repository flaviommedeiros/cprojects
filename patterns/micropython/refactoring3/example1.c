switch(OpCode)
            {
            case SL_OPCODE_SOCKET_RECVFROMASYNCRESPONSE:
                ExpArgSize = RECVFROM_IPV4_ARGS_SIZE;
                break;
#ifndef SL_TINY_EXT                        
            case SL_OPCODE_SOCKET_RECVFROMASYNCRESPONSE_V6:
                ExpArgSize = RECVFROM_IPV6_ARGS_SIZE;
                break;
#endif                        
            default:
                /* SL_OPCODE_SOCKET_RECVASYNCRESPONSE: */
                ExpArgSize = RECV_ARGS_SIZE;
            }
