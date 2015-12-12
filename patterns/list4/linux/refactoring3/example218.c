switch (para) {
	case SMT_P10F0 :
	case SMT_P10F1 :
#ifdef	ESS
	case SMT_P10F2 :
	case SMT_P10F3 :
	case SMT_P10F4 :
	case SMT_P10F5 :
	case SMT_P10F6 :
	case SMT_P10F7 :
#endif
#ifdef	SBA
	case SMT_P10F8 :
	case SMT_P10F9 :
#endif
	case SMT_P20F1 :
		if (!local) {
			pcon->pc_err = SMT_RDF_NOPARAM ;
			return ;
		}
		break ;
	case SMT_P2034 :
	case SMT_P2046 :
	case SMT_P2047 :
	case SMT_P204A :
	case SMT_P2051 :
	case SMT_P2052 :
		mac_update_counter(smc) ;
		break ;
	case SMT_P4022:
		mib_p->fddiPORTPC_LS = LS2MIB(
			sm_pm_get_ls(smc,port_to_mib(smc,port))) ;
		break ;
	case SMT_P_REASON :
		*(u32 *)to = 0 ;
		sp_len = 4 ;
		goto sp_done ;
	case SMT_P1033 :			/* time stamp */
		smt_set_timestamp(smc,smc->mib.fddiSMTTimeStamp) ;
		break ;

	case SMT_P1020:				/* port indexes */
#if	NUMPHYS == 12
		swap = "IIIIIIIIIIII" ;
#else
#if	NUMPHYS == 2
		if (smc->s.sas == SMT_SAS)
			swap = "I" ;
		else
			swap = "II" ;
#else
#if	NUMPHYS == 24
		swap = "IIIIIIIIIIIIIIIIIIIIIIII" ;
#else
	????
#endif
#endif
#endif
		break ;
	case SMT_P3212 :
		{
			sp_len = cem_build_path(smc,to,path) ;
			goto sp_done ;
		}
	case SMT_P1048 :		/* peer wrap condition */
		{
			struct smt_p_1048	*sp ;
			sp = (struct smt_p_1048 *) to ;
			sp->p1048_flag = smc->mib.fddiSMTPeerWrapFlag ;
			sp->p1048_cf_state = smc->mib.fddiSMTCF_State ;
			sp_len = sizeof(struct smt_p_1048) ;
			goto sp_done ;
		}
	case SMT_P208C :
		{
			struct smt_p_208c	*sp ;
			sp = (struct smt_p_208c *) to ;
			sp->p208c_flag =
				smc->mib.m[MAC0].fddiMACDuplicateAddressCond ;
			sp->p208c_dupcondition =
				(mib_m->fddiMACDA_Flag ? SMT_ST_MY_DUPA : 0) |
				(mib_m->fddiMACUNDA_Flag ? SMT_ST_UNA_DUPA : 0);
			sp->p208c_fddilong =
				mib_m->fddiMACSMTAddress ;
			sp->p208c_fddiunalong =
				mib_m->fddiMACUpstreamNbr ;
			sp->p208c_pad = 0 ;
			sp_len = sizeof(struct smt_p_208c) ;
			goto sp_done ;
		}
	case SMT_P208D :		/* frame error condition */
		{
			struct smt_p_208d	*sp ;
			sp = (struct smt_p_208d *) to ;
			sp->p208d_flag =
				mib_m->fddiMACFrameErrorFlag ;
			sp->p208d_frame_ct =
				mib_m->fddiMACFrame_Ct ;
			sp->p208d_error_ct =
				mib_m->fddiMACError_Ct ;
			sp->p208d_lost_ct =
				mib_m->fddiMACLost_Ct ;
			sp->p208d_ratio =
				mib_m->fddiMACFrameErrorRatio ;
			sp_len = sizeof(struct smt_p_208d) ;
			goto sp_done ;
		}
	case SMT_P208E :		/* not copied condition */
		{
			struct smt_p_208e	*sp ;
			sp = (struct smt_p_208e *) to ;
			sp->p208e_flag =
				mib_m->fddiMACNotCopiedFlag ;
			sp->p208e_not_copied =
				mib_m->fddiMACNotCopied_Ct ;
			sp->p208e_copied =
				mib_m->fddiMACCopied_Ct ;
			sp->p208e_not_copied_ratio =
				mib_m->fddiMACNotCopiedRatio ;
			sp_len = sizeof(struct smt_p_208e) ;
			goto sp_done ;
		}
	case SMT_P208F :	/* neighbor change event */
		{
			struct smt_p_208f	*sp ;
			sp = (struct smt_p_208f *) to ;
			sp->p208f_multiple =
				mib_m->fddiMACMultiple_N ;
			sp->p208f_nacondition =
				mib_m->fddiMACDuplicateAddressCond ;
			sp->p208f_old_una =
				mib_m->fddiMACOldUpstreamNbr ;
			sp->p208f_new_una =
				mib_m->fddiMACUpstreamNbr ;
			sp->p208f_old_dna =
				mib_m->fddiMACOldDownstreamNbr ;
			sp->p208f_new_dna =
				mib_m->fddiMACDownstreamNbr ;
			sp->p208f_curren_path =
				mib_m->fddiMACCurrentPath ;
			sp->p208f_smt_address =
				mib_m->fddiMACSMTAddress ;
			sp_len = sizeof(struct smt_p_208f) ;
			goto sp_done ;
		}
	case SMT_P2090 :
		{
			struct smt_p_2090	*sp ;
			sp = (struct smt_p_2090 *) to ;
			sp->p2090_multiple =
				mib_m->fddiMACMultiple_P ;
			sp->p2090_availablepaths =
				mib_m->fddiMACAvailablePaths ;
			sp->p2090_currentpath =
				mib_m->fddiMACCurrentPath ;
			sp->p2090_requestedpaths =
				mib_m->fddiMACRequestedPaths ;
			sp_len = sizeof(struct smt_p_2090) ;
			goto sp_done ;
		}
	case SMT_P4050 :
		{
			struct smt_p_4050	*sp ;
			sp = (struct smt_p_4050 *) to ;
			sp->p4050_flag =
				mib_p->fddiPORTLerFlag ;
			sp->p4050_pad = 0 ;
			sp->p4050_cutoff =
				mib_p->fddiPORTLer_Cutoff ;
			sp->p4050_alarm =
				mib_p->fddiPORTLer_Alarm ;
			sp->p4050_estimate =
				mib_p->fddiPORTLer_Estimate ;
			sp->p4050_reject_ct =
				mib_p->fddiPORTLem_Reject_Ct ;
			sp->p4050_ct =
				mib_p->fddiPORTLem_Ct ;
			sp_len = sizeof(struct smt_p_4050) ;
			goto sp_done ;
		}

	case SMT_P4051 :
		{
			struct smt_p_4051	*sp ;
			sp = (struct smt_p_4051 *) to ;
			sp->p4051_multiple =
				mib_p->fddiPORTMultiple_U ;
			sp->p4051_porttype =
				mib_p->fddiPORTMy_Type ;
			sp->p4051_connectstate =
				mib_p->fddiPORTConnectState ;
			sp->p4051_pc_neighbor =
				mib_p->fddiPORTNeighborType ;
			sp->p4051_pc_withhold =
				mib_p->fddiPORTPC_Withhold ;
			sp_len = sizeof(struct smt_p_4051) ;
			goto sp_done ;
		}
	case SMT_P4052 :
		{
			struct smt_p_4052	*sp ;
			sp = (struct smt_p_4052 *) to ;
			sp->p4052_flag =
				mib_p->fddiPORTEB_Condition ;
			sp->p4052_eberrorcount =
				mib_p->fddiPORTEBError_Ct ;
			sp_len = sizeof(struct smt_p_4052) ;
			goto sp_done ;
		}
	case SMT_P4053 :
		{
			struct smt_p_4053	*sp ;
			sp = (struct smt_p_4053 *) to ;
			sp->p4053_multiple =
				mib_p->fddiPORTMultiple_P ;
			sp->p4053_availablepaths =
				mib_p->fddiPORTAvailablePaths ;
			sp->p4053_currentpath =
				mib_p->fddiPORTCurrentPath ;
			memcpy(	(char *) &sp->p4053_requestedpaths,
				(char *) mib_p->fddiPORTRequestedPaths,4) ;
			sp->p4053_mytype =
				mib_p->fddiPORTMy_Type ;
			sp->p4053_neighbortype =
				mib_p->fddiPORTNeighborType ;
			sp_len = sizeof(struct smt_p_4053) ;
			goto sp_done ;
		}
	default :
		break ;
	}
