if (autoupdate.updateChecked
#ifndef DEDICATED
	    && NET_CompareAdr(autoupdate.autoupdateServer, clc.serverAddress)
#endif
	    )
	{
		// Mark the client as being in the process of getting an update
		if (com_updateavailable->integer)
		{
			autoupdate.updateStarted = qtrue;
			Com_InitDownloads();
		}
	}
