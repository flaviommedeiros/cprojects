#ifdef SUPPORT_UTF
if (xclass && (!should_flip_negation || (options & PCRE_UCP) != 0))
#elif !defined COMPILE_PCRE8
    if (xclass && !should_flip_negation)
#endif
#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
      {
      *class_uchardata++ = XCL_END;    /* Marks the end of extra data */
      *code++ = OP_XCLASS;
      code += LINK_SIZE;
      *code = negate_class? XCL_NOT:0;

      /* If the map is required, move up the extra data to make room for it;
      otherwise just move the code pointer to the end of the extra data. */

      if (class_has_8bitchar > 0)
        {
        *code++ |= XCL_MAP;
        memmove(code + (32 / sizeof(pcre_uchar)), code,
          IN_UCHARS(class_uchardata - code));
        memcpy(code, classbits, 32);
        code = class_uchardata + (32 / sizeof(pcre_uchar));
        }
      else code = class_uchardata;

      /* Now fill in the complete length of the item */

      PUT(previous, 1, (int)(code - previous));
      break;   /* End of class handling */
      }
