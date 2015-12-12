switch (cursor->data->type) {
	case CEPH_MSG_DATA_PAGELIST:
		new_piece = ceph_msg_data_pagelist_advance(cursor, bytes);
		break;
	case CEPH_MSG_DATA_PAGES:
		new_piece = ceph_msg_data_pages_advance(cursor, bytes);
		break;
#ifdef CONFIG_BLOCK
	case CEPH_MSG_DATA_BIO:
		new_piece = ceph_msg_data_bio_advance(cursor, bytes);
		break;
#endif /* CONFIG_BLOCK */
	case CEPH_MSG_DATA_NONE:
	default:
		BUG();
		break;
	}
