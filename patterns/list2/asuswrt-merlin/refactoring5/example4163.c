#ifdef CONFIG_CTRL_IFACE_UDP
if (ctrl->cookie) {
		char *pos;
		_cmd_len = os_strlen(ctrl->cookie) + 1 + cmd_len;
		cmd_buf = os_malloc(_cmd_len);
		if (cmd_buf == NULL)
			return -1;
		_cmd = cmd_buf;
		pos = cmd_buf;
		os_strlcpy(pos, ctrl->cookie, _cmd_len);
		pos += os_strlen(ctrl->cookie);
		*pos++ = ' ';
		os_memcpy(pos, cmd, cmd_len);
	} else
#endif /* CONFIG_CTRL_IFACE_UDP */
	{
		_cmd = cmd;
		_cmd_len = cmd_len;
	}
