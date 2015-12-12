#ifdef USE_FBR0
if (ringIndex > 1 ||
		(ringIndex == 0 &&
		bufferIndex > pRxLocal->Fbr0NumEntries - 1) ||
		(ringIndex == 1 &&
		bufferIndex > pRxLocal->Fbr1NumEntries - 1))
#else
	if (ringIndex != 1 ||
		bufferIndex > pRxLocal->Fbr1NumEntries - 1)
#endif
	{
		/* Illegal buffer or ring index cannot be used by S/W*/
		dev_err(&etdev->pdev->dev,
			  "NICRxPkts PSR Entry %d indicates "
			  "length of %d and/or bad bi(%d)\n",
			  pRxLocal->local_psr_full.bits.psr_full,
			  localLen, bufferIndex);
		return NULL;
	}
