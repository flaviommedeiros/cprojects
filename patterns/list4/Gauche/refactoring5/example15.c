#       ifdef MSWINCE
if (result == 0) {
            /* Page is free; advance to the next possible allocation base */
            new_limit = (char *)
                (((DWORD) p + GC_sysinfo.dwAllocationGranularity)
                 & ~(GC_sysinfo.dwAllocationGranularity-1));
          } else
#       endif
        /* else */ {
            if (result != sizeof(buf)) {
                ABORT("Weird VirtualQuery result");
            }
            new_limit = (char *)p + buf.RegionSize;
            protect = buf.Protect;
            if (buf.State == MEM_COMMIT
                && (protect == PAGE_EXECUTE_READWRITE
                    || protect == PAGE_READWRITE)
                && (buf.Type == MEM_IMAGE
#                   ifdef GC_REGISTER_MEM_PRIVATE
                      || (protect == PAGE_READWRITE && buf.Type == MEM_PRIVATE)
#                   else
                      /* There is some evidence that we cannot always   */
                      /* ignore MEM_PRIVATE sections under Windows ME   */
                      /* and predecessors.  Hence we now also check for */
                      /* that case.                                     */
                      || (!GC_wnt && buf.Type == MEM_PRIVATE)
#                   endif
                   )
                && !GC_is_heap_base(buf.AllocationBase)) {
#               ifdef DEBUG_VIRTUALQUERY
                  GC_dump_meminfo(&buf);
#               endif
                if ((char *)p != limit) {
                    GC_cond_add_roots(base, limit);
                    base = p;
                }
                limit = new_limit;
            }
        }
