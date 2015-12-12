switch ((enum ha_base_keytype) keyseg->type) {
    case HA_KEYTYPE_INT8:
      RT_PERIM_INC_KORR(int8, mi_sint1korr, 1);
      break;
    case HA_KEYTYPE_BINARY:
      RT_PERIM_INC_KORR(uint8, mi_uint1korr, 1);
      break;
    case HA_KEYTYPE_SHORT_INT:
      RT_PERIM_INC_KORR(int16, mi_sint2korr, 2);
      break;
    case HA_KEYTYPE_USHORT_INT:
      RT_PERIM_INC_KORR(uint16, mi_uint2korr, 2);
      break;
    case HA_KEYTYPE_INT24:
      RT_PERIM_INC_KORR(int32, mi_sint3korr, 3);
      break;
    case HA_KEYTYPE_UINT24:
      RT_PERIM_INC_KORR(int32, mi_uint3korr, 3);
      break;
    case HA_KEYTYPE_LONG_INT:
      RT_PERIM_INC_KORR(int32, mi_sint4korr, 4);
      break;
    case HA_KEYTYPE_ULONG_INT:
      RT_PERIM_INC_KORR(uint32, mi_uint4korr, 4);
      break;
#ifdef HAVE_LONG_LONG
    case HA_KEYTYPE_LONGLONG:
      RT_PERIM_INC_KORR(longlong, mi_sint8korr, 8);
      break;
    case HA_KEYTYPE_ULONGLONG:
      RT_PERIM_INC_KORR(longlong, mi_sint8korr, 8);
      break;
#endif
    case HA_KEYTYPE_FLOAT:
      RT_PERIM_INC_GET(float, mi_float4get, 4);
      break;
    case HA_KEYTYPE_DOUBLE:
      RT_PERIM_INC_GET(double, mi_float8get, 8);
      break;
    case HA_KEYTYPE_END:
      return *ab_perim - a_perim;
    default:
      return -1;
    }
