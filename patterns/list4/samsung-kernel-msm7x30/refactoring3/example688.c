switch (cur_cpu_spec->oprofile_type) {
#ifdef CONFIG_PPC_BOOK3S_64
#ifdef CONFIG_OPROFILE_CELL
		case PPC_OPROFILE_CELL:
			if (firmware_has_feature(FW_FEATURE_LPAR))
				return -ENODEV;
			model = &op_model_cell;
			ops->sync_start = model->sync_start;
			ops->sync_stop = model->sync_stop;
			break;
#endif
		case PPC_OPROFILE_RS64:
			model = &op_model_rs64;
			break;
		case PPC_OPROFILE_POWER4:
			model = &op_model_power4;
			break;
		case PPC_OPROFILE_PA6T:
			model = &op_model_pa6t;
			break;
#endif
#ifdef CONFIG_6xx
		case PPC_OPROFILE_G4:
			model = &op_model_7450;
			break;
#endif
#if defined(CONFIG_FSL_EMB_PERFMON)
		case PPC_OPROFILE_FSL_EMB:
			model = &op_model_fsl_emb;
			break;
#endif
		default:
			return -ENODEV;
	}
