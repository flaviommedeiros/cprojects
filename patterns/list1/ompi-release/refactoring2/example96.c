#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (target_rank != MPI_PROC_NULL &&
              (was_recorded || env_mpi_ignore_filter))
            {
              MPI_Comm comm;
              VT_MPI_INT sz;
              uint32_t gid, wid;

              PMPI_Type_size(origin_datatype, &sz);
              vt_win_id(win, &comm, &gid, &wid);
              if (is_rma_putre)
                vt_mpi_rma_putre(tid, &time, VT_RANK_TO_PE(target_rank, comm),
                                 gid, wid, sz * origin_count );
              else
                vt_mpi_rma_put(tid, &time, VT_RANK_TO_PE(target_rank, comm),
                               gid, wid, sz * origin_count );
            }
        }
