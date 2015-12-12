switch (lc->cmd)
      {
        case LC_SEGMENT:
        {
          struct segment_command * sc = (struct segment_command *) lc;
          if (strcmp (sc->segname, "__TEXT") == 0)
            text_base = sc->vmaddr + slide;
          break;
        }
        case LC_SEGMENT_64:
        {
          struct segment_command_64 * sc = (struct segment_command_64 *) lc;
          if (strcmp (sc->segname, "__TEXT") == 0)
            text_base = sc->vmaddr + slide;
          break;
        }
#ifdef HAVE_I386
        case LC_UNIXTHREAD:
        {
          guint8 * thread = p + sizeof (struct thread_command);
          while (thread != p + lc->cmdsize)
          {
            thread_state_flavor_t * flavor = (thread_state_flavor_t *) thread;
            mach_msg_type_number_t * count = (mach_msg_type_number_t *)
                (flavor + 1);
            if (header->magic == MH_MAGIC && *flavor == x86_THREAD_STATE32)
            {
              x86_thread_state32_t * ts = (x86_thread_state32_t *) (count + 1);
              ctx->result = ts->__eip + slide;
            }
            else if (header->magic == MH_MAGIC_64 &&
                *flavor == x86_THREAD_STATE64)
            {
              x86_thread_state64_t * ts = (x86_thread_state64_t *) (count + 1);
              ctx->result = ts->__rip + slide;
            }
            thread = ((guint8 *) (count + 1)) + (*count * sizeof (int));
          }
          break;
        }
#endif
        case LC_MAIN:
        {
          struct entry_point_command * ec = (struct entry_point_command *) p;
          text_offset = ec->entryoff;
          break;
        }
      }
