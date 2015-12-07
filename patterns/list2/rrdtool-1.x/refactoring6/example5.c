if (
#ifdef HAVE_GETEUID
                   geteuid()
#else
                   1
#endif
                   == 0) {

#ifdef HAVE_CHROOT
                if (chroot(argv[2]) != 0){
                    fprintf(stderr, "ERROR: chroot %s: %s\n", argv[2],rrd_strerror(errno));
                    exit(errno);
                }
                ChangeRoot = 1;
                firstdir = "/";
#else
                fprintf(stderr,
                        "ERROR: change root is not supported by your OS "
                        "or at least by this copy of rrdtool\n");
                exit(1);
#endif
            } else {
                firstdir = argv[2];
            }
