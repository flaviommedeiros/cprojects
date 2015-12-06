switch (req)
	{
	  case 'B':
		  if (!has_priv_user(u, PRIV_SERVER_AUSPEX))
			  break;

		  mowgli_patricia_stats(userlist, dictionary_stats_cb, u);
		  mowgli_patricia_stats(chanlist, dictionary_stats_cb, u);
		  mowgli_patricia_stats(servlist, dictionary_stats_cb, u);
		  myentity_stats(dictionary_stats_cb, u);
		  mowgli_patricia_stats(nicklist, dictionary_stats_cb, u);
		  mowgli_patricia_stats(mclist, dictionary_stats_cb, u);
		  break;

	  case 'C':
	  case 'c':
		  if (!has_priv_user(u, PRIV_SERVER_AUSPEX))
			  break;

		  MOWGLI_ITER_FOREACH(n, uplinks.head)
		  {
			  uplink = (uplink_t *)n->data;
			  numeric_sts(me.me, 213, u, "C *@127.0.0.1 A %s %d uplink", uplink->name, uplink->port);
		  }
		  break;

	  case 'E':
	  case 'e':
		  if (!has_priv_user(u, PRIV_SERVER_AUSPEX))
			  break;

		  numeric_sts(me.me, 249, u, "E :Last event to run: %s", base_eventloop->last_ran);

		  numeric_sts(me.me, 249, u, "E :%-28s %s", "Operation", "Next Execution");
		  MOWGLI_ITER_FOREACH(n, base_eventloop->timer_list.head)
		  {
			  mowgli_eventloop_timer_t *timer = n->data;

			  if (timer->active)
				  numeric_sts(me.me, 249, u, "E :%-28s %4ld seconds (%ld)", timer->name, (long)(timer->deadline - mowgli_eventloop_get_time(base_eventloop)), (long)timer->frequency);
		  }

		  break;

	  case 'f':
	  case 'F':
		  if (!has_priv_user(u, PRIV_SERVER_AUSPEX))
			  break;

		  connection_stats(connection_stats_cb, u);
		  break;

	  case 'H':
	  case 'h':
		  if (!has_priv_user(u, PRIV_SERVER_AUSPEX))
			  break;

		  MOWGLI_ITER_FOREACH(n, uplinks.head)
		  {
			  uplink = (uplink_t *)n->data;
			  numeric_sts(me.me, 244, u, "H * * %s", uplink->name);
		  }
		  break;

	  case 'I':
	  case 'i':
		  numeric_sts(me.me, 215, u, "I * * *@%s 0 nonopered", me.name);
		  break;

#ifdef OBJECT_DEBUG
	  case 'j':
	  case 'J':
		  MOWGLI_ITER_FOREACH(n, object_list.head)
		  {
			  object_t *obj = n->data;
			  numeric_sts(me.me, 249, u, "J :object:%p refs:%d destructor:%p",
				      obj, obj->refcount, obj->destructor);
		  }
		  break;
#endif

	  case 'K':
	  case 'k':
		  if (!has_priv_user(u, PRIV_AKILL))
			  break;

		  MOWGLI_ITER_FOREACH(n, klnlist.head)
		  {
			  k = (kline_t *)n->data;

			  numeric_sts(me.me, 216, u, "%c %s * %s :%s",
					  k->duration ? 'k' : 'K',
					  k->host, k->user, k->reason);
		  }

		  break;

	  case 'o':
	  case 'O':
		  if (!has_priv_user(u, PRIV_VIEWPRIVS))
			  break;

		  MOWGLI_ITER_FOREACH(n, soperlist.head)
		  {
			  soper = n->data;

			  j = 0;
			  if (!(soper->flags & SOPER_CONF))
				  fl[j++] = 'D';
			  if (soper->operclass != NULL && soper->operclass->flags & OPERCLASS_NEEDOPER)
				  fl[j++] = 'O';
			  if (j == 0)
				  fl[j++] = '*';
			  fl[j] = '\0';
			  numeric_sts(me.me, 243, u, "O *@* %s %s %s %s",
					  fl, soper->myuser ? entity(soper->myuser)->name : soper->name,
					  soper->operclass ? soper->operclass->name : soper->classname, "-1");
		  }
		  break;

	  case 'T':
	  case 't':
		  if (!has_priv_user(u, PRIV_SERVER_AUSPEX))
			  break;

		  numeric_sts(me.me, 249, u, "T :event      %7d", claro_state.event);
		  numeric_sts(me.me, 249, u, "T :node       %7d", claro_state.node);
		  numeric_sts(me.me, 249, u, "T :connection %7d", connection_count());
		  numeric_sts(me.me, 249, u, "T :operclass  %7d", cnt.operclass);
		  numeric_sts(me.me, 249, u, "T :soper      %7d", cnt.soper);
		  numeric_sts(me.me, 249, u, "T :tld        %7d", cnt.tld);
		  numeric_sts(me.me, 249, u, "T :kline      %7d", cnt.kline);
		  numeric_sts(me.me, 249, u, "T :xline      %7d", cnt.xline);
		  numeric_sts(me.me, 249, u, "T :server     %7d", cnt.server);
		  numeric_sts(me.me, 249, u, "T :user       %7d", cnt.user);
		  numeric_sts(me.me, 249, u, "T :chan       %7d", cnt.chan);
		  numeric_sts(me.me, 249, u, "T :chanuser   %7d", cnt.chanuser);
		  numeric_sts(me.me, 249, u, "T :myuser     %7d", cnt.myuser);
		  numeric_sts(me.me, 249, u, "T :myuser_acc %7d", cnt.myuser_access);
		  numeric_sts(me.me, 249, u, "T :mynick     %7d", cnt.mynick);
		  numeric_sts(me.me, 249, u, "T :myuser_nam %7d", cnt.myuser_name);
		  numeric_sts(me.me, 249, u, "T :mychan     %7d", cnt.mychan);
		  numeric_sts(me.me, 249, u, "T :chanacs    %7d", cnt.chanacs);

#ifdef OBJECT_DEBUG
		  numeric_sts(me.me, 249, u, "T :objects    %7zu", MOWGLI_LIST_LENGTH(&object_list));
#endif

		  numeric_sts(me.me, 249, u, "T :bytes sent %7.2f%s", bytes(cnt.bout), sbytes(cnt.bout));
		  numeric_sts(me.me, 249, u, "T :bytes recv %7.2f%s", bytes(cnt.bin), sbytes(cnt.bin));
		  break;

	  case 'u':
		  numeric_sts(me.me, 242, u, ":Services Uptime: %s", timediff(CURRTIME - me.start));
		  break;

	  case 'V':
	  case 'v':
		  if (!has_priv_user(u, PRIV_SERVER_AUSPEX))
			  break;

		  /* we received this command from the uplink, so,
		   * hmm, it is not idle */
		  numeric_sts(me.me, 249, u, "V :%s (AutoConn.!*@*) Idle: 0 SendQ: ? Connected: %s",
				  curr_uplink->name,
				  timediff(CURRTIME - curr_uplink->conn->first_recv));
		  break;

	  case 'q':
	  case 'Q':
		  if (!has_priv_user(u, PRIV_MASS_AKILL))
			  break;

		  MOWGLI_ITER_FOREACH(n, qlnlist.head)
		  {
			  q = (qline_t *)n->data;

			  numeric_sts(me.me, 217, u, "%c %d %s :%s",
					  q->duration ? 'q' : 'Q',
					  0, /* hit count */
					  q->mask, q->reason);
		  }

		  break;

	  case 'x':
	  case 'X':
		  if (!has_priv_user(u, PRIV_MASS_AKILL))
			  break;

		  MOWGLI_ITER_FOREACH(n, xlnlist.head)
		  {
			  x = (xline_t *)n->data;

			  numeric_sts(me.me, 247, u, "%c %d %s :%s",
					  x->duration ? 'x' : 'X',
					  0, /* hit count */
					  x->realname, x->reason);
		  }

		  break;

	  case 'y':
	  case 'Y':
		  if (!has_priv_user(u, PRIV_SERVER_AUSPEX))
			  break;

		  numeric_sts(me.me, 218, u, "Y uplink 300 %u 1 %u 0.0 0.0 1",
				  me.recontime, config_options.uplink_sendq_limit);
		  break;

	  default:
		  break;
	}
