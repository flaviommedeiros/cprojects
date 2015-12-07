if ( 0 <= (s_type = GetSaltChargeType( at, i1, t_group_info, &s_subtype ))
#if ( INCL_NON_SALT_CANDIDATATES == 1 )            
                     || 0 < (s_type = GetOtherSaltChargeType( at, i1, t_group_info, &s_subtype, 1 /* bAccept_O*/ ))
#endif
                    ) {
                    s_candidate[nNumCandidates].type     = s_type;
                    s_candidate[nNumCandidates].subtype  = s_subtype;
                    s_candidate[nNumCandidates].endpoint = at[i1].endpoint;
                }
