#ifndef DEBUG_CMD_WEP_KEY
if (cmd->cmd == IPW_CMD_WEP_KEY)
		IPW_DEBUG_HC("WEP_KEY command masked out for secure.\n");
	else
#endif
		printk_buf(IPW_DL_HOST_COMMAND, (u8 *) cmd->param, cmd->len);
