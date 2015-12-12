const zend_function_entry swoole_functions[] =
{
    PHP_FE(swoole_version, NULL)
    PHP_FE(swoole_cpu_num, NULL)
    /*------swoole_server-----*/
    PHP_FE(swoole_server_create, arginfo_swoole_server_create)
    PHP_FE(swoole_server_set, arginfo_swoole_server_set)
    PHP_FE(swoole_server_start, arginfo_swoole_server_start)
    PHP_FE(swoole_server_send, arginfo_swoole_server_send)
    PHP_FE(swoole_server_sendfile, arginfo_swoole_server_sendfile)
    PHP_FE(swoole_server_close, arginfo_swoole_server_close)
    PHP_FE(swoole_server_handler, arginfo_swoole_server_handler)
    PHP_FE(swoole_server_on, arginfo_swoole_server_on)
    PHP_FE(swoole_server_addlisten, arginfo_swoole_server_addlisten)
    PHP_FE(swoole_server_addtimer, arginfo_swoole_server_addtimer)
    PHP_FE(swoole_server_gettimer, NULL)
    PHP_FE(swoole_server_task, arginfo_swoole_server_task)
    PHP_FE(swoole_server_taskwait, arginfo_swoole_server_taskwait)
    PHP_FE(swoole_server_finish, arginfo_swoole_server_finish)
    PHP_FE(swoole_server_reload, arginfo_swoole_server_reload)
    PHP_FE(swoole_server_shutdown, arginfo_swoole_server_shutdown)
    PHP_FE(swoole_server_heartbeat, arginfo_swoole_server_heartbeat)
    PHP_FE(swoole_connection_info, arginfo_swoole_connection_info)
    PHP_FE(swoole_connection_list, arginfo_swoole_connection_list)
    /*------swoole_event-----*/
    PHP_FE(swoole_event_add, arginfo_swoole_event_add)
    PHP_FE(swoole_event_set, NULL)
    PHP_FE(swoole_event_del, arginfo_swoole_event_del)
    PHP_FE(swoole_event_exit, arginfo_swoole_void)
    PHP_FE(swoole_event_wait, arginfo_swoole_void)
    PHP_FE(swoole_event_write, arginfo_swoole_event_write)
    /*------swoole_timer-----*/
    PHP_FE(swoole_timer_add, arginfo_swoole_timer_add)
    PHP_FE(swoole_timer_del, arginfo_swoole_timer_del)
    PHP_FE(swoole_timer_after, NULL)
    PHP_FE(swoole_timer_tick, NULL)
    PHP_FE(swoole_timer_clear, NULL)
    /*------swoole_async_io------*/
    PHP_FE(swoole_async_set, NULL)
    PHP_FE(swoole_async_read, NULL)
    PHP_FE(swoole_async_write, NULL)
    PHP_FE(swoole_async_readfile, NULL)
    PHP_FE(swoole_async_writefile, NULL)
    PHP_FE(swoole_async_dns_lookup, NULL)
    /*------other-----*/
    PHP_FE(swoole_client_select, NULL)
    PHP_FE(swoole_set_process_name, NULL)
    PHP_FE(swoole_get_local_ip, NULL)
    PHP_FE(swoole_strerror, NULL)
    PHP_FE(swoole_errno, NULL)
    /*------async mysql-----*/
#ifdef SW_ASYNC_MYSQL
    PHP_FE(swoole_get_mysqli_sock, NULL)
#endif
    PHP_FE_END /* Must be the last line in swoole_functions[] */
};
