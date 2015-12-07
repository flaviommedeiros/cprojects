#ifdef ENABLE_BLCR
if (pjob->ji_qs.ji_svrflags & JOB_SVFLG_StagedIn)
#else
  if (pjob->ji_qs.ji_svrflags & (JOB_SVFLG_CHECKPOINT_FILE | JOB_SVFLG_StagedIn))
#endif
    {
    /* job has been checkpointed or files already staged in */
    /* in this case, exec_host must be already set          */

    if (prun->rq_destin && *prun->rq_destin) /* If a destination has been specified */
      {
      /* specified destination must match exec_host */
      if ((exec_host = strdup(pjob->ji_wattr[JOB_ATR_exec_host].at_val.at_str)) == NULL)
        {
        req_reject(PBSE_RMSYSTEM, 0, preq, NULL, "Cannot allocate memory");
        return(NULL);
        }

      if ((ptr = strchr(exec_host, '/')))
        *ptr = 0;

      if (strcmp(prun->rq_destin, exec_host) != 0)
        {
        /* FAILURE */
        free(exec_host);

        if (pjob->ji_qs.ji_svrflags & (JOB_SVFLG_CHECKPOINT_FILE))
          req_reject(PBSE_EXECTHERE, 0, preq, NULL, "allocated nodes must match checkpoint location");
        else
          req_reject(PBSE_EXECTHERE, 0, preq, NULL, "allocated nodes must match input file stagein location");
        
        return(NULL);
        }

      free(exec_host);
      }

    if ((pjob->ji_qs.ji_svrflags & JOB_SVFLG_HasNodes) == 0)
      {
      /* re-reserve nodes and leave exec_host as is */

      if ((rc = assign_hosts(  /* inside chk_job_torun() */
                  pjob,
                  pjob->ji_wattr[JOB_ATR_exec_host].at_val.at_str,
                  0,
                  FailHost,
                  EMsg)) != 0)   /* O */
        {
        req_reject(PBSE_EXECTHERE, 0, preq, FailHost, EMsg);
        
        return(NULL);
        }
      }
    }    /* END if (pjob->ji_qs.ji_svrflags & (JOB_SVFLG_CHECKPOINT_FILE|JOB_SVFLG_StagedIn)) */
  else
    {
    /* make sure exec gpus is clear */
    if (((pjob->ji_wattr[JOB_ATR_exec_gpus].at_flags & ATR_VFLAG_SET) != 0) &&
        (pjob->ji_wattr[JOB_ATR_exec_gpus].at_val.at_str != NULL))
      {
      job_attr_def[JOB_ATR_exec_gpus].at_free(
        &pjob->ji_wattr[JOB_ATR_exec_gpus]);
      }

    /* job has not run before or need not run there again */
    /* reserve nodes and set new exec_host */
    if ((prun->rq_destin == NULL) || (prun->rq_destin[0] == '\0'))
      {
      /* it is possible for the scheduler to pass a hostlist using the rq_extend 
       * field--we should use it as the given list as an alternative to rq_destin */

      rc = assign_hosts(pjob, preq->rq_extend, 1, FailHost, EMsg);  /* inside chk_job_torun() */
      }
    else
      {
      rc = assign_hosts(pjob, prun->rq_destin, 1, FailHost, EMsg);  /* inside chk_job_torun() */
      }

    if (rc != 0)
      {
      /* FAILURE - cannot assign correct hosts */

      req_reject(rc, 0, preq, FailHost, EMsg);

      return(NULL);
      }
    }
