switch(to->sa_family)
    {
        case SL_AF_INET:
            CmdCtrl.Opcode = SL_OPCODE_SOCKET_SENDTO;
            CmdCtrl.TxDescLen = sizeof(_SocketAddrIPv4Command_t);
            break;
#ifndef SL_TINY_EXT            
        case SL_AF_INET6_EUI_48:
            CmdCtrl.Opcode = SL_OPCODE_SOCKET_BIND_V6;
            CmdCtrl.TxDescLen = sizeof(_SocketAddrIPv6EUI48Command_t);
        	break;        
#ifdef SL_SUPPORT_IPV6
        case AF_INET6:
            CmdCtrl.Opcode = SL_OPCODE_SOCKET_SENDTO_V6;
            CmdCtrl.TxDescLen = sizeof(_SocketAddrIPv6Command_t);
            break;
#endif
#endif
        case SL_AF_RF:
        default:
            return SL_RET_CODE_INVALID_INPUT;
    }
