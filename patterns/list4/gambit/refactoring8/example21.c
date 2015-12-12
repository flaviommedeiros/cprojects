___SCMOBJ resize_vm
   ___P((___PSD
         ___SCMOBJ thunk,
         ___WORD target_nb_processors),
        (___PSV
         thunk,
         target_nb_processors)
___PSDKR
___SCMOBJ thunk;
___WORD target_nb_processors;)
{
  ___PSGET
  ___SCMOBJ err = ___FIX(___NO_ERR);

#ifndef ___SINGLE_THREADED_VMS

  ___virtual_machine_state ___vms = ___VMSTATE_FROM_PSTATE(___ps);
  int id = ___ps - ___vms->pstate; /* id of this processor */
  ___sync_op_struct sop;

  if (id != 0)
    {
      /*
       * Wait for nb_processors to be set synchronously by processor 0.
       */

      sop.op = OP_NOOP;
      barrier_sync_op (___PSP &sop);

      /*
       * Terminate current processor if it is no longer needed.
       */

      if (id >= target_nb_processors)
        ___thread_exit (); /* this call does not return */
    }
  else
    {
      int initial = ___vms->nb_processors;
      int i;

      /* TODO: add 2 msections for each additional processor */

      for (i=initial; i<target_nb_processors; i++)
        {
          ___processor_state p = &___vms->pstate[i];

          if ((err = ___setup_pstate (&___vms->pstate[i], ___vms))
              != ___FIX(___NO_ERR))
            {
              while (--i >= initial)
                ___cleanup_pstate (&___vms->pstate[i]);

              sop.op = OP_NOOP;
              barrier_sync_op (___PSP &sop);

              return err;
            }
        }

      /*
       * Set nb_processors synchronously.
       */

      sop.op = OP_SET_NB_PROCESSORS;
      sop.arg[0] = target_nb_processors;
      barrier_sync_op (___PSP &sop);

      if (target_nb_processors < initial)
        {
          /*
           * Join processors that are reclaimed when number of
           * processors shrinks.
           */

          for (i=initial-1; i>=target_nb_processors; i--)
            {
              ___processor_state p = &___vms->pstate[i];
              ___thread *t = &p->os_thread;

              ___thread_join (t); /* ignore error */
            }
        }
      else
        {
          /*
           * Create new processors when number of processors grows.
           */

          for (i=initial; i<target_nb_processors; i++)
            {
              ___processor_state p = &___vms->pstate[i];
              ___thread *t = &p->os_thread;

              t->start_fn = start_processor_execution;
              t->data_ptr = ___CAST(void*,p);
              t->data_scmobj = thunk;

              if ((err = ___thread_create (t)) != ___FIX(___NO_ERR))
                {
                  /* TODO: improve error handling */
                  static char *msgs[] = { "Could not create OS thread", NULL };
                  ___fatal_error (msgs);
                }
            }
        }
    }

#endif

  return err;
}
