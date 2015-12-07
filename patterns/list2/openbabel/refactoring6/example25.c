if ( at[i1].nNumAtInRingSystem >=
#if ( TAUT_TROPOLONE_5 == 1 )
                  5
#else
                  7 
#endif
                 &&
                 bIsCenterPointStrict( at, i1 ) &&
#if ( TAUT_RINGS_ATTACH_CHAIN == 1 )        
                 at[i1].bCutVertex &&
#endif
                 at[i1].valence == 3 && !at[i1].endpoint ) {
                int nMobile1, endpoint1, endpoint1_valence, bond_type1;
                int nMobile2, endpoint2, endpoint2_valence, bond_type2;
                for ( j = 0; j < at[i1].valence; j ++ ) {
                    i2 = at[i1].neighbor[j];
                    /*
                         // may be important
                    if ( i2 > i1 )
                        continue; // do not try same pair 2 times
                    */
                    if ( at[i2].nRingSystem != at[i1].nRingSystem ||
                         !bIsCenterPointStrict( at, i2 ) ||
#if ( TAUT_RINGS_ATTACH_CHAIN == 1 )        
                         !at[i2].bCutVertex ||
#endif                         
                         at[i2].valence != 3 || at[i2].endpoint )
                        continue;
                    bond_type = (at[i1].bond_type[j] & ~BOND_MARK_ALL);
                    if ( bond_type != BOND_SINGLE &&
                         bond_type != BOND_TAUTOM &&
                         bond_type != BOND_ALT12NS &&
                         bond_type != BOND_ALTERN ) {
                        continue; /*  not a single bond between Q-R */
                    }
                    /*  find endpoints */
                    for ( k = 0; k < at[i1].valence; k ++ ) {
                        endpoint1 = at[i1].neighbor[k];
                        if ( endpoint1 == i2 )
                            continue; /*  j == k */
                        if ( !(endpoint1_valence = nGetEndpointInfo( at, endpoint1, &eif1 ) ) )
                            continue; /*  not an endpoint1 element or can't have mobile groups */
#if ( TAUT_RINGS_ATTACH_CHAIN == 1 )        
                        if ( at[endpoint1].nRingSystem == at[i1].nRingSystem )
                            continue;
#endif
                        nMobile1  = at[endpoint1].num_H + (at[endpoint1].charge == -1);  /*  number of mobile groups */
                        if ( nMobile1 + at[endpoint1].chem_bonds_valence != endpoint1_valence )
                            continue; /*  abnormal endpoint1 valence; ignore. */
                        bond_type1 = (at[i1].bond_type[k] & ~BOND_MARK_ALL);
                        
                        if ( bond_type1 != BOND_SINGLE &&
                             bond_type1 != BOND_DOUBLE &&
                             bond_type1 != BOND_TAUTOM &&
                             bond_type1 != BOND_ALT12NS &&
                             bond_type1 != BOND_ALTERN )
                            continue;
                        
                        for ( m = 0; m < at[i2].valence; m ++ ) {
                            endpoint2 = at[i2].neighbor[m];
                            if ( endpoint2 == i1 )
                                continue;
                            if ( !(endpoint2_valence = nGetEndpointInfo( at, endpoint2, &eif2 )) )
                                continue; /*  not an endpoint2 element or can't have mobile groups */
#if ( TAUT_RINGS_ATTACH_CHAIN == 1 )        
                            if ( at[endpoint2].nRingSystem == at[i2].nRingSystem )
                                continue;
#endif
                            nMobile2  = at[endpoint2].num_H + (at[endpoint2].charge == -1);  /*  number of mobile groups */
                            bond_type2 = (at[i2].bond_type[m] & ~BOND_MARK_ALL);
                            
                            if ( bond_type2 != BOND_SINGLE &&
                                 bond_type2 != BOND_DOUBLE &&
                                 bond_type2 != BOND_TAUTOM &&
                                 bond_type2 != BOND_ALT12NS &&
                                 bond_type2 != BOND_ALTERN )
                                continue;
                            
                            /*  final test for possible tautomerism */
                            nMobile = 0;
                            
                            if ( ALLOWED_EDGE(pBNS, i1, k) && ALLOWED_EDGE(pBNS, i2, m) ) {
                            
                                /*  can mobile group move from 1 to 2? */
                                nMobile += (at[endpoint1].endpoint || nMobile1) &&  /*  from endpoint1 */
                                           (bond_type1 != BOND_DOUBLE)   &&
                                       
                                            (at[endpoint2].endpoint ||          /*  to endpoint2 */
                                            eif2.cNeutralBondsValence > at[endpoint2].valence ) &&
                                           (bond_type2 != BOND_SINGLE); 


                                /*  can mobile group move from 2 to 1? */
                                nMobile += (at[endpoint2].endpoint || nMobile2) &&  /*  from endpoint2 */
                                           (bond_type2 != BOND_DOUBLE)   && /*changed from BOND_SINGLE 2004-02-26 */
                                       
                                            (at[endpoint1].endpoint ||          /*  to endpoint1 */
                                            eif1.cNeutralBondsValence > at[endpoint1].valence ) &&
                                           (bond_type1 != BOND_SINGLE);
                            }
                            if ( !nMobile )
                                continue;
                            
                            if ( bond_type1 == bond_type2 &&
                                 (bond_type1 == BOND_SINGLE || bond_type1 == BOND_DOUBLE) )
                                continue;
                            /* -- old --
                            if ( !at[endpoint1].endpoint && !at[endpoint2].endpoint && 1 != nMobile1 + nMobile2 )
                                continue;
                            */
                            /* -- new --

                            if ( !at[endpoint1].endpoint && !at[endpoint2].endpoint ) {
                                if ( !(bond_type1 == BOND_SINGLE || bond_type1 == BOND_DOUBLE) ||
                                     !(bond_type2 == BOND_SINGLE || bond_type2 == BOND_DOUBLE) ) {
                                    // at this point bond_type1 != bond_type2
                                    continue;
                                }
                                if ( bond_type1 == BOND_SINGLE && !nMobile1 ||
                                     bond_type2 == BOND_SINGLE && !nMobile2 ||
                                     0 == nMobile1 + nMobile2 ) {
                                    continue;
                                }
                            }
                            */
#if ( TAUT_TROPOLONE_7 == 1 )
                            if ( at[i1].nNumAtInRingSystem >= 7 ) {
                                ret = nGet14TautIn7MembAltRing( at, i1, j, k, m, nDfsPathPos,
                                                              DfsPath,  nMaxLenDfsPath,
                                                              EndPoint, sizeof(EndPoint)/sizeof(EndPoint[0]),
                                                              BondPos, sizeof(BondPos)/sizeof(BondPos[0]),
                                                              &nNumEndPoints, &nNumBondPos, 
                                                              pBNS, pBD, num_atoms);
                                if ( ret > 0 ) {
                                    if ( nNumEndPoints ) {
                                        num_changes = RegisterEndPoints( t_group_info, EndPoint, nNumEndPoints, at, num_atoms, c_group_info, pBNS);
                                        if ( num_changes == -1 ) {
                                            nErr = CT_TAUCOUNT_ERR;
                                        }
                                        if ( num_changes < 0 ) {
                                            nErr = num_changes;
                                        }
                                        if ( nErr )
                                            goto free_memory;
                                        tot_changes += (num_changes > 0);
                                    }
                                    if ( nNumBondPos ) {
                                        tot_changes += ( 0 < SetTautomericBonds( at, nNumBondPos, BondPos ) );
                                    }
                                } else
                                if ( IS_BNS_ERROR( ret ) ) {
                                    nErr = ret;
                                    goto free_memory;
                                }
                            }
#endif

#if ( TAUT_TROPOLONE_5 == 1 )
                            if ( at[i1].nNumAtInRingSystem >= 5 ) {
                                ret = nGet14TautIn5MembAltRing( at, i1, j, k, m, nDfsPathPos,
                                                              DfsPath,  nMaxLenDfsPath,
                                                              EndPoint, sizeof(EndPoint)/sizeof(EndPoint[0]),
                                                              BondPos, sizeof(BondPos)/sizeof(BondPos[0]),
                                                              &nNumEndPoints, &nNumBondPos, 
                                                              pBNS, pBD, num_atoms);
                                if ( ret > 0 ) {
                                    if ( nNumEndPoints ) {
                                        num_changes = RegisterEndPoints( t_group_info, EndPoint, nNumEndPoints, at, num_atoms, c_group_info, pBNS);
                                        if ( num_changes == -1 ) {
                                            nErr = CT_TAUCOUNT_ERR;
                                        }
                                        if ( num_changes < 0 ) {
                                            nErr = num_changes;
                                        }
                                        if ( nErr )
                                            goto free_memory;
                                        tot_changes += (num_changes > 0);
                                    }
                                    if ( nNumBondPos ) {
                                        tot_changes += ( 0 < SetTautomericBonds( at, nNumBondPos, BondPos ) );
                                    }
                                } else
                                if ( IS_BNS_ERROR( ret ) ) {
                                    nErr = ret;
                                    goto free_memory;
                                }
                            }
#endif
                        }
                    }
                }
            }
