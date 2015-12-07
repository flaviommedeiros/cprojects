#ifdef SFTPSERVER_PATH
if ((cmdlen == 4) && strncmp(chansess->cmd, "sftp", 4) == 0) {
				m_free(chansess->cmd);
				chansess->cmd = m_strdup(SFTPSERVER_PATH);
			} else 
#endif
			{
				m_free(chansess->cmd);
				return DROPBEAR_FAILURE;
			}
