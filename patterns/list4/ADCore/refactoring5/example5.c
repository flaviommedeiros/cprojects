#ifdef USE_DAP
if(model == (NC_DISPATCH_NC4 | NC_DISPATCH_NCD))
	dispatcher = NCD4_dispatch_table;
   else
#endif
   if(model == (NC_DISPATCH_NC4))
	dispatcher = NC4_dispatch_table;
   else
#endif /*USE_NETCDF4*/
#ifdef USE_DAP
   if(model == (NC_DISPATCH_NC3 | NC_DISPATCH_NCD))
	dispatcher = NCD3_dispatch_table;
   else
#endif
   if(model == (NC_DISPATCH_NC3))
	dispatcher = NC3_dispatch_table;
   else
      return  NC_ENOTNC;
