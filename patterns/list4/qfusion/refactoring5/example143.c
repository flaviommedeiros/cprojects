#ifdef HAVE_LIBSSH2_AGENT_API
if((data->set.ssh_auth_types & CURLSSH_AUTH_AGENT)
         && (strstr(sshc->authlist, "publickey") != NULL)) {

        /* Connect to the ssh-agent */
        /* The agent could be shared by a curl thread i believe
           but nothing obvious as keys can be added/removed at any time */
        if(!sshc->ssh_agent) {
          sshc->ssh_agent = libssh2_agent_init(sshc->ssh_session);
          if(!sshc->ssh_agent) {
            infof(data, "Could not create agent object\n");

            state(conn, SSH_AUTH_KEY_INIT);
          }
        }

        rc = libssh2_agent_connect(sshc->ssh_agent);
        if(rc == LIBSSH2_ERROR_EAGAIN)
          break;
        if(rc < 0) {
          infof(data, "Failure connecting to agent\n");
          state(conn, SSH_AUTH_KEY_INIT);
        }
        else {
          state(conn, SSH_AUTH_AGENT_LIST);
        }
      }
      else
#endif /* HAVE_LIBSSH2_AGENT_API */
        state(conn, SSH_AUTH_KEY_INIT);
