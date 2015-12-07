#ifdef MANAGEMENT_IN_EXTRA
if (man->connection.in_extra)
	      {
		if (!strcmp ((char *)line, "END"))
		  in_extra_dispatch (man);
		else
		  buffer_list_push (man->connection.in_extra, line);
	      }
	    else
#endif
	      man_process_command (man, (char *) line);
