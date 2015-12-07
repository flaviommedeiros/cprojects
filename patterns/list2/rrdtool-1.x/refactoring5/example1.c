#ifdef HAVE_LIBRADOS
if (rrd_file->rados)
        ret = rrd_rados_close(rrd_file->rados);
    else
#endif
    ret = close(rrd_simple_file->fd);
