#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (root != MPI_PROC_NULL && (was_recorded || env_mpi_ignore_filter))
            {
              VT_MPI_INT me, N, recvcount, sendsz, recvsz, i;
              uint8_t iam_root;

#if defined(HAVE_DECL_MPI_ROOT) && HAVE_DECL_MPI_ROOT
              VT_MPI_INT inter;
              PMPI_Comm_test_inter(comm, &inter);
              if (inter)
                {
                  iam_root = (root == MPI_ROOT);
                }
              else
#endif /* HAVE_DECL_MPI_ROOT */
                {
                  PMPI_Comm_rank(comm, &me);
                  iam_root = (root == me);
                }

              recvcount = recvsz = 0;
              if (iam_root)
                {
                  PMPI_Comm_size(comm, &N);
                  PMPI_Type_size(recvtype, &recvsz);
                  for (i = 0; i < N; i++) recvcount += recvcounts[i];
                }

#if defined(HAVE_DECL_MPI_IN_PLACE) && HAVE_DECL_MPI_IN_PLACE
              if (sendbuf == MPI_IN_PLACE)
                {
                  sendtype = recvtype;
                  sendcount = recvcount;
                }
#endif /* HAVE_DECL_MPI_IN_PLACE */

              PMPI_Type_size(sendtype, &sendsz);

              matchid = VTTHRD_MPICOLLOP_NEXT_MATCHINGID(VTThrdv[tid]);

              vt_mpi_collbegin(tid, &time, vt_mpi_regid[VT__MPI_GATHERV],
                               matchid, VT_RANK_TO_PE(root, comm),
                               VT_COMM_ID(comm), sendcount * sendsz,
                               recvcount * recvsz);
            }
        }
