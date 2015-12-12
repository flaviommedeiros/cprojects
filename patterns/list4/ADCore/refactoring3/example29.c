switch(type){
      case NC_CHAR :
	 return((int)sizeof(char));
      case NC_BYTE :
	 return((int)sizeof(signed char));
      case NC_SHORT :
	 return(int)(sizeof(short));
      case NC_INT :
	 return((int)sizeof(int));
      case NC_FLOAT :
	 return((int)sizeof(float));
      case NC_DOUBLE : 
	 return((int)sizeof(double));

	 /* These can occur in netcdf-3 code */ 
      case NC_UBYTE :
	 return((int)sizeof(unsigned char));
      case NC_USHORT :
	 return((int)(sizeof(unsigned short)));
      case NC_UINT :
	 return((int)sizeof(unsigned int));
      case NC_INT64 :
	 return((int)sizeof(signed long long));
      case NC_UINT64 :
	 return((int)sizeof(unsigned long long));
#ifdef USE_NETCDF4
      case NC_STRING :
	 return((int)sizeof(char*));
#endif /*USE_NETCDF4*/

      default:
	 return -1;
   }
