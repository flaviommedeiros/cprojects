static FT_Vector  dummy_vec_1[4] =
  {
#if 1
    XVEC( 408.9111, 535.3164 ),
    XVEC( 455.8887, 634.396  ),
    XVEC( -37.8765, 786.2207 ),
    XVEC( 164.6074, 535.3164 )
#else
    { (FT_Int32)0x0198E93DL , (FT_Int32)0x021750FFL },  /* 408.9111, 535.3164 */
    { (FT_Int32)0x01C7E312L , (FT_Int32)0x027A6560L },  /* 455.8887, 634.3960 */
    { (FT_Int32)0xFFDA1F9EL , (FT_Int32)0x0312387FL },  /* -37.8765, 786.2207 */
    { (FT_Int32)0x00A49B7EL , (FT_Int32)0x021750FFL }   /* 164.6074, 535.3164 */
#endif
   };
