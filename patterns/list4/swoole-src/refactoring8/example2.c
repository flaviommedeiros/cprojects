static zend_function_entry swoole_server_methods[] = {
    PHP_FALIAS(__construct, swoole_server_create, arginfo_swoole_server_create)
    PHP_FALIAS(set, swoole_server_set, arginfo_swoole_server_set_oo)
    PHP_FALIAS(start, swoole_server_start, arginfo_swoole_void)
    PHP_FALIAS(send, swoole_server_send, arginfo_swoole_server_send_oo)
    PHP_ME(swoole_server, sendto, arginfo_swoole_server_sendto_oo, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_server, sendwait, arginfo_swoole_server_sendwait, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_server, exist, arginfo_swoole_server_exist, ZEND_ACC_PUBLIC)
    PHP_FALIAS(sendfile, swoole_server_sendfile, arginfo_swoole_server_sendfile_oo)
    PHP_FALIAS(close, swoole_server_close, arginfo_swoole_server_close_oo)
    PHP_FALIAS(task, swoole_server_task, arginfo_swoole_server_task_oo)
    PHP_FALIAS(taskwait, swoole_server_taskwait, arginfo_swoole_server_taskwait_oo)
    PHP_FALIAS(finish, swoole_server_finish, arginfo_swoole_server_finish_oo)
    PHP_FALIAS(addlistener, swoole_server_addlisten, arginfo_swoole_server_addlisten_oo)
    PHP_FALIAS(listen, swoole_server_addlisten, arginfo_swoole_server_addlisten_oo)
    PHP_FALIAS(reload, swoole_server_reload, arginfo_swoole_server_reload_oo)
    PHP_FALIAS(shutdown, swoole_server_shutdown, arginfo_swoole_void)
    PHP_FALIAS(hbcheck, swoole_server_heartbeat, arginfo_swoole_server_heartbeat_oo)
    PHP_FALIAS(heartbeat, swoole_server_heartbeat, arginfo_swoole_server_heartbeat_oo)
    PHP_FALIAS(handler, swoole_server_handler, arginfo_swoole_server_handler_oo)
    PHP_FALIAS(on, swoole_server_on, arginfo_swoole_server_on_oo)
    PHP_FALIAS(connection_info, swoole_connection_info, arginfo_swoole_connection_info_oo)
    PHP_FALIAS(connection_list, swoole_connection_list, arginfo_swoole_connection_list_oo)
    //psr-0 style
    PHP_FALIAS(getClientInfo, swoole_connection_info, arginfo_swoole_connection_info_oo)
    PHP_FALIAS(getClientList, swoole_connection_list, arginfo_swoole_connection_list_oo)
    //timer
    PHP_FALIAS(addtimer, swoole_server_addtimer, arginfo_swoole_server_addtimer_oo)
    PHP_FALIAS(deltimer, swoole_timer_del, arginfo_swoole_timer_del)
    PHP_FALIAS(gettimer, swoole_server_gettimer, NULL)
    PHP_FALIAS(after, swoole_timer_after, NULL)
    PHP_FALIAS(tick, swoole_timer_tick, NULL)
    PHP_FALIAS(clearTimer, swoole_timer_clear, NULL)
    //process
    PHP_ME(swoole_server, sendmessage, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_server, addprocess, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(swoole_server, stats, NULL, ZEND_ACC_PUBLIC)
#ifdef SWOOLE_SOCKETS_SUPPORT
    PHP_ME(swoole_server, getSocket, NULL, ZEND_ACC_PUBLIC)
#endif
    PHP_ME(swoole_server, bind, arginfo_swoole_server_bind, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};
