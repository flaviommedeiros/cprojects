if (!file->use_event
        && (file->event != NULL
            || (of->uniq != 0 && of->uniq != file->uniq)
            || now - file->created >= of->valid
#if (NGX_HAVE_OPENAT)
            || of->disable_symlinks != file->disable_symlinks
            || of->disable_symlinks_from != file->disable_symlinks_from
#endif
        ))
    {
        ngx_log_debug4(NGX_LOG_DEBUG_CORE, log, 0,
                       "retest open file: %s, fd:%d, c:%d, e:%d",
                       file->name, file->fd, file->count, file->err);

        if (file->is_dir) {

            /*
             * chances that directory became file are very small
             * so test_dir flag allows to use a single syscall
             * in ngx_file_info() instead of three syscalls
             */

            of->test_dir = 1;
        }
        else if (!file->err)
        {
            /* increment the count to prevent the handle from getting closed by some other request */
            file->count++;

            *out_file = file;
        }

        of->fd = file->fd;
        of->uniq = file->uniq;

        return NGX_DONE;
    }
