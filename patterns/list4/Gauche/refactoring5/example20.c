#       ifdef ENABLE_DISCLAIM
if ((hhdr -> hb_flags & HAS_DISCLAIM) != 0) {
            GC_disclaim_and_reclaim_or_free_small_block(hbp);
          } else
#       endif
          /* else */ {
            GC_bytes_found += HBLKSIZE;
            GC_freehblk(hbp);
          }
