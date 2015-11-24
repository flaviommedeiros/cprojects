switch (info->si_code)
            {
#ifdef CLD_EXITED
            case CLD_EXITED: si_code_str = "Child has exited"; break;
#endif
#ifdef CLD_KILLED
            case CLD_KILLED: si_code_str = "Child has terminated abnormally and did not create a core file"; break;
#endif
#ifdef CLD_DUMPED
            case CLD_DUMPED: si_code_str = "Child has terminated abnormally and created a core file"; break;
#endif
#ifdef CLD_WTRAPPED
            case CLD_TRAPPED: si_code_str = "Traced child has trapped"; break;
#endif
#ifdef CLD_STOPPED
            case CLD_STOPPED: si_code_str = "Child has stopped"; break;
#endif
#ifdef CLD_CONTINUED
            case CLD_CONTINUED: si_code_str = "Stopped child has continued"; break;
#endif
            }
