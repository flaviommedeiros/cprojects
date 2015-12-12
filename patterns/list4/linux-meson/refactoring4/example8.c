#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,33)
if( wait_event_interruptible(cdev->fifo_inq, kfifo_len( cdev->pDataKFiFo )>0) )
	#else
		if( wait_event_interruptible(cdev->fifo_inq, kfifo_len( &cdev->DataKFiFo )>0) )
	#endif
		{
			return -ERESTARTSYS; /* signal: tell the fs layer to handle it */
		}
