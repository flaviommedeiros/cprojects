#             ifdef GC_ONLY_LOG_TO_FILE
if (str != NULL && *str == '0' && *(str + 1) == '\0')
#             else
                /* Otherwise setting the environment variable   */
                /* to anything other than "0" will prevent from */
                /* redirecting stdout/err to the log file.      */
                if (str == NULL || (*str == '0' && *(str + 1) == '\0'))
#             endif
              {
                GC_stdout = log_d;
                GC_stderr = log_d;
              }
