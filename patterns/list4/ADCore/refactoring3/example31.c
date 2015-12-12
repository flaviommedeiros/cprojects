switch(xtype) {
      case NC_NAT: nm = "undefined"; break;
      case NC_BYTE: nm = "byte"; break;
      case NC_CHAR: nm = "char"; break;
      case NC_SHORT: nm = "short"; break;
      case NC_INT: nm = "int"; break;
      case NC_FLOAT: nm = "float"; break;
      case NC_DOUBLE: nm = "double"; break;
      case NC_INT64: nm = "int64"; break;
      case NC_UBYTE: nm = "ubyte"; break;
      case NC_USHORT: nm = "ushort"; break;
      case NC_UINT: nm = "uint"; break;
      case NC_UINT64: nm = "uint64"; break;
#ifdef USE_NETCDF4
      case NC_STRING: nm = "string"; break;
#endif
      default: break;
   }
