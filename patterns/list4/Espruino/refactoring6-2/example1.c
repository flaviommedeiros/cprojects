while (!hasHadBreak && loopCond
#ifdef JSPARSE_MAX_LOOP_ITERATIONS
      && loopCount-->0
#endif
  ) {
    jslSeekToP(execInfo.lex, &whileCondStart);
    cond = jspeAssignmentExpression();
    loopCond = JSP_SHOULD_EXECUTE && jsvGetBoolAndUnLock(jsvSkipName(cond));
    jsvUnLock(cond);
    if (loopCond) {
      jslSeekToP(execInfo.lex, &whileBodyStart);
      execInfo.execute |= EXEC_IN_LOOP;
      jspDebuggerLoopIfCtrlC();
      jsvUnLock(jspeBlockOrStatement());
      if (!wasInLoop) execInfo.execute &= (JsExecFlags)~EXEC_IN_LOOP;
      if (execInfo.execute & EXEC_CONTINUE)
        execInfo.execute = EXEC_YES;
      else if (execInfo.execute & EXEC_BREAK) {
        execInfo.execute = EXEC_YES;
        hasHadBreak = true;
      }
    }
  }
