#ifdef BCM_SHM_INTERFACE
if(rdmalt(Adapter, TARGET_SFID_TXDESC_MAP_LOC, (PUINT)uibuff, sizeof(UINT) * MAX_TARGET_DSX_BUFFERS)<0)
#else	
	if(rdmaltWithLock(Adapter, TARGET_SFID_TXDESC_MAP_LOC, (PUINT)uibuff, sizeof(UINT) * MAX_TARGET_DSX_BUFFERS)<0)
#endif
	{
		BCM_DEBUG_PRINT(Adapter,DBG_TYPE_PRINTK, 0, 0, "rdm failed\n");
		return;
	}
