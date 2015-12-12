#ifdef _WIN32
if(type & (RB_FD_SOCKET | RB_FD_PIPE)) {
        closesocket(fd);
        return;
    } else
#endif
        close(fd);
