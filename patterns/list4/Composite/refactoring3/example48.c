switch (i) {
		case 0:
			cos_default_div_fault_handler  = did->handler;
			break;
		case 14:
			cos_default_page_fault_handler = did->handler;
			break;
		case 0xe9:
			cos_default_reg_save_handler   = did->handler;
			break;
#ifdef FPU_ENABLED
                case 7:
                        cos_default_fpu_not_available_handler = did->handler;
                        break;
#endif
		}
