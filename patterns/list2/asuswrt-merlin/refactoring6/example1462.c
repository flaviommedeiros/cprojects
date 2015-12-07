if(
#if !defined(BCM_SHM_INTERFACE)	

				(((ULONG)sWrmBuffer.Register & 0x0F000000) != 0x0F000000) || 
#else
									(
				((ULONG)sWrmBuffer.Register  < 0xAF000000) 
			   							||
			    (((ULONG)sWrmBuffer.Register > 0xBFFFFFFF))
									)||
#endif				
					((ULONG)sWrmBuffer.Register & 0x3)
			 )
			{
				BCM_DEBUG_PRINT(Adapter,DBG_TYPE_PRINTK, 0, 0, "WRM Done On invalid Address : %x Access Denied.\n",
						(int)sWrmBuffer.Register);
				Status = -EINVAL;
				break;
			}
