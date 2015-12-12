switch (seed_type) {
#ifdef HAVE_SSL_RAND_EGD
    case RB_PRNG_EGD:
        if(RAND_egd(path) == -1)
            return -1;
        break;
#endif
    case RB_PRNG_FILE:
        if(RAND_load_file(path, -1) == -1)
            return -1;
        break;
#ifdef _WIN32
    case RB_PRNGWIN32:
        RAND_screen();
        break;
#endif
    default:
        return -1;
    }
