while (!hasHadBreak && JSP_SHOULD_EXECUTE && loopCond
#ifdef JSPARSE_MAX_LOOP_ITERATIONS
        && loopCount-->0
#endif
    ) {
      jslSeekToP(execInfo.lex, &forCondStart);
      ;
      if (execInfo.lex->tk == ';') {
        loopCond = true;
      } else {
        JsVar *cond = jspeAssignmentExpression();
        loopCond = jsvGetBoolAndUnLock(jsvSkipName(cond));
        jsvUnLock(cond);
      }
      if (JSP_SHOULD_EXECUTE && loopCond) {
        jslSeekToP(execInfo.lex, &forBodyStart);
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
      if (JSP_SHOULD_EXECUTE && loopCond && !hasHadBreak) {
        jslSeekToP(execInfo.lex, &forIterStart);
        if (execInfo.lex->tk != ')') jsvUnLock(jspeExpression());
      }
    }
