#if ENABLE_MULTI_PACKET_QUERY_SNOOPING
if (QuestionNeedsMulticastResponse)
#else
		// We only do the following accelerated cache expiration and duplicate question suppression processing
		// for non-truncated multicast queries with multicast responses.
		// For any query generating a unicast response we don't do this because we can't assume we will see the response.
		// For truncated queries we don't do this because a response we're expecting might be suppressed by a subsequent
		// known-answer packet, and when there's packet loss we can't safely assume we'll receive *all* known-answer packets.
		if (QuestionNeedsMulticastResponse && !(query->h.flags.b[0] & kDNSFlag0_TC))
#endif
			{
			const mDNSu32 slot = HashSlot(&pktq.qname);
			CacheGroup *cg = CacheGroupForName(m, slot, pktq.qnamehash, &pktq.qname);
			CacheRecord *cr;

			// Make a list indicating which of our own cache records we expect to see updated as a result of this query
			// Note: Records larger than 1K are not habitually multicast, so don't expect those to be updated
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
	
			// Check if this question is the same as any of mine.
			// We only do this for non-truncated queries. Right now it would be too complicated to try
			// to keep track of duplicate suppression state between multiple packets, especially when we
			// can't guarantee to receive all of the Known Answer packets that go with a particular query.
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
			}
