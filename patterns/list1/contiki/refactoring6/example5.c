if(*dscp != NULL
#if CTK_CONF_ICONS
           && data == (process_data_t)(*dscp)->icon
#endif /* CTK_CONF_ICONS */
           ) {
          RUN((*dscp)->prgname, (*dscp)->process, NULL);
          break;
        }
