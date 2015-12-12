___HIDDEN void adjust_msections
   ___P((___msections **msp,
         int n),
        (msp,
         n)
___msections **msp;
int n;)
{
  int max_ns, ns;
  ___msections *ms = *msp;
  ___msection *hd;
  ___msection *tl;

  if (ms == 0)
    {
      max_ns = 0;
      ns = 0;
      hd = 0;
      tl = 0;
    }
  else
    {
      max_ns = ms->max_nb_sections;
      ns = ms->nb_sections;
      hd = ms->head;
      tl = ms->tail;
    }

  if (ms == 0 || n > max_ns)
    {
      /* must allocate a new msections structure */

      ___msections *new_ms;
      int i;

      while (n > max_ns) /* grow max_nb_sections until big enough */
        max_ns = 2*max_ns + 1;

      new_ms = ___CAST(___msections*,
                       alloc_mem_aligned
                         (___WORDS(___sizeof_msections(max_ns)),
                          1,
                          0));

      if (new_ms == 0)
        return;

      new_ms->max_nb_sections = max_ns;
      new_ms->nb_sections = ns;
      new_ms->head = hd;
      new_ms->tail = tl;

      for (i=ns-1; i>=0; i--)
        new_ms->sections[i] = ms->sections[i];

      if (ms != 0)
        free_mem_aligned (ms);

      ms = new_ms;

      *msp = ms;
    }

  if (n < ns)
    {
      /* contraction of the msections */

      int j;

      while (ns > n)
        {
          ___msection *s = tl;

          tl = tl->prev;

          if (tl == 0)
            hd = 0;
          else
            tl->next = 0;

          for (j=s->pos; j<ns-1; j++)
            {
              ms->sections[j] = ms->sections[j+1];
              ms->sections[j]->pos = j;
            }

          free_mem_aligned (s);

          ns--;
        }

      ms->nb_sections = ns;
      ms->head = hd;
      ms->tail = tl;

      /*
       * Contraction of the msections structure is not performed
       * because there is typically very little memory to be
       * reclaimed.
       */
    }
  else
    {
      /* expansion of the msections */

      int i, j;

      while (ns < n)
        {
          ___msection *s = ___CAST(___msection*,
                                   alloc_mem_aligned
                                     (___WORDS(___sizeof_msection(___MSECTION_SIZE)),
                                      1,
                                      0));

          if (s == 0)
            return;

          i = find_msection (ms, ___CAST(void*,s));

#ifdef ___ALLOC_MEM_UP
          i++;
#endif

          for (j=ns; j>i; j--)
            {
              ms->sections[j] = ms->sections[j-1];
              ms->sections[j]->pos = j;
            }

          ms->sections[i] = s;

          if (tl == 0)
            {
              hd = s;
              s->index = 0;
            }
          else
            {
              tl->next = s;
              s->index = tl->index + 1;
            }

          s->pos = i;
          s->prev = tl;
          s->next = 0;

          tl = s;

          ms->nb_sections = ++ns;
          ms->head = hd;
          ms->tail = tl;
        }
    }
}
