#if ( KETO_ENOL_TAUT == 1 )
if ( !((tgi->bTautFlags & TG_FLAG_KETO_ENOL_TAUT ) &&
                        nGetEndpointInfo_KET( at, endpoint, &eif )) )
#endif
                {
                    ret = BNS_BOND_ERR;
                    break;
                }
