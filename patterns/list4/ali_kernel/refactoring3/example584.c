switch (request) {
		/* when I and D space are separate, these will need to be fixed. */
	case PTRACE_PEEKDATA:
		pr_debug("ptrace: PEEKDATA\n");
		/* fall through */
	case PTRACE_PEEKTEXT:	/* read word at location addr. */
		{
			unsigned long tmp = 0;
			int copied = 0, to_copy = sizeof(tmp);

			ret = -EIO;
			pr_debug("ptrace: PEEKTEXT at addr 0x%08lx + %i\n", addr, to_copy);
			if (is_user_addr_valid(child, addr, to_copy) < 0)
				break;
			pr_debug("ptrace: user address is valid\n");

			switch (bfin_mem_access_type(addr, to_copy)) {
			case BFIN_MEM_ACCESS_CORE:
			case BFIN_MEM_ACCESS_CORE_ONLY:
				copied = access_process_vm(child, addr, &tmp,
				                           to_copy, 0);
				if (copied)
					break;

				/* hrm, why didn't that work ... maybe no mapping */
				if (addr >= FIXED_CODE_START &&
				    addr + to_copy <= FIXED_CODE_END) {
					copy_from_user_page(0, 0, 0, &tmp, paddr, to_copy);
					copied = to_copy;
				} else if (addr >= BOOT_ROM_START) {
					memcpy(&tmp, paddr, to_copy);
					copied = to_copy;
				}

				break;
			case BFIN_MEM_ACCESS_DMA:
				if (safe_dma_memcpy(&tmp, paddr, to_copy))
					copied = to_copy;
				break;
			case BFIN_MEM_ACCESS_ITEST:
				if (isram_memcpy(&tmp, paddr, to_copy))
					copied = to_copy;
				break;
			default:
				copied = 0;
				break;
			}

			pr_debug("ptrace: copied size %d [0x%08lx]\n", copied, tmp);
			if (copied == to_copy)
				ret = put_user(tmp, datap);
			break;
		}

		/* read the word at location addr in the USER area. */
	case PTRACE_PEEKUSR:
		{
			unsigned long tmp;
			ret = -EIO;
			tmp = 0;
			if ((addr & 3) || (addr > (sizeof(struct pt_regs) + 16))) {
				printk(KERN_WARNING "ptrace error : PEEKUSR : temporarily returning "
				                    "0 - %x sizeof(pt_regs) is %lx\n",
				     (int)addr, sizeof(struct pt_regs));
				break;
			}
			if (addr == sizeof(struct pt_regs)) {
				/* PT_TEXT_ADDR */
				tmp = child->mm->start_code + TEXT_OFFSET;
			} else if (addr == (sizeof(struct pt_regs) + 4)) {
				/* PT_TEXT_END_ADDR */
				tmp = child->mm->end_code;
			} else if (addr == (sizeof(struct pt_regs) + 8)) {
				/* PT_DATA_ADDR */
				tmp = child->mm->start_data;
#ifdef CONFIG_BINFMT_ELF_FDPIC
			} else if (addr == (sizeof(struct pt_regs) + 12)) {
				goto case_PTRACE_GETFDPIC_EXEC;
			} else if (addr == (sizeof(struct pt_regs) + 16)) {
				goto case_PTRACE_GETFDPIC_INTERP;
#endif
			} else {
				tmp = get_reg(child, addr);
			}
			ret = put_user(tmp, datap);
			break;
		}

#ifdef CONFIG_BINFMT_ELF_FDPIC
	case PTRACE_GETFDPIC: {
		unsigned long tmp = 0;

		switch (addr) {
		case_PTRACE_GETFDPIC_EXEC:
		case PTRACE_GETFDPIC_EXEC:
			tmp = child->mm->context.exec_fdpic_loadmap;
			break;
		case_PTRACE_GETFDPIC_INTERP:
		case PTRACE_GETFDPIC_INTERP:
			tmp = child->mm->context.interp_fdpic_loadmap;
			break;
		default:
			break;
		}

		ret = put_user(tmp, datap);
		break;
	}
#endif

		/* when I and D space are separate, this will have to be fixed. */
	case PTRACE_POKEDATA:
		pr_debug("ptrace: PTRACE_PEEKDATA\n");
		/* fall through */
	case PTRACE_POKETEXT:	/* write the word at location addr. */
		{
			int copied = 0, to_copy = sizeof(data);

			ret = -EIO;
			pr_debug("ptrace: POKETEXT at addr 0x%08lx + %i bytes %lx\n",
			         addr, to_copy, data);
			if (is_user_addr_valid(child, addr, to_copy) < 0)
				break;
			pr_debug("ptrace: user address is valid\n");

			switch (bfin_mem_access_type(addr, to_copy)) {
			case BFIN_MEM_ACCESS_CORE:
			case BFIN_MEM_ACCESS_CORE_ONLY:
				copied = access_process_vm(child, addr, &data,
				                           to_copy, 1);
				if (copied)
					break;

				/* hrm, why didn't that work ... maybe no mapping */
				if (addr >= FIXED_CODE_START &&
				    addr + to_copy <= FIXED_CODE_END) {
					copy_to_user_page(0, 0, 0, paddr, &data, to_copy);
					copied = to_copy;
				} else if (addr >= BOOT_ROM_START) {
					memcpy(paddr, &data, to_copy);
					copied = to_copy;
				}

				break;
			case BFIN_MEM_ACCESS_DMA:
				if (safe_dma_memcpy(paddr, &data, to_copy))
					copied = to_copy;
				break;
			case BFIN_MEM_ACCESS_ITEST:
				if (isram_memcpy(paddr, &data, to_copy))
					copied = to_copy;
				break;
			default:
				copied = 0;
				break;
			}

			pr_debug("ptrace: copied size %d\n", copied);
			if (copied == to_copy)
				ret = 0;
			break;
		}

	case PTRACE_POKEUSR:	/* write the word at location addr in the USER area */
		ret = -EIO;
		if ((addr & 3) || (addr > (sizeof(struct pt_regs) + 16))) {
			printk(KERN_WARNING "ptrace error : POKEUSR: temporarily returning 0\n");
			break;
		}

		if (addr >= (sizeof(struct pt_regs))) {
			ret = 0;
			break;
		}
		if (addr == PT_SYSCFG) {
			data &= SYSCFG_MASK;
			data |= get_reg(child, PT_SYSCFG);
		}
		ret = put_reg(child, addr, data);
		break;

	case PTRACE_SYSCALL:	/* continue and stop at next (return from) syscall */
	case PTRACE_CONT:	/* restart after signal. */
		pr_debug("ptrace: syscall/cont\n");

		ret = -EIO;
		if (!valid_signal(data))
			break;
		if (request == PTRACE_SYSCALL)
			set_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		else
			clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		child->exit_code = data;
		ptrace_disable(child);
		pr_debug("ptrace: before wake_up_process\n");
		wake_up_process(child);
		ret = 0;
		break;

	/*
	 * make the child exit.  Best I can do is send it a sigkill.
	 * perhaps it should be put in the status that it wants to
	 * exit.
	 */
	case PTRACE_KILL:
		ret = 0;
		if (child->exit_state == EXIT_ZOMBIE)	/* already dead */
			break;
		child->exit_code = SIGKILL;
		ptrace_disable(child);
		wake_up_process(child);
		break;

	case PTRACE_SINGLESTEP:	/* set the trap flag. */
		pr_debug("ptrace: single step\n");
		ret = -EIO;
		if (!valid_signal(data))
			break;
		clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
		ptrace_enable(child);
		child->exit_code = data;
		wake_up_process(child);
		ret = 0;
		break;

	case PTRACE_GETREGS:
		/* Get all gp regs from the child. */
		ret = ptrace_getregs(child, datap);
		break;

	case PTRACE_SETREGS:
		printk(KERN_WARNING "ptrace: SETREGS: **** NOT IMPLEMENTED ***\n");
		/* Set all gp regs in the child. */
		ret = 0;
		break;

	default:
		ret = ptrace_request(child, request, addr, data);
		break;
	}
