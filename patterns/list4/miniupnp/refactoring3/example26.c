switch (pcp_buf[0]) { /* code */

	case PCP_OPTION_3RD_PARTY:

		if (option_length != PCP_3RD_PARTY_OPTION_SIZE) {
			pcp_msg_info->result_code = PCP_ERR_MALFORMED_OPTION;
			return 0;
		}
#ifdef DEBUG
		syslog(LOG_DEBUG, "PCP OPTION: \t Third party\n");
		syslog(LOG_DEBUG, "Third PARTY IP: \t %s\n", inet_ntop(AF_INET6,
		       pcp_buf + 4, third_addr, INET6_ADDRSTRLEN));
#endif
		if (pcp_msg_info->thirdp_ip ) {
			syslog(LOG_ERR, "PCP: THIRD PARTY OPTION was already present. \n");
			pcp_msg_info->result_code = PCP_ERR_MALFORMED_OPTION;
			return 0;
		} else {
			pcp_msg_info->thirdp_ip = (struct in6_addr *)(pcp_buf + 4);
			pcp_msg_info->mapped_ip = (struct in6_addr *)(pcp_buf + 4);
		}
		break;

	case PCP_OPTION_PREF_FAIL:

		if (option_length != PCP_PREFER_FAIL_OPTION_SIZE) {
			pcp_msg_info->result_code = PCP_ERR_MALFORMED_OPTION;
			return 0;
		}
#ifdef DEBUG
		syslog(LOG_DEBUG, "PCP OPTION: \t Prefer failure \n");
#endif
		if (pcp_msg_info->opcode != PCP_OPCODE_MAP) {
			syslog(LOG_DEBUG, "PCP: Unsupported OPTION for given OPCODE.\n");
			pcp_msg_info->result_code = PCP_ERR_MALFORMED_REQUEST;
		}
		if (pcp_msg_info->pfailure_present != 0 ) {
			syslog(LOG_DEBUG, "PCP: PREFER FAILURE OPTION was already present.\n");
			pcp_msg_info->result_code = PCP_ERR_MALFORMED_OPTION;
		} else {
			pcp_msg_info->pfailure_present = 1;
		}
		break;

	case PCP_OPTION_FILTER:
		/* TODO fully implement filter */
		if (option_length != PCP_FILTER_OPTION_SIZE) {
			pcp_msg_info->result_code = PCP_ERR_MALFORMED_OPTION;
			return 0;
		}
#ifdef DEBUG
		syslog(LOG_DEBUG, "PCP OPTION: \t Filter\n");
#endif
		if (pcp_msg_info->opcode != PCP_OPCODE_MAP) {
			syslog(LOG_ERR, "PCP: Unsupported OPTION for given OPCODE.\n");
			pcp_msg_info->result_code = PCP_ERR_MALFORMED_REQUEST;
			return 0;
		}
		break;

#ifdef PCP_FLOWP
	case PCP_OPTION_FLOW_PRIORITY:

#ifdef DEBUG
		syslog(LOG_DEBUG, "PCP OPTION: \t Flow priority\n");
#endif
		if (option_length != PCP_FLOW_PRIORITY_OPTION_SIZE) {
			syslog(LOG_ERR, "PCP: Error processing DSCP. sizeof %d and remaining %d. flow len %d \n",
			       PCP_FLOW_PRIORITY_OPTION_SIZE, remain, READNU16(pcp_buf + 2));
			pcp_msg_info->result_code = PCP_ERR_MALFORMED_OPTION;
			return 0;
		}

#ifdef DEBUG
		syslog(LOG_DEBUG, "DSCP UP: \t %d\n", pcp_buf[4]);
		syslog(LOG_DEBUG, "DSCP DOWN: \t %d\n", pcp_buf[5]);
#endif
		pcp_msg_info->dscp_up = pcp_buf[4];
		pcp_msg_info->dscp_down = pcp_buf[5];
		pcp_msg_info->flowp_present = 1;

		break;
#endif
	default:
		if (pcp_buf[0] < 128) {
			syslog(LOG_ERR, "PCP: Unrecognized mandatory PCP OPTION: %d \n", (int)pcp_buf[0]);
			/* Mandatory to understand */
			pcp_msg_info->result_code = PCP_ERR_UNSUPP_OPTION;
			remain = 0;
			break;
		}
		/* TODO - log optional not understood options? */
		break;
	}
