#ifndef WIN32
if (kill(postmaster_pid, 0) != 0)
#else
			if (WaitForSingleObject(postmaster_pid, 0) == WAIT_OBJECT_0)
#endif
			{
				fprintf(stderr, _("\n%s: postmaster failed\nExamine %s/log/postmaster.log for the reason\n"), progname, outputdir);
				exit(2);
			}
