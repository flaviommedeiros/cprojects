switch (field) {
	case RM_PartitionState:
		state = (int *) data;
		switch (*state) {
		case RM_PARTITION_FREE:
			*state = BG_BLOCK_FREE;
			break;
		case RM_PARTITION_CONFIGURING:
			*state = BG_BLOCK_BOOTING;
			break;
#ifdef HAVE_BGL
		case RM_PARTITION_BUSY:
			*state = BG_BLOCK_BUSY;
			break;
#else
		case RM_PARTITION_REBOOTING:
			*state = BG_BLOCK_REBOOTING;
			break;
#endif
		case RM_PARTITION_READY:
			*state = BG_BLOCK_INITED;
			break;
		case RM_PARTITION_DEALLOCATING:
			*state = BG_BLOCK_TERM;
			break;
		case RM_PARTITION_ERROR:
			*state = BG_BLOCK_ERROR_FLAG;
			break;
		case RM_PARTITION_NAV:
			*state = BG_BLOCK_NAV;
			break;
		default:
			break;
		}
		break;
	case RM_PartitionOptions:
		break;
#ifdef HAVE_BGL
	case RM_PartitionMode:
		break;
#endif
	case RM_SwitchFirstConnection:
	case RM_SwitchNextConnection:
		curr_conn = (rm_connection_t *)data;
		switch(curr_conn->p1) {
		case RM_PORT_S1:
			curr_conn->p1 = 1;
			break;
		case RM_PORT_S2:
			curr_conn->p1 = 2;
			break;
		case RM_PORT_S4:
			curr_conn->p1 = 4;
			break;
		default:
			error("1 unknown port %d",
			      _port_enum(curr_conn->p1));
			return SLURM_ERROR;
		}

		switch(curr_conn->p2) {
		case RM_PORT_S0:
			curr_conn->p2 = 0;
			break;
		case RM_PORT_S3:
			curr_conn->p2 = 3;
			break;
		case RM_PORT_S5:
			curr_conn->p2 = 5;
			break;
		default:
			error("2 unknown port %d",
			      _port_enum(curr_conn->p2));
			return SLURM_ERROR;
		}
		break;
	case RM_PortID:
		state = (int *) data;
		(*state) = _port_enum(*state);
		break;
	default:
		break;
	}
