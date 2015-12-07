#ifdef ENOENT
if (errno == ENOENT) {
            DEBUGMSGTL(("read_config", "%s: %s\n", filename,
                        strerror(errno)));
        } else
#endif                          /* ENOENT */
#ifdef EACCES
        if (errno == EACCES) {
            DEBUGMSGTL(("read_config", "%s: %s\n", filename,
                        strerror(errno)));
        } else
#endif                          /* EACCES */
        {
            snmp_log_perror(filename);
        }
