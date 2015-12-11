static int _01forward(oggpack_buffer *opb,
                      vorbis_look_residue *vl,
                      int **in,int ch,
                      long **partword,
#ifdef TRAIN_RES
                      int (*encode)(oggpack_buffer *,int *,int,
                                    codebook *,long *),
                      int submap
#else
                      int (*encode
