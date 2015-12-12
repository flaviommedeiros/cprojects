#ifdef NOT_YET_READY_FOR_8_BYTE_POINTERS
if (file_length >= ULL(1) << 56)
      def=8;
    else
#endif
    if (file_length >= ULL(1) << 48)
      def=7;
    else if (file_length >= ULL(1) << 40)
      def=6;
    else if (file_length >= ULL(1) << 32)
      def=5;
    else if (file_length >= ULL(1) << 24)
      def=4;
    else if (file_length >= ULL(1) << 16)
      def=3;
    else
      def=2;
