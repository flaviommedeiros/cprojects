switch(create_size) {
#ifndef HAVE_BGL
		case 64:
			blockreq.small64 = 8;
			break;
		case 256:
			blockreq.small256 = 2;
#endif
		case 32:
			blockreq.small32 = 16;
			break;
		case 128:
			blockreq.small128 = 4;
			break;
		case 512:
			slurm_mutex_unlock(&block_state_mutex);
			/* the slurmctld is always locked here */
			if (!node_already_down(mp_name))
				drain_nodes(mp_name, reason,
					    slurm_get_slurm_user_id());
			rc = SLURM_SUCCESS;
			goto cleanup;
			break;
		default:
			error("Unknown create size of %d", create_size);
			break;
		}
