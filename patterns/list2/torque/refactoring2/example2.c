#ifndef NUMA_SUPPORT
if ((pjob->ji_nodeid == 0) && 
      is_nodeid_on_this_host(pjob, nodeid) == true)
#endif /* ndef NUMA_SUPPORT */
    {
    /* XXX */
 
    i = TM_ERROR;
    
    ptask = pbs_task_create(pjob, TM_NULL_TASK);
    
    if (ptask != NULL)
      {
      strcpy(ptask->ti_qs.ti_parentjobid, jobid);
      
      ptask->ti_qs.ti_parentnode = pjob->ji_nodeid;
      ptask->ti_qs.ti_parenttask = fromtask;
      
      if (LOGLEVEL >= 6)
         {
        log_record(
          PBSEVENT_ERROR,
          PBS_EVENTCLASS_JOB,
          pjob->ji_qs.ji_jobid,
          "saving task (TM_SPAWN)");
         }
      
      if (task_save(ptask) != -1)
        {
        *ret = start_process(ptask, argv, envp);
 
        if (*ret != -1)
          i = TM_OKAY;
        }
      }
    
    arrayfree(argv);
    arrayfree(envp);
    
    *ret = tm_reply(chan, i, event);
    
    if (*ret != DIS_SUCCESS)
      return(TM_DONE);
    
    *ret = diswsi(chan, ((i == TM_ERROR) ?  TM_ESYSTEM : ptask->ti_qs.ti_task));
    
    return(TM_DONE);
    }  /* END if I'm MS and task is on me */
  
  /*
   * If I'm a regular mom and the destination is not
   * MS, just send a GET_TID to MS.
   */
#ifndef NUMA_SUPPORT
  else if ((pjob->ji_nodeid != 0) && 
           (nodeid != pjob->ji_vnods[0].vn_node))
#endif /* ndef NUMA_SUPPORT */
    {
    /* XXX */
    
    pnode = &pjob->ji_vnods[0];
    phost = pnode->vn_host;
    
    ep = event_alloc(IM_GET_TID,pnode->vn_host,TM_NULL_EVENT,TM_NULL_TASK);
    
    ep->ee_argv = argv;
    ep->ee_envp = envp;
    ep->ee_forward.fe_node = nodeid;
    ep->ee_forward.fe_event = event;
    ep->ee_forward.fe_taskid = fromtask;
 
    local_socket = tcp_connect_sockaddr((struct sockaddr *)&phost->sock_addr,sizeof(phost->sock_addr));

    if (local_socket < 0)
      return(TM_DONE);
    else if ((local_chan = DIS_tcp_setup(local_socket)) == NULL)
      {
      }
    else if ((*ret = im_compose(local_chan,jobid,cookie,IM_GET_TID,ep->ee_event,TM_NULL_TASK)) != DIS_SUCCESS)
      {
      }
    else
      {
      DIS_tcp_wflush(local_chan);
      *reply_ptr = FALSE;
      }

    close(local_socket);
    if (local_chan != NULL)
      DIS_tcp_cleanup(local_chan);

    return(TM_DONE);
    }
