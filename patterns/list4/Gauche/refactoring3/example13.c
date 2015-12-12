switch(kind) {
          case PTRFREE:
            kind_str = "PTRFREE";
            break;
          case NORMAL:
            kind_str = "NORMAL";
            break;
          case UNCOLLECTABLE:
            kind_str = "UNCOLLECTABLE";
            break;
#         ifdef ATOMIC_UNCOLLECTABLE
            case AUNCOLLECTABLE:
              kind_str = "ATOMIC_UNCOLLECTABLE";
              break;
#         endif
          case STUBBORN:
            kind_str = "STUBBORN";
            break;
          default:
            kind_str = NULL;
                /* The alternative is to use snprintf(buffer) but it is */
                /* not quite portable (see vsnprintf in misc.c).        */
        }
