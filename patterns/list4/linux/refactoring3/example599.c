switch (addr) {
		case 0 ... 31:
			regs->regs[addr] = data;
			break;
		case FPR_BASE ... FPR_BASE + 31: {
			union fpureg *fregs = get_fpu_regs(child);

			init_fp_ctx(child);
#ifdef CONFIG_32BIT
			if (test_thread_flag(TIF_32BIT_FPREGS)) {
				/*
				 * The odd registers are actually the high
				 * order bits of the values stored in the even
				 * registers - unless we're using r2k_switch.S.
				 */
				set_fpr32(&fregs[(addr & ~1) - FPR_BASE],
					  addr & 1, data);
				break;
			}
#endif
			set_fpr64(&fregs[addr - FPR_BASE], 0, data);
			break;
		}
		case PC:
			regs->cp0_epc = data;
			break;
		case MMHI:
			regs->hi = data;
			break;
		case MMLO:
			regs->lo = data;
			break;
#ifdef CONFIG_CPU_HAS_SMARTMIPS
		case ACX:
			regs->acx = data;
			break;
#endif
		case FPC_CSR:
			child->thread.fpu.fcr31 = data & ~FPU_CSR_ALL_X;
			break;
		case DSP_BASE ... DSP_BASE + 5: {
			dspreg_t *dregs;

			if (!cpu_has_dsp) {
				ret = -EIO;
				break;
			}

			dregs = __get_dsp_regs(child);
			dregs[addr - DSP_BASE] = data;
			break;
		}
		case DSP_CONTROL:
			if (!cpu_has_dsp) {
				ret = -EIO;
				break;
			}
			child->thread.dsp.dspcontrol = data;
			break;
		default:
			/* The rest are not allowed. */
			ret = -EIO;
			break;
		}
