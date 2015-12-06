STATIC const mp_map_elem_t mp_module_socket_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_usocket) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_socket), (mp_obj_t)&usocket_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_getaddrinfo), (mp_obj_t)&mod_socket_getaddrinfo_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_inet_pton), (mp_obj_t)&mod_socket_inet_pton_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_sockaddr), (mp_obj_t)&mod_socket_sockaddr_obj },
#if MICROPY_SOCKET_EXTRA
    { MP_OBJ_NEW_QSTR(MP_QSTR_htons), (mp_obj_t)&mod_socket_htons_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_gethostbyname), (mp_obj_t)&mod_socket_gethostbyname_obj },
#endif

#define C(name) { MP_OBJ_NEW_QSTR(MP_QSTR_ ## name), MP_OBJ_NEW_SMALL_INT(name) }
    C(AF_UNIX),
    C(AF_INET),
    C(AF_INET6),
    C(SOCK_STREAM),
    C(SOCK_DGRAM),
    C(SOCK_RAW),

    C(MSG_DONTROUTE),
    C(MSG_DONTWAIT),

    C(SOL_SOCKET),
    C(SO_BROADCAST),
    C(SO_ERROR),
    C(SO_KEEPALIVE),
    C(SO_LINGER),
    C(SO_REUSEADDR),
#undef C
};
