switch (*p1++)
	      {
              case Cbol:
              case Ceol:
              case Cbegbuf:
              case Cendbuf:
              case Cwordbeg:
              case Cwordend:
              case Cwordbound:
              case Cnotwordbound:
#ifdef EDH
	      case Cwordleft:
	      case Cwordright:
	      case Cnotwordleft:
	      case Cnotwordright:
#endif // EDH
                goto loop_p1;
              case Cstart_memory:
              case Cend_memory:
                p1++;
                goto loop_p1;
	      case Cexact:
		ch = (unsigned char)*p1++;
		if (map[ch])
		  goto make_normal_jump;
		break;
	      case Canychar:
		for (b = 0; b < 256; b++)
		  if (b != '\n' && map[b])
		    goto make_normal_jump;
		break;
	      case Cset:
		for (b = 0; b < 256; b++)
		  if ((p1[b >> 3] & (1 << (b & 7))) && map[b])
		    goto make_normal_jump;
		p1 += 256/8;
		break;
	      default:
		goto make_normal_jump;
	      }
