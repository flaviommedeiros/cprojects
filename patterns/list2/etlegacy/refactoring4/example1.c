#if !defined(DEDICATED) && !defined(LEGACY_DEBUG)
if (Sys_Dialog(DT_YES_NO, "ET:L crashed last time it was running. Do you want to reset settings to default values?\n\nNote & Warning:\nIf you are running several client instances ensure a different value\nof CVAR fs_homepath is set for each client.\nOtherwise the same profile path is used which may cause other side effects.", "Reset settings") == DR_YES)
#else
				if (qfalse)
#endif
				{
					Com_Printf("WARNING: profile.pid found for profile '%s' - system settings will revert to defaults\n", cl_profileStr);
					// set crashed state
					Cbuf_AddText("set com_crashed 1\n");
				}
