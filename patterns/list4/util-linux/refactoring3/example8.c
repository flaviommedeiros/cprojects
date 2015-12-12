switch (policy) {
	case SCHED_OTHER:
		printf("SCHED_OTHER\n");
		break;
	case SCHED_FIFO:
		printf("SCHED_FIFO\n");
		break;
#ifdef SCHED_RESET_ON_FORK
	case SCHED_FIFO | SCHED_RESET_ON_FORK:
		printf("SCHED_FIFO|SCHED_RESET_ON_FORK\n");
		break;
#endif
#ifdef SCHED_IDLE
	case SCHED_IDLE:
		printf("SCHED_IDLE\n");
		break;
#endif
	case SCHED_RR:
		printf("SCHED_RR\n");
		break;
#ifdef SCHED_RESET_ON_FORK
	case SCHED_RR | SCHED_RESET_ON_FORK:
		printf("SCHED_RR|SCHED_RESET_ON_FORK\n");
		break;
#endif
#ifdef SCHED_BATCH
	case SCHED_BATCH:
		printf("SCHED_BATCH\n");
		break;
#endif
	default:
		warnx(_("unknown scheduling policy"));
	}
