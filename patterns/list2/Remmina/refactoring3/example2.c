switch (feature->id)
	{
#ifdef HAVE_LIBSSH
	case REMMINA_PROTOCOL_FEATURE_TOOL_SSH:
		if (gp->priv->ssh_tunnel)
		{
			remmina_connection_window_open_from_file_full (
			    remmina_file_dup_temp_protocol (gp->priv->remmina_file, "SSH"), NULL, gp->priv->ssh_tunnel, NULL);
			return;
		}
		break;

	case REMMINA_PROTOCOL_FEATURE_TOOL_SFTP:
		if (gp->priv->ssh_tunnel)
		{
			remmina_connection_window_open_from_file_full (
			    remmina_file_dup_temp_protocol (gp->priv->remmina_file, "SFTP"), NULL, gp->priv->ssh_tunnel, NULL);
			return;
		}
		break;
#endif
	default:
		break;
	}
