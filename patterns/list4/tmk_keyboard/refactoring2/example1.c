#if LWIP_TCPIP_CORE_LOCKING
if ((conn->flags & NETCONN_FLAG_WRITE_DELAYED) != 0)
#endif
    {
      sys_sem_signal(&conn->op_completed);
    }
