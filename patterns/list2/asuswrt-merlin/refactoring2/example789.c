#if defined(TUI)
if (!tui_is_window_visible (DISASSEM_WIN))
#endif
    {
      printf_filtered ("Dump of assembler code ");
      if (name != NULL)
	{
	  printf_filtered ("for function %s:\n", name);
	}
      else
	{
	  printf_filtered ("from ");
	  deprecated_print_address_numeric (low, 1, gdb_stdout);
	  printf_filtered (" to ");
	  deprecated_print_address_numeric (high, 1, gdb_stdout);
	  printf_filtered (":\n");
	}

      /* Dump the specified range.  */
      gdb_disassembly (uiout, 0, 0, 0, -1, low, high);

      printf_filtered ("End of assembler dump.\n");
      gdb_flush (gdb_stdout);
    }
#if defined(TUI)
  else
    {
      tui_show_assembly (low);
    }
