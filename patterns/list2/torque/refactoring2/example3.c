#ifndef NUMA_SUPPORT
if ((pjob->ji_nodeid != 0) && 
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
