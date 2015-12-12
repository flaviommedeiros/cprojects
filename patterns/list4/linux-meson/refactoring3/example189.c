switch (le16_to_cpu(info->type)) {
	case HFA384X_INFO_COMMTALLIES:
		prism2_info_commtallies(local, buf, left);
		break;

#ifndef PRISM2_NO_STATION_MODES
	case HFA384X_INFO_LINKSTATUS:
		prism2_info_linkstatus(local, buf, left);
		break;

	case HFA384X_INFO_SCANRESULTS:
		prism2_info_scanresults(local, buf, left);
		break;

	case HFA384X_INFO_HOSTSCANRESULTS:
		prism2_info_hostscanresults(local, buf, left);
		break;
#endif /* PRISM2_NO_STATION_MODES */

#ifndef PRISM2_NO_DEBUG
	default:
		PDEBUG(DEBUG_EXTRA, "%s: INFO - len=%d type=0x%04x\n",
		       local->dev->name, le16_to_cpu(info->len),
		       le16_to_cpu(info->type));
		PDEBUG(DEBUG_EXTRA, "Unknown info frame:");
		for (i = 0; i < (left < 100 ? left : 100); i++)
			PDEBUG2(DEBUG_EXTRA, " %02x", buf[i]);
		PDEBUG2(DEBUG_EXTRA, "\n");
		break;
#endif /* PRISM2_NO_DEBUG */
	}
