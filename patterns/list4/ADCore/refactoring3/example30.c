switch(xtype) {
      case NC_NAT: sz = 0; break;
      case NC_BYTE: sz = sizeof(signed char); break;
      case NC_CHAR: sz = sizeof(char); break;
      case NC_SHORT: sz = sizeof(short); break;
      case NC_INT: sz = sizeof(int); break;
      case NC_FLOAT: sz = sizeof(float); break;
      case NC_DOUBLE: sz = sizeof(double); break;
      case NC_INT64: sz = sizeof(signed long long); break;
      case NC_UBYTE: sz = sizeof(unsigned char); break;
      case NC_USHORT: sz = sizeof(unsigned short); break;
      case NC_UINT: sz = sizeof(unsigned int); break;
      case NC_UINT64: sz = sizeof(unsigned long long); break;
#ifdef USE_NETCDF4
      case NC_STRING: sz = sizeof(char*); break;
#endif
      default: break;
   }
