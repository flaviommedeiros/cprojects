# if defined(__linux__)
if (no_pwritev)
# endif
    {
      off_t written;
      size_t index;

# if defined(__linux__)
    retry:
# endif
      written = 0;
      index = 0;
      r = 0;
      do {
        if (req->bufs[index].len > 0) {
          r = pwrite(req->file,
                     req->bufs[index].base,
                     req->bufs[index].len,
                     req->off + written);
          if (r > 0)
            written += r;
        }
        index++;
      } while (index < req->nbufs && r >= 0);
      if (written > 0)
        r = written;
    }
# if defined(__linux__)
    else {
      r = uv__pwritev(req->file,
                      (struct iovec*) req->bufs,
                      req->nbufs,
                      req->off);
      if (r == -1 && errno == ENOSYS) {
        no_pwritev = 1;
        goto retry;
      }
    }
