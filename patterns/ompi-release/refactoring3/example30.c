switch (info->si_code)
            {
#ifdef POLL_IN
            case POLL_IN: si_code_str = "Data input available"; break;
#endif
#ifdef POLL_OUT
            case POLL_OUT: si_code_str = "Output buffers available"; break;
#endif
#ifdef POLL_MSG
            case POLL_MSG: si_code_str = "Input message available"; break;
#endif
#ifdef POLL_ERR
            case POLL_ERR: si_code_str = "I/O error"; break;
#endif
#ifdef POLL_PRI
            case POLL_PRI: si_code_str = "High priority input available"; break;
#endif
#ifdef POLL_HUP
            case POLL_HUP: si_code_str = "Device disconnected"; break;
#endif
            }
