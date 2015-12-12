switch ((enum ha_base_keytype) keyseg->type) {
    case HA_KEYTYPE_INT8:
      RT_D_MBR_KORR(int8, mi_sint1korr, 1, (double));
      break;
    case HA_KEYTYPE_BINARY:
      RT_D_MBR_KORR(uint8, mi_uint1korr, 1, (double));
      break;
    case HA_KEYTYPE_SHORT_INT:
      RT_D_MBR_KORR(int16, mi_sint2korr, 2, (double));
      break;
    case HA_KEYTYPE_USHORT_INT:
      RT_D_MBR_KORR(uint16, mi_uint2korr, 2, (double));
      break;
    case HA_KEYTYPE_INT24:
      RT_D_MBR_KORR(int32, mi_sint3korr, 3, (double));
      break;
    case HA_KEYTYPE_UINT24:
      RT_D_MBR_KORR(uint32, mi_uint3korr, 3, (double));
      break;
    case HA_KEYTYPE_LONG_INT:
      RT_D_MBR_KORR(int32, mi_sint4korr, 4, (double));
      break;
    case HA_KEYTYPE_ULONG_INT:
      RT_D_MBR_KORR(uint32, mi_uint4korr, 4, (double));
      break;
#ifdef HAVE_LONG_LONG
    case HA_KEYTYPE_LONGLONG:
      RT_D_MBR_KORR(longlong, mi_sint8korr, 8, (double));
      break;
    case HA_KEYTYPE_ULONGLONG:
      RT_D_MBR_KORR(longlong, mi_sint8korr, 8, ulonglong2double);
      break;
#endif
    case HA_KEYTYPE_FLOAT:
      RT_D_MBR_GET(float, mi_float4get, 4, (double));
      break;
    case HA_KEYTYPE_DOUBLE:
      RT_D_MBR_GET(double, mi_float8get, 8, (double));
      break;
    case HA_KEYTYPE_END:
      key_length = 0;
      break;
    default:
      return 1;
    }
