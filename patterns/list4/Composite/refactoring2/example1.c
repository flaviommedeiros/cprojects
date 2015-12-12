#if LWIP_TCPIP_CORE_LOCKING
if (conn->write_delayed != 0)
#endif
    {
      sys_sem_signal(conn->op_completed);
    }
