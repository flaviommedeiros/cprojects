if (autoupdate.updateStarted
#ifndef DEDICATED
	    && NET_CompareAdr(autoupdate.autoupdateServer, clc.serverAddress)
#endif
	    )
	{
		if (strlen(com_updatefiles->string) > MIN_PACK_LEN)
		{
			char *updateFile;
			char updateFilesRemaining[MAX_TOKEN_CHARS] = "";

			upd.bWWWDl             = qtrue;
			upd.bWWWDlDisconnected = qtrue;

			updateFile = strtok(com_updatefiles->string, ";");

			if (updateFile == NULL)
			{
				Com_Error(ERR_AUTOUPDATE, "Could not parse update string.");
			}
			else
			{
				// download format: @remotename@localname
				Q_strncpyz(upd.downloadList, va("@%s@%s", updateFile, updateFile), MAX_INFO_STRING);
				Q_strncpyz(upd.originalDownloadName, va("%s/%s", AUTOUPDATE_DIR, updateFile), sizeof(upd.originalDownloadName));

				if (!Q_stricmp(updateFile, UPDATE_PACKAGE))
				{
					Q_strncpyz(upd.downloadName, va("%s/updater/%s-%s-%s", UPDATE_SERVER_NAME, ETLEGACY_VERSION_SHORT, CPUSTRING, updateFile), sizeof(upd.downloadName));
				}
				else
				{
					Q_strncpyz(upd.downloadName, va("%s/packages/%s", UPDATE_SERVER_NAME, updateFile), sizeof(upd.downloadName));
				}

				Q_strncpyz(upd.downloadTempName, FS_BuildOSPath(Cvar_VariableString("fs_homepath"), AUTOUPDATE_DIR, va("%s.tmp", updateFile)), sizeof(upd.downloadTempName));
				// TODO: add file size, so UI can show progress bar
				//Cvar_SetValue("cl_downloadSize", clc.downloadSize);

				if (!DL_BeginDownload(upd.downloadTempName, upd.downloadName))
				{
					Com_Error(ERR_AUTOUPDATE, "Could not download an update file: \"%s\"", upd.downloadName);
					upd.bWWWDlAborting = qtrue;
				}

				while (1)
				{
					updateFile = strtok(NULL, ";");

					if (updateFile == NULL)
					{
						break;
					}

					Q_strcat(updateFilesRemaining, sizeof(updateFilesRemaining), va("%s;", updateFile));
				}

				if (strlen(updateFilesRemaining) > MIN_PACK_LEN)
				{
					Cvar_Set("com_updatefiles", updateFilesRemaining);
				}
				else
				{
					Cvar_Set("com_updatefiles", "");
				}
			}
		}
		return qtrue;
	}
