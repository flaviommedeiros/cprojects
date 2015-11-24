#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (was_recorded || env_mpi_ignore_filter)
            {
              VT_MPI_INT N, sendcount = 0, recvcount = 0, sendsz, recvsz, i;
              matchid = VTTHRD_MPICOLLOP_NEXT_MATCHINGID(VTThrdv[tid]);

              PMPI_Comm_size(comm, &N);
              for (i = 0; i < N; i++)
                {
                  PMPI_Type_size(recvtypes[i], &recvsz);
                  PMPI_Type_size(sendtypes[i], &sendsz);
                  recvcount += recvsz * recvcounts[i];
                  sendcount += sendsz * sendcounts[i];
                }

              vt_mpi_collbegin(tid, &time, vt_mpi_regid[VT__MPI_ALLTOALLW],
                               matchid, VT_NO_ID, VT_COMM_ID(comm),
                               sendcount, recvcount);
            }
        }
