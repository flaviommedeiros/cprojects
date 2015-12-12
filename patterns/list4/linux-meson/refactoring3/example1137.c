switch (cmd){
	case 'r':
	case 'R':
		work_mode=WORK_MODE_READ;
		do_read_work(argn,argv);
		break;
	case 'w':
	case 'W':
		work_mode=WORK_MODE_WRITE;
		do_write_work(argn,argv);
		break;
	case 'c':
	case 'C':
		work_mode=WORK_MODE_CLKMEASURE;
		do_clk_measure_work(argn,argv);
		break;
	case 'd':
	case 'D':
		work_mode=WORK_MODE_DUMP;
		do_dump_work(argn,argv);
		break;
	case 't':
	case 'T':
		work_mode=WORK_MODE_THREAD;
		do_thread_show_work(argn,argv);
		break;
	case 's':
	case 'S':
		work_mode=WORK_MODE_STACK;
		do_stack_show_work(argn,argv);
		break;

#ifdef CONFIG_GPIO_TEST	
	case 'g':
	case 'G':
		work_mode=WORK_MODE_GPIOTEST;
		do_gpio_test_work(argn,argv);
		break;
#endif /* CONFIG_GPIO_TEST */

	default:
		goto end;
	}
