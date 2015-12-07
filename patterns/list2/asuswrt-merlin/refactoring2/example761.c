#if (HCF_TYPE) & HCF_TYPE_CCX
if( ifbp->IFB_CKIPStat != HCF_ACT_CCX_ON  )
#endif // HCF_TYPE_CCX
				{
#if HCF_ENCAP == HCF_ENC
					HCFASSERT( len >= HFS_DAT + 2 + sizeof(snap_header), len )
/*34*/ 				i = *(wci_recordp)&bufp[HFS_STAT] & ( HFS_STAT_MSG_TYPE | HFS_STAT_ERR );
					if ( i == HFS_STAT_TUNNEL ||
						 ( i == HFS_STAT_1042 && hcf_encap( (wci_bufp)&bufp[HFS_TYPE] ) != ENC_TUNNEL ) ) {
												//.  copy E-II Type to 802.3 LEN field
/*36*/					bufp[HFS_LEN  ] = bufp[HFS_TYPE  ];
						bufp[HFS_LEN+1] = bufp[HFS_TYPE+1];
												//.  discard Snap by overwriting with data
						ifbp->IFB_RxLen -= (HFS_TYPE - HFS_LEN);
						buf_addr -= ( HFS_TYPE - HFS_LEN ); // this happens to bring us at a DW boundary of 36
					}
#endif // HCF_ENC
				}
