switch (*s) {
        case 'r': rdwr = O_RDONLY;  break;
        case 'w': rdwr = O_WRONLY; flags |= O_CREAT | O_TRUNC;  break;
        case 'a': rdwr = O_WRONLY; flags |= O_CREAT | O_APPEND;  break;
        case '+': rdwr = O_RDWR;  break;
#ifdef O_CLOEXEC
        case 'e': flags |= O_CLOEXEC;  break;
#endif
#ifdef O_EXCL
        case 'x': flags |= O_EXCL;  break;
#endif
        default:  break;
        }
