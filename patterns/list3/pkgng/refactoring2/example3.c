#ifdef TRACE
if (!ps->trace)
#endif
    {
      q = ps->oclauses;
      for (p = q; p < ps->ohead; p++)
	if ((c = *p))
	  *q++ = c;
      ps->ohead = q;

      q = ps->lclauses;
      for (p = q; p < ps->lhead; p++)
	if ((c = *p))
	  *q++ = c;
      ps->lhead = q;
    }
