switch (cursor->data->type) {
	case CEPH_MSG_DATA_PAGELIST:
		page = ceph_msg_data_pagelist_next(cursor, page_offset, length);
		break;
	case CEPH_MSG_DATA_PAGES:
		page = ceph_msg_data_pages_next(cursor, page_offset, length);
		break;
#ifdef CONFIG_BLOCK
	case CEPH_MSG_DATA_BIO:
		page = ceph_msg_data_bio_next(cursor, page_offset, length);
		break;
#endif /* CONFIG_BLOCK */
	case CEPH_MSG_DATA_NONE:
	default:
		page = NULL;
		break;
	}
