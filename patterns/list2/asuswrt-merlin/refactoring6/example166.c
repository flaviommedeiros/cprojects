if (rename(buf[4], buf[3]) < 0 && errno != ENOENT
#ifdef ENOTDIR
        && errno != ENOTDIR
#endif
        ) {
        BIO_printf(bio_err, "unable to rename %s to %s\n", buf[4], buf[3]);
        perror("reason");
        rename(dbfile, buf[0]);
        rename(buf[1], dbfile);
        goto err;
    }
