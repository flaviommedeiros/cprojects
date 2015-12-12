switch (key_get(el, ch, &val)) {
			case XK_CMD:
				cmd = val.cmd;
				break;
			case XK_STR:
				FUN(el,push)(el, val.str);
				break;
#ifdef notyet
			case XK_EXE:
				/* XXX: In the future to run a user function */
				RunCommand(val.str);
				break;
#endif
			default:
				EL_ABORT((el->el_errfile, "Bad XK_ type \n"));
				break;
			}
