switch (index) {
#ifdef CONFIG_SLIRP
    case QEMU_OPTION_smb:
#if 1
        net_slirp_smb(optarg);
#else
        if (net_slirp_smb(optarg) < 0)
            exit(1);
#endif
        break;
#endif
    case QEMU_OPTION_runas:
        user_pwd = getpwnam(optarg);
        if (!user_pwd) {
            fprintf(stderr, "User \"%s\" doesn't exist\n", optarg);
            exit(1);
        }
        break;
    case QEMU_OPTION_chroot:
        chroot_dir = optarg;
        break;
    case QEMU_OPTION_daemonize:
        daemonize = 1;
        break;
    }
