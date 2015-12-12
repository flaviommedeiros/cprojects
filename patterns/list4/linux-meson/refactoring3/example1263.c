switch (osd_data->type) {
	case CEPH_OSD_DATA_TYPE_NONE:
		return 0;
	case CEPH_OSD_DATA_TYPE_PAGES:
		return osd_data->length;
	case CEPH_OSD_DATA_TYPE_PAGELIST:
		return (u64)osd_data->pagelist->length;
#ifdef CONFIG_BLOCK
	case CEPH_OSD_DATA_TYPE_BIO:
		return (u64)osd_data->bio_length;
#endif /* CONFIG_BLOCK */
	default:
		WARN(true, "unrecognized data type %d\n", (int)osd_data->type);
		return 0;
	}
