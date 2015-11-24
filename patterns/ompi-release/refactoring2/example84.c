#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (was_recorded || env_mpi_ignore_filter)
            {
              VT_MPI_INT N, sendsz, recvsz;

              matchid = VTTHRD_MPICOLLOP_NEXT_MATCHINGID(VTThrdv[tid]);

              PMPI_Type_size(recvtype, &recvsz);
              PMPI_Type_size(sendtype, &sendsz);
              PMPI_Comm_size(comm, &N);

              vt_mpi_collbegin(tid, &time, vt_mpi_regid[VT__MPI_ALLTOALL],
                               matchid, VT_NO_ID, VT_COMM_ID(comm),
                               sendsz * sendcount * N, recvsz * recvcount * N);
            }
        }
