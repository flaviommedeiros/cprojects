Command customCommands[] = 
{
	COMMAND_REQ("core_loadlib", request_core_loadlib),
	COMMAND_REQ("core_enumextcmd", request_core_enumextcmd),
	COMMAND_REQ("core_machine_id", request_core_machine_id),
	COMMAND_REQ("core_uuid", request_core_uuid),
#ifdef _WIN32
	COMMAND_INLINE_REP("core_patch_url", request_core_patch_url),
#endif
	COMMAND_TERMINATOR
};
