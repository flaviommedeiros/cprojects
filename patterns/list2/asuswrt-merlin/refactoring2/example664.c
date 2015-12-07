#if ENABLE_MULTI_PACKET_QUERY_SNOOPING
if (!(query->h.flags.b[0] & kDNSFlag0_TC))
#endif
				for (q = m->Questions; q; q=q->next)
					if (!q->Target.type && ActiveQuestion(q) && m->timenow - q->LastQTxTime > mDNSPlatformOneSecond / 4)
						if (!q->InterfaceID || q->InterfaceID == InterfaceID)
							if (q->NextInDQList == mDNSNULL && dqp != &q->NextInDQList)
								if (q->qtype == pktq.qtype &&
									q->qclass == pktq.qclass &&
									q->qnamehash == pktq.qnamehash && SameDomainName(&q->qname, &pktq.qname))
									{ *dqp = q; dqp = &q->NextInDQList; }
