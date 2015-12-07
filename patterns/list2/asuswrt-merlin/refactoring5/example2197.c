#ifdef PROCESS_SUPPORT
if (current_thread_g != executing_task)
						status = write_stack_register (current_thread_g, regno, suffix+1);
					else
#endif
						status = write_register (regno, suffix+1);
