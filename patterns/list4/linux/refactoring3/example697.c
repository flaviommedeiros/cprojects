switch (cursor->data->type) {
	case CEPH_MSG_DATA_PAGELIST:
		ceph_msg_data_pagelist_cursor_init(cursor, length);
		break;
	case CEPH_MSG_DATA_PAGES:
		ceph_msg_data_pages_cursor_init(cursor, length);
		break;
#ifdef CONFIG_BLOCK
	case CEPH_MSG_DATA_BIO:
		ceph_msg_data_bio_cursor_init(cursor, length);
		break;
#endif /* CONFIG_BLOCK */
	case CEPH_MSG_DATA_NONE:
	default:
		/* BUG(); */
		break;
	}
