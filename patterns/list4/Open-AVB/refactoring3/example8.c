switch (cmd->cmd) {
	case ETHTOOL_GRXRINGS:
		cmd->data = adapter->num_rx_queues;
		ret = 0;
		break;
#ifdef ETHTOOL_GRXFHINDIR
	case ETHTOOL_GRXFHINDIR:
		ret = igb_get_rss_hash_opts(adapter, cmd);
		break;
#endif /* ETHTOOL_GRXFHINDIR */
	default:
		break;
	}
