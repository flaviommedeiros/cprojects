___HIDDEN void process_wills
   ___P((___PSDNC),
        (___PSVNC)
___PSDKR)
{
  ___PSGET
  ___WORD* tail_exec;
  ___WORD* tail_nonexec;
  ___WORD curr;

#ifdef ENABLE_CONSISTENCY_CHECKS
  reference_location = IN_WILL_LIST;
#endif

  determine_will_executability (nonexecutable_wills);

  /*
   * Finish scanning the wills whose testator object remains to be
   * marked.
   *
   * The wills that have become executable are also transferred from
   * the nonexecutable wills list to the executable wills list.
   */

  tail_exec = &executable_wills;
  curr = *tail_exec;

  while (___UNTAG(curr) != 0)
    {
      ___WORD will = ___TAG(___UNTAG(curr),___tSUBTYPED);

      mark_array (___PSP &will, 1);

      *tail_exec = ___TAG(___UNTAG(will),___EXECUTABLE_WILL);
      tail_exec = &___BODY_AS(will,___tSUBTYPED)[0];
      curr = *tail_exec;
      if (curr & ___UNMARKED_TESTATOR_WILL)
        mark_array (___PSP tail_exec+1, 1); /* mark testator object */
    }

  tail_nonexec = &nonexecutable_wills;
  curr = *tail_nonexec;

  while (___UNTAG(curr) != 0)
    {
      ___WORD will = ___TAG(___UNTAG(curr),___tSUBTYPED);

      mark_array (___PSP &will, 1);

      if (___BODY_AS(will,___tSUBTYPED)[0] & ___EXECUTABLE_WILL)
        {
          /* move will to executable will list */

          *tail_exec = ___TAG(___UNTAG(will),___EXECUTABLE_WILL);
          tail_exec = &___BODY_AS(will,___tSUBTYPED)[0];
          curr = *tail_exec;
          if (curr & ___UNMARKED_TESTATOR_WILL)
            mark_array (___PSP tail_exec+1, 1); /* mark testator object */
        }
      else
        {
          /* leave will in nonexecutable will list */

          *tail_nonexec = ___TAG(___UNTAG(will),0);
          tail_nonexec = &___BODY_AS(will,___tSUBTYPED)[0];
          curr = *tail_nonexec;
          if (curr & ___UNMARKED_TESTATOR_WILL)
            mark_array (___PSP tail_nonexec+1, 1); /* mark testator object */
        }
    }

  *tail_exec = ___TAG(0,___EXECUTABLE_WILL);
  *tail_nonexec = ___TAG(0,0);
}
