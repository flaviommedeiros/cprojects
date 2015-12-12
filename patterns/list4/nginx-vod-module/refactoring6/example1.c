if (file->use_event
            || (file->event == NULL
                && (of->uniq == 0 || of->uniq == file->uniq)
                && now - file->created < of->valid
#if (NGX_HAVE_OPENAT)
                && of->disable_symlinks == file->disable_symlinks
                && of->disable_symlinks_from == file->disable_symlinks_from
#endif
            ))
        {
            /* initially had a cache miss, but now that the open completed, there's a cache hit
                closing the file handle and using the cached handle instead */
            if (of->fd != NGX_INVALID_FILE) {

                ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, log, 0, "file cleanup: fd:%d",
                               of->fd);

                if (ngx_close_file(of->fd) == NGX_FILE_ERROR) {
                    ngx_log_error(NGX_LOG_ALERT, log, ngx_errno,
                                  ngx_close_file_n " \"%s\" failed", name->data);
                }
                of->fd = NGX_INVALID_FILE;
            }
            
            if (file->err == 0) {
                of->err = 0;
                of->failed = NULL;

                of->fd = file->fd;
                of->uniq = file->uniq;
                of->mtime = file->mtime;
                of->size = file->size;

                of->is_dir = file->is_dir;
                of->is_file = file->is_file;
                of->is_link = file->is_link;
                of->is_exec = file->is_exec;
                of->is_directio = file->is_directio;

                if (!file->is_dir) {
                    file->count++;
                    ngx_open_file_add_event(cache, file, of, log);
                }

            } else {
                of->err = file->err;
#if (NGX_HAVE_OPENAT)
                of->failed = file->disable_symlinks ? ngx_openat_file_n
                                                    : ngx_open_file_n;
#else
                of->failed = ngx_open_file_n;
#endif
            }

            goto found;
        }
