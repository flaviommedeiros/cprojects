#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          MPI_Request* request;
          struct VTRequest* req;
          VT_MPI_INT i;

          for (i = 0; i < count; i++)
            {
              request = &array_of_requests[i];
              req = vt_request_get(*request);
              if (req)
                {
                  if (req->flags & ERF_IS_PERSISTENT )
                    {
                      req->flags |= ERF_IS_ACTIVE;
                      if ((req->flags & ERF_SEND) &&
                          (req->dest != MPI_PROC_NULL) &&
                          (was_recorded || env_mpi_ignore_filter))
                        {
                          vt_mpi_send(tid, &time,
                            VT_RANK_TO_PE_BY_GROUP(req->dest, req->group),
                            req->cid, req->tag, req->bytes);
                        }
                    }
                }
            }
        }
