#if ENABLE_MULTI_PACKET_QUERY_SNOOPING
if (!(query->h.flags.b[0] & kDNSFlag0_TC))
#endif
				for (cr = cg ? cg->members : mDNSNULL; cr; cr=cr->next)
					if (SameNameRecordAnswersQuestion(&cr->resrec, &pktq) && cr->resrec.rdlength <= SmallRecordLimit)
						if (!cr->NextInKAList && eap != &cr->NextInKAList)
							{
							*eap = cr;
							eap = &cr->NextInKAList;
#if ENABLE_MULTI_PACKET_QUERY_SNOOPING
							if (cr->MPUnansweredQ == 0 || m->timenow - cr->MPLastUnansweredQT >= mDNSPlatformOneSecond)
								{
								// Although MPUnansweredQ is only really used for multi-packet query processing,
								// we increment it for both single-packet and multi-packet queries, so that it stays in sync
								// with the MPUnansweredKA value, which by necessity is incremented for both query types.
								cr->MPUnansweredQ++;
								cr->MPLastUnansweredQT = m->timenow;
								cr->MPExpectingKA = mDNStrue;
								}
#endif
							}
