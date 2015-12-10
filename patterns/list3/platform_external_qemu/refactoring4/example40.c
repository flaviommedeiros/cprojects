#ifdef STORMC4_WOS
if(!KeymapBase)
		#else
		if(!ConsoleDevice)
		#endif
		{
			#ifdef STORMC4_WOS
			KeymapBase=OpenLibrary("keymap.library", 0L);
			#else
			if(ConPort=CreateMsgPort())
			{
				if(ConReq=CreateIORequest(ConPort,sizeof(struct IOStdReq)))
				{
					if(!OpenDevice("console.device",-1,(struct IORequest *)ConReq,0))
						ConsoleDevice=(struct Library *)ConReq->io_Device;
					else
					{
						DeleteIORequest(ConReq);
						ConReq=NULL;
					}
				}
				else
				{
					DeleteMsgPort(ConPort);
					ConPort=NULL;
				}
			}
			#endif
		}
