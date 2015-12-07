if ( 0 == (s_type = GetSaltChargeType( at, i, t_group_info, &s_subtype )) ||
                     /* -C=O or =C-OH, O = S, Se, Te */
#if ( INCL_NON_SALT_CANDIDATATES == 1 )            
                     1 == (s_type = GetOtherSaltChargeType( at, i, t_group_info, &s_subtype, 1 )) ||
                     /* =Z-MH or -Z=M, Z = centerpoint, M = endpoint, other than above */
#endif
                     2 == (s_type = GetOtherSaltType( at, i, &s_subtype ) ) 
                     /* >C-SH, >C-S(-); S=S,Se,Te */
                   ) 
                {

                    if ( nNumCandidates >= nMaxNumCandidates ) 
                    {
                        err = BNS_VERT_EDGE_OVFL;
                        goto quick_exit;
                    }
                    s_candidate[nNumCandidates].atnumber = i;
                    s_candidate[nNumCandidates].type     = s_type;
                    s_candidate[nNumCandidates].subtype  = s_subtype;
                    s_candidate[nNumCandidates].endpoint = at[i].endpoint;
                    nNumCandidates ++;
                    nNumOtherCandidates += (1 == s_type);
                    nNumPOnlyCandidates += (2 == s_type);
                    s_subtype_all                        |= s_subtype;
                    /*i1 = i;*/ /* save a representative of a tautomeric group */
                }
