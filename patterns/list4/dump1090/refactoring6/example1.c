if ((Modes.fd = open(Modes.filename,
#ifdef _WIN32
                                    (O_RDONLY | O_BINARY)
#else
                                    (O_RDONLY)
#endif
                                    )) == -1) {
            perror("Opening data file");
            exit(1);
        }
