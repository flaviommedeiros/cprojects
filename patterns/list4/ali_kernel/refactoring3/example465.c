switch (request) {
		/*
		 * read word at location "addr" in the child process.
		 */
		case PTRACE_PEEKTEXT:
		case PTRACE_PEEKDATA:
			ret = generic_ptrace_peekdata(child, addr, data);
			break;

		case PTRACE_PEEKUSR:
			ret = ptrace_read_user(child, addr, (unsigned long __user *)data);
			break;

		/*
		 * write the word at location addr.
		 */
		case PTRACE_POKETEXT:
		case PTRACE_POKEDATA:
			ret = generic_ptrace_pokedata(child, addr, data);
			break;

		case PTRACE_POKEUSR:
			ret = ptrace_write_user(child, addr, data);
			break;

		/*
		 * continue/restart and stop at next (return from) syscall
		 */
		case PTRACE_SYSCALL:
		case PTRACE_CONT:
			ret = -EIO;
			if (!valid_signal(data))
				break;
			if (request == PTRACE_SYSCALL)
				set_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
			else
				clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
			child->exit_code = data;
			single_step_disable(child);
			wake_up_process(child);
			ret = 0;
			break;

		/*
		 * make the child exit.  Best I can do is send it a sigkill.
		 * perhaps it should be put in the status that it wants to
		 * exit.
		 */
		case PTRACE_KILL:
			single_step_disable(child);
			if (child->exit_state != EXIT_ZOMBIE) {
				child->exit_code = SIGKILL;
				wake_up_process(child);
			}
			ret = 0;
			break;

		/*
		 * execute single instruction.
		 */
		case PTRACE_SINGLESTEP:
			ret = -EIO;
			if (!valid_signal(data))
				break;
			single_step_enable(child);
			clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
			child->exit_code = data;
			/* give it a chance to run. */
			wake_up_process(child);
			ret = 0;
			break;

		case PTRACE_GETREGS:
			ret = ptrace_getregs(child, (void __user *)data);
			break;

		case PTRACE_SETREGS:
			ret = ptrace_setregs(child, (void __user *)data);
			break;

		case PTRACE_GETFPREGS:
			ret = ptrace_getfpregs(child, (void __user *)data);
			break;
		
		case PTRACE_SETFPREGS:
			ret = ptrace_setfpregs(child, (void __user *)data);
			break;

#ifdef CONFIG_IWMMXT
		case PTRACE_GETWMMXREGS:
			ret = ptrace_getwmmxregs(child, (void __user *)data);
			break;

		case PTRACE_SETWMMXREGS:
			ret = ptrace_setwmmxregs(child, (void __user *)data);
			break;
#endif

		case PTRACE_GET_THREAD_AREA:
			ret = put_user(task_thread_info(child)->tp_value,
				       (unsigned long __user *) data);
			break;

		case PTRACE_SET_SYSCALL:
			task_thread_info(child)->syscall = data;
			ret = 0;
			break;

#ifdef CONFIG_CRUNCH
		case PTRACE_GETCRUNCHREGS:
			ret = ptrace_getcrunchregs(child, (void __user *)data);
			break;

		case PTRACE_SETCRUNCHREGS:
			ret = ptrace_setcrunchregs(child, (void __user *)data);
			break;
#endif

#ifdef CONFIG_VFP
		case PTRACE_GETVFPREGS:
			ret = ptrace_getvfpregs(child, (void __user *)data);
			break;

		case PTRACE_SETVFPREGS:
			ret = ptrace_setvfpregs(child, (void __user *)data);
			break;
#endif

		default:
			ret = ptrace_request(child, request, addr, data);
			break;
	}
