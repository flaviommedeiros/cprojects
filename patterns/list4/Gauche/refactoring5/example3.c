#     ifdef PROC_VDB
if (GC_dirty_maintained) {
          /* Pages that were never dirtied cannot contain pointers.     */
          GC_push_selected((ptr_t)bottom, (ptr_t)top, GC_page_was_ever_dirty);
        } else
#     endif
      /* else */ {
        GC_push_all(bottom, top);
      }
