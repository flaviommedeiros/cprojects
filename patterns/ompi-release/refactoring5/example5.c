#ifdef OTFMERGE_MPI
if( i > 0 ) {

                    /* send data to rank */
                    MPI_Ssend( &(ostreams[offset + j].id), 1, MPI_INT, i, 0,
                               MPI_COMM_WORLD);
                    MPI_Ssend( &(ostreams[offset + j].num_cpus), 1, MPI_INT, i, 0,
                               MPI_COMM_WORLD);
                    MPI_Ssend( ostreams[offset + j].cpus,
                               ostreams[offset + j].num_cpus, MPI_INT, i, 0,
                               MPI_COMM_WORLD);

                } else
#endif /* OTFMERGE_MPI */
                {

                    /* save data for rank 0 */
                    rank_data.ostreams[j].id = ostreams[offset + j].id;
                    rank_data.ostreams[j].num_cpus =
                        ostreams[offset + j].num_cpus;
                    rank_data.ostreams[j].cpus =
                        (int*) malloc( rank_data.ostreams[j].num_cpus *
                            sizeof(int));
                    memcpy(rank_data.ostreams[j].cpus, ostreams[offset + j].cpus,
                    rank_data.ostreams[j].num_cpus * (sizeof(int)));

                }
