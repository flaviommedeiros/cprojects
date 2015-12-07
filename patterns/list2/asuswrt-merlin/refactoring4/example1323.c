#ifdef DB_WINCE
if (LF_ISSET(DB_OSO_REGION))
				fhp->handle = CreateFileForMapping(tname,
				    access, share, NULL, createflag, attr, 0);
			else
#endif
				fhp->handle = CreateFile(tname,
				    access, share, NULL, createflag, attr, 0);
