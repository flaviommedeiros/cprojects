if (setgid(gid) == -1
#ifdef HAVE_SETGROUPS
            || setgroups(1, (gid_t *)&gid) == -1
#endif
            ) {
            snmp_log_perror("setgid failed");
            if (!netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID, 
					NETSNMP_DS_AGENT_NO_ROOT_ACCESS)) {
                exit(1);
            }
        }
