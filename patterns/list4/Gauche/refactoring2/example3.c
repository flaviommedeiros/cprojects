#    ifndef GC_NO_FINALIZATION
if (GC_general_register_disappearing_link((void * *)((word *)op+lw-1),
                                                 op) == GC_NO_MEMORY)
#    endif
       {
           /* Couldn't register it due to lack of memory.  Punt.        */
           /* This will probably fail too, but gives the recovery code  */
           /* a chance.                                                 */
           return(GC_malloc(n*lb));
       }
