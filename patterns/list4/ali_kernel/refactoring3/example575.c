switch (addr) {
		case 0 ... 31:
			tmp = regs->regs[addr];
			break;
		case FPR_BASE ... FPR_BASE + 31:
			if (tsk_used_math(child)) {
				fpureg_t *fregs = get_fpu_regs(child);

#ifdef CONFIG_32BIT
				/*
				 * The odd registers are actually the high
				 * order bits of the values stored in the even
				 * registers - unless we're using r2k_switch.S.
				 */
				if (addr & 1)
					tmp = (unsigned long) (fregs[((addr & ~1) - 32)] >> 32);
				else
					tmp = (unsigned long) (fregs[(addr - 32)] & 0xffffffff);
#endif
#ifdef CONFIG_64BIT
				tmp = fregs[addr - FPR_BASE];
#endif
			} else {
				tmp = -1;	/* FP not yet used  */
			}
			break;
		case PC:
			tmp = regs->cp0_epc;
			break;
		case CAUSE:
			tmp = regs->cp0_cause;
			break;
		case BADVADDR:
			tmp = regs->cp0_badvaddr;
			break;
		case MMHI:
			tmp = regs->hi;
			break;
		case MMLO:
			tmp = regs->lo;
			break;
#ifdef CONFIG_CPU_HAS_SMARTMIPS
		case ACX:
			tmp = regs->acx;
			break;
#endif
		case FPC_CSR:
			tmp = child->thread.fpu.fcr31;
			break;
		case FPC_EIR: {	/* implementation / version register */
			unsigned int flags;
#ifdef CONFIG_MIPS_MT_SMTC
			unsigned long irqflags;
			unsigned int mtflags;
#endif /* CONFIG_MIPS_MT_SMTC */

			preempt_disable();
			if (!cpu_has_fpu) {
				preempt_enable();
				break;
			}

#ifdef CONFIG_MIPS_MT_SMTC
			/* Read-modify-write of Status must be atomic */
			local_irq_save(irqflags);
			mtflags = dmt();
#endif /* CONFIG_MIPS_MT_SMTC */
			if (cpu_has_mipsmt) {
				unsigned int vpflags = dvpe();
				flags = read_c0_status();
				__enable_fpu();
				__asm__ __volatile__("cfc1\t%0,$0": "=r" (tmp));
				write_c0_status(flags);
				evpe(vpflags);
			} else {
				flags = read_c0_status();
				__enable_fpu();
				__asm__ __volatile__("cfc1\t%0,$0": "=r" (tmp));
				write_c0_status(flags);
			}
#ifdef CONFIG_MIPS_MT_SMTC
			emt(mtflags);
			local_irq_restore(irqflags);
#endif /* CONFIG_MIPS_MT_SMTC */
			preempt_enable();
			break;
		}
		case DSP_BASE ... DSP_BASE + 5: {
			dspreg_t *dregs;

			if (!cpu_has_dsp) {
				tmp = 0;
				ret = -EIO;
				goto out;
			}
			dregs = __get_dsp_regs(child);
			tmp = (unsigned long) (dregs[addr - DSP_BASE]);
			break;
		}
		case DSP_CONTROL:
			if (!cpu_has_dsp) {
				tmp = 0;
				ret = -EIO;
				goto out;
			}
			tmp = child->thread.dsp.dspcontrol;
			break;
		default:
			tmp = 0;
			ret = -EIO;
			goto out;
		}
