#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (root != MPI_PROC_NULL && (was_recorded || env_mpi_ignore_filter))
            {
              VT_MPI_INT me, N, sendcount, sendsz, recvsz, i;
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

              sendcount = sendsz = 0;
              if (iam_root)
                {
                  PMPI_Comm_size(comm, &N);
                  PMPI_Type_size(sendtype, &sendsz);
                  for (i = 0; i < N; i++) sendcount += sendcounts[i];
                }

#if defined(HAVE_DECL_MPI_IN_PLACE) && HAVE_DECL_MPI_IN_PLACE
              if (recvbuf == MPI_IN_PLACE)
                {
                  recvtype = sendtype;
                  recvcount = sendcount;
                }
#endif /* HAVE_DECL_MPI_IN_PLACE */

              PMPI_Type_size(recvtype, &recvsz);

              matchid = VTTHRD_MPICOLLOP_NEXT_MATCHINGID(VTThrdv[tid]);

              vt_mpi_collbegin(tid, &time, vt_mpi_regid[VT__MPI_SCATTERV],
                               matchid, VT_RANK_TO_PE(root, comm),
                               VT_COMM_ID(comm), sendcount * sendsz,
                               recvcount * recvsz);
            }
        }
