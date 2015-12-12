Command baseCommands[] =
{
	// Console commands
	{ "core_console_write",
		{ remote_request_core_console_write, NULL, { TLV_META_TYPE_STRING }, 1 | ARGUMENT_FLAG_REPEAT },
		{ remote_response_core_console_write, NULL, EMPTY_TLV },
	},

	// Native Channel commands
	// this overloads the "core_channel_open" in the base command list
	COMMAND_REQ_REP("core_channel_open", remote_request_core_channel_open, remote_response_core_channel_open),
	COMMAND_REQ("core_channel_write", remote_request_core_channel_write),
	COMMAND_REQ_REP("core_channel_close", remote_request_core_channel_close, remote_response_core_channel_close),

	// Buffered/Pool channel commands
	COMMAND_REQ("core_channel_read", remote_request_core_channel_read),
	// Pool channel commands
	COMMAND_REQ("core_channel_seek", remote_request_core_channel_seek),
	COMMAND_REQ("core_channel_eof", remote_request_core_channel_eof),
	COMMAND_REQ("core_channel_tell", remote_request_core_channel_tell),
	// Soon to be deprecated
	COMMAND_REQ("core_channel_interact", remote_request_core_channel_interact),
	// Crypto
	COMMAND_REQ("core_crypto_negotiate", remote_request_core_crypto_negotiate),
	// timeouts
	COMMAND_REQ("core_transport_set_timeouts", remote_request_core_transport_set_timeouts),
#ifdef _WIN32
	COMMAND_REQ("core_transport_getcerthash", remote_request_core_transport_getcerthash),
	COMMAND_REQ("core_transport_setcerthash", remote_request_core_transport_setcerthash),
#endif
	COMMAND_REQ("core_transport_list", remote_request_core_transport_list),
	COMMAND_INLINE_REQ("core_transport_sleep", remote_request_core_transport_sleep),
	COMMAND_INLINE_REQ("core_transport_change", remote_request_core_transport_change),
	COMMAND_INLINE_REQ("core_transport_next", remote_request_core_transport_next),
	COMMAND_INLINE_REQ("core_transport_prev", remote_request_core_transport_prev),
	COMMAND_REQ("core_transport_add", remote_request_core_transport_add),
	COMMAND_REQ("core_transport_remove", remote_request_core_transport_remove),
	// Migration
	COMMAND_INLINE_REQ("core_migrate", remote_request_core_migrate),
	// Shutdown
	COMMAND_INLINE_REQ("core_shutdown", remote_request_core_shutdown),
	// Terminator
	COMMAND_TERMINATOR
};
