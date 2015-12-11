if (jspIsInterrupted()
#ifdef USE_DEBUGGER
      && !(jsiStatus & JSIS_EXIT_DEBUGGER)
#endif
      ) {
    jsiConsoleRemoveInputLine();
    jsiConsolePrint("Execution Interrupted\n");
    jspSetInterrupted(false);
  }
