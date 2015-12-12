switch ((enum ha_base_keytype) keyseg->type) {
    case HA_KEYTYPE_INT8:
      RT_COMB_KORR(int8, mi_sint1korr, mi_int1store, 1);
      break;
    case HA_KEYTYPE_BINARY:
      RT_COMB_KORR(uint8, mi_uint1korr, mi_int1store, 1);
      break;
    case HA_KEYTYPE_SHORT_INT:
      RT_COMB_KORR(int16, mi_sint2korr, mi_int2store, 2);
      break;
    case HA_KEYTYPE_USHORT_INT:
      RT_COMB_KORR(uint16, mi_uint2korr, mi_int2store, 2);
      break;
    case HA_KEYTYPE_INT24:
      RT_COMB_KORR(int32, mi_sint3korr, mi_int3store, 3);
      break;
    case HA_KEYTYPE_UINT24:
      RT_COMB_KORR(uint32, mi_uint3korr, mi_int3store, 3);
      break;
    case HA_KEYTYPE_LONG_INT:
      RT_COMB_KORR(int32, mi_sint4korr, mi_int4store, 4);
      break;
    case HA_KEYTYPE_ULONG_INT:
      RT_COMB_KORR(uint32, mi_uint4korr, mi_int4store, 4);
      break;
#ifdef HAVE_LONG_LONG
    case HA_KEYTYPE_LONGLONG:
      RT_COMB_KORR(longlong, mi_sint8korr, mi_int8store, 8);
      break;
    case HA_KEYTYPE_ULONGLONG:
      RT_COMB_KORR(ulonglong, mi_uint8korr, mi_int8store, 8);
      break;
#endif
    case HA_KEYTYPE_FLOAT:
      RT_COMB_GET(float, mi_float4get, mi_float4store, 4);
      break;
    case HA_KEYTYPE_DOUBLE:
      RT_COMB_GET(double, mi_float8get, mi_float8store, 8);
      break;
    case HA_KEYTYPE_END:
      return 0;
    default:
      return 1;
    }
