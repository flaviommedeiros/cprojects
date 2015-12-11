#if ( LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0) )
if (!ha->synced || ha->refcount != 1)
#else
		if (!ha->sync_cnt || ha->refcount != 1)
#endif
			continue;
