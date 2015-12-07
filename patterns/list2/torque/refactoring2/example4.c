#ifndef NUMA_SUPPORT
if ((pnode != NULL) &&
        (pjob->ji_nodeid == pnode->hn_node))
#endif /* ndef NUMA_SUPPORT */
      {
      task *tmp_task;

      /* send event to local child */

      tmp_task = task_find(pjob, pobit->oe_info.fe_taskid);

      if ((tmp_task != NULL) &&
          (tmp_task->ti_chan != NULL))
        {
        tm_reply(tmp_task->ti_chan, IM_ALL_OKAY, pobit->oe_info.fe_event);

        diswsi(tmp_task->ti_chan, ptask->ti_qs.ti_exitstat);

        DIS_tcp_wflush(tmp_task->ti_chan);
        }
      }
#ifndef NUMA_SUPPORT 
    else
      {
      /* Send a response over to MOM whose child sent the request. */
      if (pnode != NULL)
        send_task_obit_response(pjob, pnode, cookie, pobit, ptask->ti_qs.ti_exitstat);
      }
