if ((this->type == RAD_LISTEN_AUTH)
#ifdef WITH_ACCT
	    || (this->type == RAD_LISTEN_ACCT)
#endif
#ifdef WITH_PROXY
	    || (this->type == RAD_LISTEN_PROXY)
#endif
#ifdef WITH_COMMAND_SOCKET
	    || ((this->type == RAD_LISTEN_COMMAND) &&
		(((fr_command_socket_t *) this->data)->magic != COMMAND_SOCKET_MAGIC))
#endif
		) {
		listen_socket_t *sock = this->data;

		rad_assert(talloc_parent(sock) == this);
		rad_assert(sock->ev == NULL);

		/*
		 *	Remove the child from the parent tree.
		 */
		if (this->parent) {
			rbtree_deletebydata(this->parent->children, this);
		}

		/*
		 *	Delete / close all of the children, too!
		 */
		if (this->children) {
			rbtree_walk(this->children, RBTREE_DELETE_ORDER, listener_unlink, this);
		}

#ifdef WITH_TLS
		/*
		 *	Note that we do NOT free this->tls, as the
		 *	pointer is parented by its CONF_SECTION.  It
		 *	may be used by multiple listeners.
		 */
		if (this->tls) {
			rad_assert(!sock->tls_session || (talloc_parent(sock->tls_session) == sock));
			rad_assert(!sock->request || (talloc_parent(sock->request) == sock));
#ifdef HAVE_PTHREAD_H
			pthread_mutex_destroy(&(sock->mutex));
#endif
		}
#endif	/* WITH_TLS */
	}
