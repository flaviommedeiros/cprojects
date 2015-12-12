#ifdef USE_DAP
if(model == (NC_DISPATCH_NC3 | NC_DISPATCH_NCD))
	dispatcher = NCD3_dispatch_table;
   else
#endif
   if(model == (NC_DISPATCH_NC3))
	dispatcher = NC3_dispatch_table;
   else
      return  NC_ENOTNC;
