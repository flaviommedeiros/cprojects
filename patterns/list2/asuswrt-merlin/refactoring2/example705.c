#if HCF_DMA
if ( ! ( ifbp->IFB_CntlOpt & USE_DMA ) )
#endif // HCF_DMA
			{
				ifbp->IFB_RscInd = get_fid( ifbp );
				HCFASSERT( ifbp->IFB_RscInd, 0 )
				cmd_exe( ifbp, HCMD_ALLOC, 0 );
				IF_PROT_TIME( if ( prot_cnt == 0 ) rc = HCF_ERR_TIME_OUT; )
			}
