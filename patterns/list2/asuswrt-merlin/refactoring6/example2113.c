if( addr->sa_family == 0 
#if defined(AF_LOCAL)
		|| addr->sa_family == AF_LOCAL 
#endif
#if defined(AF_UNIX)
		|| addr->sa_family == AF_UNIX 
#endif
		){
		SNPRINTF (str, len) "%s", Unix_socket_path_DYN );
