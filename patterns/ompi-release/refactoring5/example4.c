#ifdef OTFMERGE_MPI
if( i > 0) {

                /* send number of output-streams to rank i */
                MPI_Ssend( &(rank_data.num_ostreams), 1, MPI_INT, i, 0,
                           MPI_COMM_WORLD);

            } else
#endif /* OTFMERGE_MPI */
            {

                /* save number of output-streams for rank 0 in rank_data */
                rank_data.ostreams =
                    (OutStream*) malloc( rank_data.num_ostreams *
                        sizeof(OutStream) );

            }
