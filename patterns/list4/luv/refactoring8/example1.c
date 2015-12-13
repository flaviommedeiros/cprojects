static const luaL_Reg luv_functions[] = {
  // loop.c
  {"loop_close", luv_loop_close},
  {"run", luv_run},
  {"loop_alive", luv_loop_alive},
  {"stop", luv_stop},
  {"backend_fd", luv_backend_fd},
  {"backend_timeout", luv_backend_timeout},
  {"now", luv_now},
  {"update_time", luv_update_time},
  {"walk", luv_walk},

  // req.c
  {"cancel", luv_cancel},

  // handle.c
  {"is_active", luv_is_active},
  {"is_closing", luv_is_closing},
  {"close", luv_close},
  {"ref", luv_ref},
  {"unref", luv_unref},
  {"has_ref", luv_has_ref},
  {"send_buffer_size", luv_send_buffer_size},
  {"recv_buffer_size", luv_recv_buffer_size},
  {"fileno", luv_fileno},

  // timer.c
  {"new_timer", luv_new_timer},
  {"timer_start", luv_timer_start},
  {"timer_stop", luv_timer_stop},
  {"timer_again", luv_timer_again},
  {"timer_set_repeat", luv_timer_set_repeat},
  {"timer_get_repeat", luv_timer_get_repeat},

  // prepare.c
  {"new_prepare", luv_new_prepare},
  {"prepare_start", luv_prepare_start},
  {"prepare_stop", luv_prepare_stop},

  // check.c
  {"new_check", luv_new_check},
  {"check_start", luv_check_start},
  {"check_stop", luv_check_stop},

  // idle.c
  {"new_idle", luv_new_idle},
  {"idle_start", luv_idle_start},
  {"idle_stop", luv_idle_stop},

  // async.c
  {"new_async", luv_new_async},
  {"async_send", luv_async_send},

  // poll.c
  {"new_poll", luv_new_poll},
  {"new_socket_poll", luv_new_socket_poll},
  {"poll_start", luv_poll_start},
  {"poll_stop", luv_poll_stop},

  // signal.c
  {"new_signal", luv_new_signal},
  {"signal_start", luv_signal_start},
  {"signal_stop", luv_signal_stop},

  // process.c
  {"disable_stdio_inheritance", luv_disable_stdio_inheritance},
  {"spawn", luv_spawn},
  {"process_kill", luv_process_kill},
  {"kill", luv_kill},

  // stream.c
  {"shutdown", luv_shutdown},
  {"listen", luv_listen},
  {"accept", luv_accept},
  {"read_start", luv_read_start},
  {"read_stop", luv_read_stop},
  {"write", luv_write},
  {"write2", luv_write2},
  {"try_write", luv_try_write},
  {"is_readable", luv_is_readable},
  {"is_writable", luv_is_writable},
  {"stream_set_blocking", luv_stream_set_blocking},

  // tcp.c
  {"new_tcp", luv_new_tcp},
  {"tcp_open", luv_tcp_open},
  {"tcp_nodelay", luv_tcp_nodelay},
  {"tcp_keepalive", luv_tcp_keepalive},
  {"tcp_simultaneous_accepts", luv_tcp_simultaneous_accepts},
  {"tcp_bind", luv_tcp_bind},
  {"tcp_getpeername", luv_tcp_getpeername},
  {"tcp_getsockname", luv_tcp_getsockname},
  {"tcp_connect", luv_tcp_connect},
  {"tcp_write_queue_size", luv_write_queue_size},

  // pipe.c
  {"new_pipe", luv_new_pipe},
  {"pipe_open", luv_pipe_open},
  {"pipe_bind", luv_pipe_bind},
  {"pipe_connect", luv_pipe_connect},
  {"pipe_getsockname", luv_pipe_getsockname},
  {"pipe_getpeername", luv_pipe_getpeername},
  {"pipe_pending_instances", luv_pipe_pending_instances},
  {"pipe_pending_count", luv_pipe_pending_count},
  {"pipe_pending_type", luv_pipe_pending_type},

  // tty.c
  {"new_tty", luv_new_tty},
  {"tty_set_mode", luv_tty_set_mode},
  {"tty_reset_mode", luv_tty_reset_mode},
  {"tty_get_winsize", luv_tty_get_winsize},

  // udp.c
  {"new_udp", luv_new_udp},
  {"udp_open", luv_udp_open},
  {"udp_bind", luv_udp_bind},
  {"udp_getsockname", luv_udp_getsockname},
  {"udp_set_membership", luv_udp_set_membership},
  {"udp_set_multicast_loop", luv_udp_set_multicast_loop},
  {"udp_set_multicast_ttl", luv_udp_set_multicast_ttl},
  {"udp_set_multicast_interface", luv_udp_set_multicast_interface},
  {"udp_set_broadcast", luv_udp_set_broadcast},
  {"udp_set_ttl", luv_udp_set_ttl},
  {"udp_send", luv_udp_send},
  {"udp_try_send", luv_udp_try_send},
  {"udp_recv_start", luv_udp_recv_start},
  {"udp_recv_stop", luv_udp_recv_stop},

  // fs_event.c
  {"new_fs_event", luv_new_fs_event},
  {"fs_event_start", luv_fs_event_start},
  {"fs_event_stop", luv_fs_event_stop},
  {"fs_event_getpath", luv_fs_event_getpath},

  // fs_poll.c
  {"new_fs_poll", luv_new_fs_poll},
  {"fs_poll_start", luv_fs_poll_start},
  {"fs_poll_stop", luv_fs_poll_stop},
  {"fs_poll_getpath", luv_fs_poll_getpath},

  // fs.c
  {"fs_close", luv_fs_close},
  {"fs_open", luv_fs_open},
  {"fs_read", luv_fs_read},
  {"fs_unlink", luv_fs_unlink},
  {"fs_write", luv_fs_write},
  {"fs_mkdir", luv_fs_mkdir},
  {"fs_mkdtemp", luv_fs_mkdtemp},
  {"fs_rmdir", luv_fs_rmdir},
  {"fs_scandir", luv_fs_scandir},
  {"fs_scandir_next", luv_fs_scandir_next},
  {"fs_stat", luv_fs_stat},
  {"fs_fstat", luv_fs_fstat},
  {"fs_lstat", luv_fs_lstat},
  {"fs_rename", luv_fs_rename},
  {"fs_fsync", luv_fs_fsync},
  {"fs_fdatasync", luv_fs_fdatasync},
  {"fs_ftruncate", luv_fs_ftruncate},
  {"fs_sendfile", luv_fs_sendfile},
  {"fs_access", luv_fs_access},
  {"fs_chmod", luv_fs_chmod},
  {"fs_fchmod", luv_fs_fchmod},
  {"fs_utime", luv_fs_utime},
  {"fs_futime", luv_fs_futime},
  {"fs_link", luv_fs_link},
  {"fs_symlink", luv_fs_symlink},
  {"fs_readlink", luv_fs_readlink},
  {"fs_chown", luv_fs_chown},
  {"fs_fchown", luv_fs_fchown},

  // dns.c
  {"getaddrinfo", luv_getaddrinfo},
  {"getnameinfo", luv_getnameinfo},

  // misc.c
  {"chdir", luv_chdir},
  {"os_homedir", luv_os_homedir},
  {"cpu_info", luv_cpu_info},
  {"cwd", luv_cwd},
  {"exepath", luv_exepath},
  {"get_process_title", luv_get_process_title},
  {"get_total_memory", luv_get_total_memory},
  {"get_free_memory", luv_get_free_memory},
  {"getpid", luv_getpid},
#ifndef _WIN32
  {"getuid", luv_getuid},
  {"setuid", luv_setuid},
  {"getgid", luv_getgid},
  {"setgid", luv_setgid},
#endif
  {"getrusage", luv_getrusage},
  {"guess_handle", luv_guess_handle},
  {"hrtime", luv_hrtime},
  {"interface_addresses", luv_interface_addresses},
  {"loadavg", luv_loadavg},
  {"resident_set_memory", luv_resident_set_memory},
  {"set_process_title", luv_set_process_title},
  {"uptime", luv_uptime},
  {"version", luv_version},
  {"version_string", luv_version_string},

  // thread.c
  {"new_thread", luv_new_thread},
  {"thread_equal", luv_thread_equal},
  {"thread_self", luv_thread_self},
  {"thread_join", luv_thread_join},
  {"sleep", luv_thread_sleep},

  // work.c
  {"new_work", luv_new_work},
  {"queue_work", luv_queue_work},

  {NULL, NULL}
};