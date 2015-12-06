if(	!(p1 = (t_AEP_ModExp *)     DSO_bind_func( aep_dso,AEP_F1))  ||
		!(p2 = (t_AEP_ModExpCrt*)   DSO_bind_func( aep_dso,AEP_F2))  ||
#ifdef AEPRAND
		!(p3 = (t_AEP_GenRandom*)   DSO_bind_func( aep_dso,AEP_F3))  ||
#endif
		!(p4 = (t_AEP_Finalize*)    DSO_bind_func( aep_dso,AEP_F4))  ||
		!(p5 = (t_AEP_Initialize*)  DSO_bind_func( aep_dso,AEP_F5))  ||
		!(p6 = (t_AEP_OpenConnection*) DSO_bind_func( aep_dso,AEP_F6))  ||
		!(p7 = (t_AEP_SetBNCallBacks*) DSO_bind_func( aep_dso,AEP_F7))  ||
		!(p8 = (t_AEP_CloseConnection*) DSO_bind_func( aep_dso,AEP_F8)))
		{
		AEPHKerr(AEPHK_F_AEP_INIT,AEPHK_R_NOT_LOADED);
		goto err;
		}
