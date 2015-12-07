#ifdef WIN32
if (CreateDirectory(buf, NULL) == 0)
#else
            if (mkdir(buf, mode) == -1)
#endif
                goto out;
            else
                snmp_log(LOG_INFO, "Created directory: %s\n", buf);
