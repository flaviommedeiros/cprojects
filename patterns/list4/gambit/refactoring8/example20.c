___HIDDEN int barrier_sync_op
   ___P((___PSD
         ___sync_op_struct *sop_ptr),
        (___PSV
         sop_ptr)
___PSDKR
___sync_op_struct *sop_ptr;)
{
#ifdef ___SINGLE_THREADED_VMS

  return 0;

#else

  ___PSGET
  ___virtual_machine_state ___vms = ___VMSTATE_FROM_PSTATE(___ps);
  int id = ___ps - ___vms->pstate; /* id of this processor */
  int child_id1 = id*2+1;          /* id of child 1 */
  int child_id2 = id*2+2;          /* id of child 2 */
  int n = ___vms->nb_processors;   /* number of processors */
  ___sync_op_struct sop = *sop_ptr;
  int sid = id;

  /*
   * This function performs a barrier synchronization by imposing a
   * tree structure on the set of processors in this Gambit VM.
   */

  /*
   * Check operations from children processors and self to
   * determine the highest priority operation.
   */

  if (child_id1 < n)
    {
      int sid1;
      ___sync_op_struct sop1;

      while ((sid1 = ___ps->sync_id1) == SYNC_WAIT)
        WASTE_TIME();

      sop1 = ___ps->sync_op1;

      if (sop1.op < sop.op)
        {
          sop = sop1;
          sid = sid1;
        }
      else if (sop1.op == sop.op && COMBINING_OP(sop1.op))
        {
          switch (COMBINING_OP(sop1.op))
            {
            case COMBINING_AND:
              sop1.arg[0] &= sop.arg[0];
              break;
            case COMBINING_ADD:
              sop1.arg[0] += sop.arg[0];
              break;
            case COMBINING_MAX:
              if (sop1.arg[0] < sop.arg[0]) sop1.arg[0] = sop.arg[0];
              break;
            }

          sop = sop1;
          sid = sid1;
        }

      ___ps->sync_id1 = SYNC_WAIT;

      if (child_id2 < n)
        {
          int sid2;
          ___sync_op_struct sop2;

          while ((sid2 = ___ps->sync_id2) == SYNC_WAIT)
            WASTE_TIME();

          sop2 = ___ps->sync_op2;

          if (sop2.op < sop.op)
            {
              sop = sop2;
              sid = sid2;
            }
          else if (sop2.op == sop.op && COMBINING_OP(sop2.op))
            {
              switch (COMBINING_OP(sop2.op))
                {
                case COMBINING_AND:
                  sop2.arg[0] &= sop.arg[0];
                  break;
                case COMBINING_ADD:
                  sop2.arg[0] += sop.arg[0];
                  break;
                case COMBINING_MAX:
                  if (sop2.arg[0] < sop.arg[0]) sop2.arg[0] = sop.arg[0];
                  break;
                }

              sop = sop2;
              sid = sid2;
            }

          ___ps->sync_id2 = SYNC_WAIT;
        }
    }

  /*
   * Propagate highest priority operation to parent processor.
   */

  if (id == 0)
    {
      /*
       * Special case operation that sets nb_processors because this
       * information is used by the barrier_sync algorithm itself.
       */

      if (sop.op == OP_SET_NB_PROCESSORS)
        ___vms->nb_processors = sop.arg[0];
    }
  else
    {
      ___processor_state parent = &___vms->pstate[(id-1)/2];

      ___ps->sync_id0 = SYNC_WAIT;

      if (id & 1)
        {
          parent->sync_op1 = sop;
          parent->sync_id1 = sid;
        }
      else
        {
          parent->sync_op2 = sop;
          parent->sync_id2 = sid;
        }

      /*
       * Wait for parent to reply with winning operation.
       */

      while ((sid = ___ps->sync_id0) == SYNC_WAIT)
        WASTE_TIME();

      sop = ___ps->sync_op0;
    }

  /*
   * Propagate winning operation to children processors.
   */

  if (child_id1 < n)
    {
      ___processor_state child1 = &___vms->pstate[child_id1];

      child1->sync_op0 = sop;
      child1->sync_id0 = sid;

      if (child_id2 < n)
        {
          ___processor_state child2 = &___vms->pstate[child_id2];

          child2->sync_op0 = sop;
          child2->sync_id0 = sid;
        }
    }

  /*
   * Return winning operation and id of originating processor.
   */

  *sop_ptr = sop;

  return sid;

#endif
}
