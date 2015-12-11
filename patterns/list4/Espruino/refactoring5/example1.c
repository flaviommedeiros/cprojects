#ifdef USE_DEBUGGER
if (jsiStatus & JSIS_IN_DEBUGGER) {
        jsiDebuggerLine(lineToExecute);
        jsvUnLock(lineToExecute);
      } else
#endif
      {
        // execute!
        JsVar *v = jspEvaluateVar(lineToExecute, 0, jsiLineNumberOffset);
        // add input line to history
        jsiHistoryAddLine(lineToExecute);
        jsvUnLock(lineToExecute);
        jsiLineNumberOffset = 0; // forget the current line number now
        // print result (but NOT if we had an error)
        if (jsiEcho() && !jspHasError()) {
          jsiConsolePrintChar('=');
          jsfPrintJSON(v, JSON_LIMIT | JSON_NEWLINES | JSON_PRETTY | JSON_SHOW_DEVICES);
          jsiConsolePrint("\n");
        }
        jsvUnLock(v);
      }
