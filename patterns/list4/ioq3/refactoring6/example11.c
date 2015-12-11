if(FS_idPak(fs_serverReferencedPakNames[i], BASEGAME, NUM_ID_PAKS)
#ifndef STANDALONE
				|| FS_idPak(fs_serverReferencedPakNames[i], BASETA, NUM_TA_PAKS)
#endif
			)
		{
			continue;
		}
