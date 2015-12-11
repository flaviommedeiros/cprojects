#ifdef LEGACY_PROTOCOL
if(com_legacyprotocol->integer > 0)
				{
					// Server is ioq3 but has a different protocol than we do.
					// Fall back to idq3 protocol.
					clc.compat = qtrue;

					Com_Printf(S_COLOR_YELLOW "Warning: Server reports protocol version %d, "
						   "we have %d. Trying legacy protocol %d.\n",
						   ver, com_protocol->integer, com_legacyprotocol->integer);
				}
				else
#endif
				{
					Com_Printf(S_COLOR_YELLOW "Warning: Server reports protocol version %d, we have %d. "
						   "Trying anyways.\n", ver, com_protocol->integer);
				}
