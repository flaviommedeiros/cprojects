switch ((enum ha_base_keytype) keyseg->type) {
    case HA_KEYTYPE_INT8:
      RT_CMP_KORR(int8, mi_sint1korr, 1, nextflag);
      break;
    case HA_KEYTYPE_BINARY:
      RT_CMP_KORR(uint8, mi_uint1korr, 1, nextflag);
      break;
    case HA_KEYTYPE_SHORT_INT:
      RT_CMP_KORR(int16, mi_sint2korr, 2, nextflag);
      break;
    case HA_KEYTYPE_USHORT_INT:
      RT_CMP_KORR(uint16, mi_uint2korr, 2, nextflag);
      break;
    case HA_KEYTYPE_INT24:
      RT_CMP_KORR(int32, mi_sint3korr, 3, nextflag);
      break;
    case HA_KEYTYPE_UINT24:
      RT_CMP_KORR(uint32, mi_uint3korr, 3, nextflag);
      break;
    case HA_KEYTYPE_LONG_INT:
      RT_CMP_KORR(int32, mi_sint4korr, 4, nextflag);
      break;
    case HA_KEYTYPE_ULONG_INT:
      RT_CMP_KORR(uint32, mi_uint4korr, 4, nextflag);
      break;
#ifdef HAVE_LONG_LONG
    case HA_KEYTYPE_LONGLONG:
      RT_CMP_KORR(longlong, mi_sint8korr, 8, nextflag)
      break;
    case HA_KEYTYPE_ULONGLONG:
      RT_CMP_KORR(ulonglong, mi_uint8korr, 8, nextflag)
      break;
#endif
    case HA_KEYTYPE_FLOAT:
      /* The following should be safe, even if we compare doubles */
      RT_CMP_GET(float, mi_float4get, 4, nextflag);
      break;
    case HA_KEYTYPE_DOUBLE:
      RT_CMP_GET(double, mi_float8get, 8, nextflag);
      break;
    case HA_KEYTYPE_END:
      goto end;
    default:
      return 1;
    }
