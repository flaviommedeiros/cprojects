#if ( LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0) )
if (ha->synced)
#else
		if (ha->sync_cnt)
#endif
			continue;
