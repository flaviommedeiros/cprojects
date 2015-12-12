___SCMOBJ ___device_stream_select_virt
   ___P((___device *self,
         ___BOOL for_writing,
         int i,
         int pass,
         ___device_select_state *state),
        (self,
         for_writing,
         i,
         pass,
         state)
___device *self;
___BOOL for_writing;
int i;
int pass;
___device_select_state *state;)
{
  ___device_stream *d = ___CAST(___device_stream*,self);

#ifdef USE_PUMPS

  int stage = (for_writing
               ? d->base.write_stage
               : d->base.read_stage);
  ___device_stream_pump *p = (for_writing
                              ? d->write_pump
                              : d->read_pump);

  if (p != NULL)
    {
      if (pass == ___SELECT_PASS_1)
        {
          HANDLE wait_obj;

          if (stage != ___STAGE_OPEN)
            wait_obj = p->thread;
          else
            {
              if (for_writing)
                wait_obj = p->pipe.wevent;
              else
                wait_obj = p->pipe.revent;
            }

          ___device_select_add_wait_obj (state, i, wait_obj);

          return ___FIX(___SELECT_SETUP_DONE);
        }

      /* pass == ___SELECT_PASS_CHECK */

      if (stage != ___STAGE_OPEN)
        state->devs[i] = NULL;
      else
        {
          if (state->devs_next[i] != -1)
            state->devs[i] = NULL;
        }

      return ___FIX(___NO_ERR);
    }

#endif

  return ___device_stream_select_raw_virt
           (d,
            for_writing,
            i,
            pass,
            state);
}
