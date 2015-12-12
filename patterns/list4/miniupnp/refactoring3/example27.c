switch (pcp_msg_info->opcode) {
		case PCP_OPCODE_MAP:

			remainingSize -= PCP_MAP_V1_SIZE;
			if (remainingSize < 0) {
				pcp_msg_info->result_code = PCP_ERR_MALFORMED_REQUEST;
				return pcp_msg_info->result_code;
			}

#ifdef DEBUG
			printMAPOpcodeVersion1(req);
#endif /* DEBUG */
			parsePCPMAP_version1(req, pcp_msg_info);

			req += PCP_MAP_V1_SIZE;

			parsePCPOptions(req, remainingSize, pcp_msg_info);
			if (ValidatePCPMsg(pcp_msg_info)) {
				if (pcp_msg_info->lifetime == 0) {
					DeletePCPMap(pcp_msg_info);
				} else {
					CreatePCPMap(pcp_msg_info);
				}
			} else {
				syslog(LOG_ERR, "PCP: Invalid PCP v1 MAP message.");
				return pcp_msg_info->result_code;
			}
			break;

#ifdef PCP_PEER
		case PCP_OPCODE_PEER:

			remainingSize -= PCP_PEER_V1_SIZE;
			if (remainingSize < 0) {
				pcp_msg_info->result_code = PCP_ERR_MALFORMED_REQUEST;
				return pcp_msg_info->result_code;
			}

#ifdef DEBUG
			printPEEROpcodeVersion1(req);
#endif /* DEBUG */
			parsePCPPEER_version1(req, pcp_msg_info);

			req += PCP_PEER_V1_SIZE;

			parsePCPOptions(req, remainingSize, pcp_msg_info);

			if (ValidatePCPMsg(pcp_msg_info)) {
				if (pcp_msg_info->lifetime == 0) {
					DeletePCPPeer(pcp_msg_info);
				} else {
					CreatePCPPeer(pcp_msg_info);
				}
			} else {
				syslog(LOG_ERR, "PCP: Invalid PCP v1 PEER message.");
				 return pcp_msg_info->result_code;
			}


			break;
#endif /* PCP_PEER */
		default:
			pcp_msg_info->result_code = PCP_ERR_UNSUPP_OPCODE;
			break;
		}
