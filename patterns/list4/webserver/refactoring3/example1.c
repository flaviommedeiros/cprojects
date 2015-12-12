switch (srv->thread_policy) {
#ifdef HAVE_PTHREAD
		case SCHED_FIFO:
			cherokee_buffer_add_str (&n, ", FIFO scheduling policy");
			break;
		case SCHED_RR:
			cherokee_buffer_add_str (&n, ", RR scheduling policy");
			break;
#endif
		default:
			cherokee_buffer_add_str (&n, ", standard scheduling policy");
			break;
		}
