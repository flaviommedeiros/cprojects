#ifdef _WIN32
if (FD_ISSET (handle, (fd_set *)vec_eo)) events |= EV_WRITE;
