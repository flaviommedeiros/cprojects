switch( p->p_type ) {
#     ifdef PT_GNU_RELRO
        case PT_GNU_RELRO:
        /* This entry is known to be constant and will eventually be remapped
           read-only.  However, the address range covered by this entry is
           typically a subset of a previously encountered "LOAD" segment, so
           we need to exclude it.  */
        {
            int j;

            start = ((ptr_t)(p->p_vaddr)) + info->dlpi_addr;
            end = start + p->p_memsz;
            for (j = n_load_segs; --j >= 0; ) {
              if ((word)start >= (word)load_segs[j].start
                  && (word)start < (word)load_segs[j].end) {
                if (load_segs[j].start2 != 0) {
                  WARN("More than one GNU_RELRO segment per load seg\n",0);
                } else {
                  GC_ASSERT((word)end <= (word)load_segs[j].end);
                  /* Remove from the existing load segment */
                  load_segs[j].end2 = load_segs[j].end;
                  load_segs[j].end = start;
                  load_segs[j].start2 = end;
                }
                break;
              }
              if (j == 0) WARN("Failed to find PT_GNU_RELRO segment"
                               " inside PT_LOAD region", 0);
            }
        }

        break;
#     endif

      case PT_LOAD:
        {
          GC_has_static_roots_func callback = GC_has_static_roots;
          if( !(p->p_flags & PF_W) ) break;
          start = ((char *)(p->p_vaddr)) + info->dlpi_addr;
          end = start + p->p_memsz;

          if (callback != 0 && !callback(info->dlpi_name, start, p->p_memsz))
            break;
#         ifdef PT_GNU_RELRO
            if (n_load_segs >= MAX_LOAD_SEGS) ABORT("Too many PT_LOAD segs");
#           if CPP_WORDSZ == 64
              /* FIXME: GC_push_all eventually does the correct         */
              /* rounding to the next multiple of ALIGNMENT, so, most   */
              /* probably, we should remove the corresponding assertion */
              /* check in GC_add_roots_inner along with this code line. */
              /* start pointer value may require aligning */
              start = (ptr_t)((word)start & ~(sizeof(word) - 1));
#           endif
            load_segs[n_load_segs].start = start;
            load_segs[n_load_segs].end = end;
            load_segs[n_load_segs].start2 = 0;
            load_segs[n_load_segs].end2 = 0;
            ++n_load_segs;
#         else
            GC_add_roots_inner(start, end, TRUE);
#         endif /* PT_GNU_RELRO */
        }
      break;
      default:
        break;
    }
