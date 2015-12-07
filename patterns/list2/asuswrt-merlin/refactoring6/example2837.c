if(
#if !defined(BCM_SHM_INTERFACE)				
				(((ULONG)sRdmBuffer.Register & 0x0F000000) != 0x0F000000) || 
#else
									(
				((ULONG)sRdmBuffer.Register  < 0xAF000000) 
			   							||
			    (((ULONG)sRdmBuffer.Register > 0xBFFFFFFF))
									)||
#endif				
					((ULONG)sRdmBuffer.Register & 0x3)
			  )
			{
				BCM_DEBUG_PRINT(Adapter,DBG_TYPE_PRINTK, 0, 0, "RDM Done On invalid Address : %x Access Denied.\n",
					(int)sRdmBuffer.Register);
				Status = -EINVAL;
				break;
			}
