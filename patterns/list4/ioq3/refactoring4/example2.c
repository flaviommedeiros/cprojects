#ifndef BSPC
if (cm_noAreas->integer || area == -1)
#else
	if ( area == -1)
#endif
	{	// for debugging, send everything
		Com_Memset (buffer, 255, bytes);
	}
	else
	{
		floodnum = cm.areas[area].floodnum;
		for (i=0 ; i<cm.numAreas ; i++)
		{
			if (cm.areas[i].floodnum == floodnum || area == -1)
				buffer[i>>3] |= 1<<(i&7);
		}
	}
