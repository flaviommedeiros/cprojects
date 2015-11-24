#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          struct VTRequest* req;

          req = vt_request_get(*request);
          if (req && (req->flags & ERF_IS_PERSISTENT))
            {
              if (req->flags & ERF_IS_ACTIVE )
                /* mark active requests for deallocation */
                req->flags |= ERF_DEALLOCATE;
              else
                /* deallocate inactive requests -*/
                vt_request_free(req);
            }
          /* -- else non-persistent requests:
                + we don't track non-persistent sends
                + MPI standard strongly suggests to deallocate non-persistent
                  recv's only by waot or test
                ==> nothing to do here
           */
        }
