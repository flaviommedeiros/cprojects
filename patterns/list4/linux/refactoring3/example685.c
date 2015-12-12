switch (type) {
		case OVS_CT_ATTR_COMMIT:
			info->commit = true;
			break;
#ifdef CONFIG_NF_CONNTRACK_ZONES
		case OVS_CT_ATTR_ZONE:
			info->zone.id = nla_get_u16(a);
			break;
#endif
#ifdef CONFIG_NF_CONNTRACK_MARK
		case OVS_CT_ATTR_MARK: {
			struct md_mark *mark = nla_data(a);

			if (!mark->mask) {
				OVS_NLERR(log, "ct_mark mask cannot be 0");
				return -EINVAL;
			}
			info->mark = *mark;
			break;
		}
#endif
#ifdef CONFIG_NF_CONNTRACK_LABELS
		case OVS_CT_ATTR_LABELS: {
			struct md_labels *labels = nla_data(a);

			if (!labels_nonzero(&labels->mask)) {
				OVS_NLERR(log, "ct_labels mask cannot be 0");
				return -EINVAL;
			}
			info->labels = *labels;
			break;
		}
#endif
		case OVS_CT_ATTR_HELPER:
			*helper = nla_data(a);
			if (!memchr(*helper, '\0', nla_len(a))) {
				OVS_NLERR(log, "Invalid conntrack helper");
				return -EINVAL;
			}
			break;
		default:
			OVS_NLERR(log, "Unknown conntrack attr (%d)",
				  type);
			return -EINVAL;
		}
