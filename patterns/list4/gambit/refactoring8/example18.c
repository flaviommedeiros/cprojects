___HIDDEN void explain_problem
   ___P((___PSD
         ___WORD obj,
         char *msg),
        (___PSV
         obj,
         msg)
___PSDKR
___WORD obj;
char *msg;)
{
  ___PSGET

  dump_memory_map (___PSPNC);

  ___printf (">>> The object 0x%08x %s\n", obj, msg);

  {
    int j;
    for (j=-1; j<10; j++)
      {
        ___printf (">>>  body[%2d] = 0x%08x\n", j, ___BODY(obj)[j]);
        print_object (___BODY(obj)[j], 1, ">>>             ", 0);
      }
  }

  switch (reference_location)
    {
    case IN_OBJECT:
      {
        ___WORD container;
        ___WORD head = container_body[-1];
        ___SIZE_TS words = ___HD_WORDS(head);
        int subtype = ___HD_SUBTYPE(head);
        int i;

#if ___tPAIR != ___tSUBTYPED
        if (subtype == ___sPAIR)
          container = ___TAG(container_body-___BODY_OFS,___tPAIR);
        else
#endif
          container = ___TAG(container_body-___BODY_OFS,___tSUBTYPED);

        ___printf (">>> The reference was found in ");
        if (___HD_TYP(head) == ___PERM)
          ___printf ("___PERM ");
        else if (___HD_TYP(head) == ___STILL)
          ___printf ("___STILL ");
        else if (___HD_TYP(head) == ___MOVABLE0)
          ___printf ("___MOVABLE0 ");
        else if (___TYP(head) == ___FORW)
          ___printf ("___FORW ");
        else
          ___printf ("UNKNOWN ");
        ___printf ("object with body at 0x%08x:\n", container_body);

        ___printf (">>>  subtype = %d\n", subtype);
        ___printf (">>>  length  = %ld words\n", words);
        if (words <= 100)
          {
            for (i=0; i<words; i++)
              ___printf (">>>  body[%2d] = 0x%08x\n", i, container_body[i]);
          }
        else
          {
            for (i=0; i<50; i++)
              ___printf (">>>  body[%2d] = 0x%08x\n", i, container_body[i]);
            ___printf ("...\n");
            for (i=words-50; i<words; i++)
              ___printf (">>>  body[%2d] = 0x%08x\n", i, container_body[i]);
          }
        ___printf (">>> container =\n");
        print_object (container, 4, ">>>   ", 0);
        break;
      }

    case IN_REGISTER:
      ___printf (">>> The reference was found in a register\n");
      break;

    case IN_GLOBAL_VAR:
      ___printf (">>> The reference was found in a global variable\n");
      break;

    case IN_WILL_LIST:
      ___printf (">>> The reference was found in a will list\n");
      break;

    case IN_CONTINUATION:
      ___printf (">>> The reference was found in a continuation\n");
      break;

    case IN_RC:
      ___printf (">>> The reference was found in a reference counted object\n");
      break;
    }
}
