switch (ani_msg_type)
      {
         case PTT_MSG_READ_REGISTER:
            reg_addr = *(v_U32_t*) ((char*)wmsg + 8);
            PTT_TRACE(VOS_TRACE_LEVEL_INFO, "%s: PTT_MSG_READ_REGISTER [0x%08lX]\n",
               __FUNCTION__, reg_addr);
            vosStatus = sme_DbgReadRegister(pAdapterHandle->hHal, reg_addr, &reg_val);
            *(v_U32_t*) ((char*)wmsg + 12) = reg_val;
            if(vosStatus != VOS_STATUS_SUCCESS)
               PTT_TRACE(VOS_TRACE_LEVEL_ERROR, "%s: Read Register [0x%08lX] failed!!\n",
               __FUNCTION__, reg_addr);
            ptt_sock_send_msg_to_app(wmsg, 0, ANI_NL_MSG_PUMAC, wnl->nlh.nlmsg_pid);
            break;
         case PTT_MSG_WRITE_REGISTER:
            reg_addr = *(v_U32_t*) ((const unsigned char*)wmsg + 8);
            reg_val = *(v_U32_t*)((const unsigned char*)wmsg + 12);
            PTT_TRACE(VOS_TRACE_LEVEL_INFO, "%s: PTT_MSG_WRITE_REGISTER Addr [0x%08lX] value [0x%08lX]\n",
               __FUNCTION__, reg_addr, reg_val);
            vosStatus = sme_DbgWriteRegister(pAdapterHandle->hHal, reg_addr, reg_val);
            if(vosStatus != VOS_STATUS_SUCCESS)
            {
               PTT_TRACE(VOS_TRACE_LEVEL_ERROR, "%s: Write Register [0x%08lX] value [0x%08lX] failed!!\n",
                  __FUNCTION__, reg_addr, reg_val);
            }
            //send message to the app
            ptt_sock_send_msg_to_app(wmsg, 0, ANI_NL_MSG_PUMAC, wnl->nlh.nlmsg_pid);
            break;
         case PTT_MSG_READ_MEMORY:
            reg_addr = *(v_U32_t*) ((char*)wmsg + 8);
            len_payload = *(v_U32_t*) ((char*)wmsg + 12);
            PTT_TRACE(VOS_TRACE_LEVEL_INFO, "%s: PTT_MSG_READ_MEMORY addr [0x%08lX] bytes [0x%08lX]\n",
               __FUNCTION__, reg_addr, len_payload);
            buf = (v_U8_t*)wmsg + 16;
            vosStatus = sme_DbgReadMemory(pAdapterHandle->hHal, reg_addr, buf, len_payload);
            if(vosStatus != VOS_STATUS_SUCCESS) {
               PTT_TRACE(VOS_TRACE_LEVEL_ERROR, "%s: Memory read failed for [0x%08lX]!!\n",
                  __FUNCTION__, reg_addr);
            }
            ptt_sock_swap_32(buf, len_payload);
            //send message to the app
            ptt_sock_send_msg_to_app(wmsg, 0, ANI_NL_MSG_PUMAC, wnl->nlh.nlmsg_pid);
            break;
         case PTT_MSG_WRITE_MEMORY:
            reg_addr = *(v_U32_t*) ((char*)wmsg + 8);
            len_payload = *(v_U32_t*) ((char*)wmsg + 12);
            PTT_TRACE(VOS_TRACE_LEVEL_INFO, "%s: PTT_MSG_DBG_WRITE_MEMORY addr [0x%08lX] bytes [0x%08lX]\n",
               __FUNCTION__, reg_addr, len_payload);
            buf = (v_U8_t*)wmsg + 16;
            ptt_sock_swap_32(buf, len_payload);
            vosStatus = sme_DbgWriteMemory(pAdapterHandle->hHal, reg_addr, buf, len_payload);
            if(vosStatus != VOS_STATUS_SUCCESS)
            {
               PTT_TRACE(VOS_TRACE_LEVEL_ERROR, "%s: Memory write failed for addr [0x%08lX]!!\n",
                  __FUNCTION__, reg_addr);
            }
            //send message to the app
            ptt_sock_send_msg_to_app(wmsg, 0, ANI_NL_MSG_PUMAC, wnl->nlh.nlmsg_pid);
            break;
         case PTT_MSG_LOG_DUMP_DBG:
            cmd = *(unsigned int *) ((char *)wmsg + 8);
            arg1 = *(unsigned int *) ((char *)wmsg + 12);
            arg2 = *(unsigned int *) ((char *)wmsg + 16);
            arg3 = *(unsigned int *) ((char *)wmsg + 20);
            arg4 = *(unsigned int *) ((char *)wmsg + 24);
            PTT_TRACE(VOS_TRACE_LEVEL_INFO, "%s: PTT_MSG_LOG_DUMP_DBG %d arg1 %d arg2 %d arg3 %d arg4 %d\n",
               __FUNCTION__, cmd, arg1, arg2, arg3, arg4);
#ifdef FEATURE_WLAN_NON_INTEGRATED_SOC
            // FIXME_PRIMA -- need logDump() replacement
            logPrintf(pAdapterHandle->hHal, cmd, arg1, arg2, arg3, arg4);
#endif //FEATURE_WLAN_NON_INTEGRATED_SOC
            //send message to the app
            ptt_sock_send_msg_to_app(wmsg, 0, ANI_NL_MSG_PUMAC, wnl->nlh.nlmsg_pid);
            break;
#ifdef ANI_MANF_DIAG
         case PTT_MSG_FTM_CMDS_TYPE:
            wlan_hdd_process_ftm_cmd(pAdapterHandle,wnl);
            break;
#endif
         default:
            PTT_TRACE(VOS_TRACE_LEVEL_ERROR, "%s: Unknown ANI Msg [0x%X], length [0x%X]\n",
               __FUNCTION__, ani_msg_type, be16_to_cpu(wmsg->length ));
            break;
      }
