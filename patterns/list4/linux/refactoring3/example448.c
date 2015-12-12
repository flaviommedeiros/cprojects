switch (cmd) {
		case 'm':
			cmd = inchar();
			switch (cmd) {
			case 'm':
			case 's':
			case 'd':
				memops(cmd);
				break;
			case 'l':
				memlocate();
				break;
			case 'z':
				memzcan();
				break;
			case 'i':
				show_mem(0);
				break;
			default:
				termch = cmd;
				memex();
			}
			break;
		case 'd':
			dump();
			break;
		case 'l':
			symbol_lookup();
			break;
		case 'r':
			prregs(excp);	/* print regs */
			break;
		case 'e':
			excprint(excp);
			break;
		case 'S':
			super_regs();
			break;
		case 't':
			backtrace(excp);
			break;
		case 'f':
			cacheflush();
			break;
		case 's':
			if (do_spu_cmd() == 0)
				break;
			if (do_step(excp))
				return cmd;
			break;
		case 'x':
		case 'X':
			return cmd;
		case EOF:
			printf(" <no input ...>\n");
			mdelay(2000);
			return cmd;
		case '?':
			xmon_puts(help_string);
			break;
		case '#':
			set_lpp_cmd();
			break;
		case 'b':
			bpt_cmds();
			break;
		case 'C':
			csum();
			break;
		case 'c':
			if (cpu_cmd())
				return 0;
			break;
		case 'z':
			bootcmds();
			break;
		case 'p':
			proccall();
			break;
#ifdef CONFIG_PPC_STD_MMU
		case 'u':
			dump_segments();
			break;
#elif defined(CONFIG_44x)
		case 'u':
			dump_tlb_44x();
			break;
#elif defined(CONFIG_PPC_BOOK3E)
		case 'u':
			dump_tlb_book3e();
			break;
#endif
		default:
			printf("Unrecognized command: ");
			do {
				if (' ' < cmd && cmd <= '~')
					putchar(cmd);
				else
					printf("\\x%x", cmd);
				cmd = inchar();
			} while (cmd != '\n');
			printf(" (type ? for help)\n");
			break;
		}
