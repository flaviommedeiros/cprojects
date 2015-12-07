# if defined(__linux__)
if (no_preadv)
# endif
    {
      off_t nread;
      size_t index;

# if defined(__linux__)
    retry:
# endif
      nread = 0;
      index = 0;
      result = 1;
      do {
        if (req->bufs[index].len > 0) {
          result = pread(req->file,
                         req->bufs[index].base,
                         req->bufs[index].len,
                         req->off + nread);
          if (result > 0)
            nread += result;
        }
        index++;
      } while (index < req->nbufs && result > 0);
      if (nread > 0)
        result = nread;
    }
# if defined(__linux__)
    else {
      result = uv__preadv(req->file,
                          (struct iovec*)req->bufs,
                          req->nbufs,
                          req->off);
      if (result == -1 && errno == ENOSYS) {
        no_preadv = 1;
        goto retry;
      }
    }
