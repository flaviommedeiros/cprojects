switch (p_CB->state) {
#ifdef __CMSIS_RTOS
    case 3:
      /* Task is waiting to allocate memory, remove it from the waiting list */
      mem = rt_alloc_box(p_msg);
      if (mem == NULL) break;
      p_TCB = rt_get_first ((P_XCB)p_CB);
      rt_ret_val(p_TCB, (U32)mem);
      p_TCB->state = READY;
      rt_rmv_dly (p_TCB);
      rt_put_prio (&os_rdy, p_TCB);
      break;
#endif
    case 2:
      /* Task is waiting to send a message, remove it from the waiting list */
      p_TCB = rt_get_first ((P_XCB)p_CB);
#ifdef __CMSIS_RTOS
      rt_ret_val(p_TCB, 0/*osOK*/);
#else
      rt_ret_val(p_TCB, OS_R_OK);
#endif
      p_CB->msg[p_CB->first] = p_TCB->msg;
      rt_inc (&p_CB->count);
      if (++p_CB->first == p_CB->size) {
        p_CB->first = 0;
      }
      p_TCB->state = READY;
      rt_rmv_dly (p_TCB);
      rt_put_prio (&os_rdy, p_TCB);
      break;
    case 1:
      /* Task is waiting for a message, pass the message to the task directly */
      p_TCB = rt_get_first ((P_XCB)p_CB);
#ifdef __CMSIS_RTOS
      rt_ret_val2(p_TCB, 0x10/*osEventMessage*/, (U32)p_msg);
#else
      *p_TCB->msg = p_msg;
      rt_ret_val (p_TCB, OS_R_MBX);
#endif
      p_TCB->state = READY;
      rt_rmv_dly (p_TCB);
      rt_put_prio (&os_rdy, p_TCB);
      break;
  }
