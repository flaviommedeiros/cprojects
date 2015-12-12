switch (op)
    {
    case OP_END:
    return;

#ifdef SUPPORT_UTF
    case OP_CHAR:
    case OP_CHARI:
    case OP_NOT:
    case OP_NOTI:
    case OP_STAR:
    case OP_MINSTAR:
    case OP_PLUS:
    case OP_MINPLUS:
    case OP_QUERY:
    case OP_MINQUERY:
    case OP_UPTO:
    case OP_MINUPTO:
    case OP_EXACT:
    case OP_POSSTAR:
    case OP_POSPLUS:
    case OP_POSQUERY:
    case OP_POSUPTO:
    case OP_STARI:
    case OP_MINSTARI:
    case OP_PLUSI:
    case OP_MINPLUSI:
    case OP_QUERYI:
    case OP_MINQUERYI:
    case OP_UPTOI:
    case OP_MINUPTOI:
    case OP_EXACTI:
    case OP_POSSTARI:
    case OP_POSPLUSI:
    case OP_POSQUERYI:
    case OP_POSUPTOI:
    case OP_NOTSTAR:
    case OP_NOTMINSTAR:
    case OP_NOTPLUS:
    case OP_NOTMINPLUS:
    case OP_NOTQUERY:
    case OP_NOTMINQUERY:
    case OP_NOTUPTO:
    case OP_NOTMINUPTO:
    case OP_NOTEXACT:
    case OP_NOTPOSSTAR:
    case OP_NOTPOSPLUS:
    case OP_NOTPOSQUERY:
    case OP_NOTPOSUPTO:
    case OP_NOTSTARI:
    case OP_NOTMINSTARI:
    case OP_NOTPLUSI:
    case OP_NOTMINPLUSI:
    case OP_NOTQUERYI:
    case OP_NOTMINQUERYI:
    case OP_NOTUPTOI:
    case OP_NOTMINUPTOI:
    case OP_NOTEXACTI:
    case OP_NOTPOSSTARI:
    case OP_NOTPOSPLUSI:
    case OP_NOTPOSQUERYI:
    case OP_NOTPOSUPTOI:
    if (utf) utf16_char = TRUE;
#endif
    /* Fall through. */

    default:
    length = OP_lengths16[op] - 1;
    break;

    case OP_CLASS:
    case OP_NCLASS:
    /* Skip the character bit map. */
    ptr += 32/sizeof(pcre_uint16);
    length = 0;
    break;

    case OP_XCLASS:
    /* LINK_SIZE can be 1 or 2 in 16 bit mode. */
    if (LINK_SIZE > 1)
      length = (int)((((unsigned int)(ptr[0]) << 16) | (unsigned int)(ptr[1]))
        - (1 + LINK_SIZE + 1));
    else
      length = (int)((unsigned int)(ptr[0]) - (1 + LINK_SIZE + 1));

    /* Reverse the size of the XCLASS instance. */
    *ptr = swap_uint16(*ptr);
    ptr++;
    if (LINK_SIZE > 1)
      {
      *ptr = swap_uint16(*ptr);
      ptr++;
      }

    op = *ptr;
    *ptr = swap_uint16(op);
    ptr++;
    if ((op & XCL_MAP) != 0)
      {
      /* Skip the character bit map. */
      ptr += 32/sizeof(pcre_uint16);
      length -= 32/sizeof(pcre_uint16);
      }
    break;
    }
