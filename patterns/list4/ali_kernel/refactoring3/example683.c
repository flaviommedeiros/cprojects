switch (je16_to_cpu(item->u.nodetype)) {
		case JFFS2_NODETYPE_INODE:
			s->sum_size += JFFS2_SUMMARY_INODE_SIZE;
			s->sum_num++;
			dbg_summary("inode (%u) added to summary\n",
						je32_to_cpu(item->i.inode));
			break;
		case JFFS2_NODETYPE_DIRENT:
			s->sum_size += JFFS2_SUMMARY_DIRENT_SIZE(item->d.nsize);
			s->sum_num++;
			dbg_summary("dirent (%u) added to summary\n",
						je32_to_cpu(item->d.ino));
			break;
#ifdef CONFIG_JFFS2_FS_XATTR
		case JFFS2_NODETYPE_XATTR:
			s->sum_size += JFFS2_SUMMARY_XATTR_SIZE;
			s->sum_num++;
			dbg_summary("xattr (xid=%u, version=%u) added to summary\n",
				    je32_to_cpu(item->x.xid), je32_to_cpu(item->x.version));
			break;
		case JFFS2_NODETYPE_XREF:
			s->sum_size += JFFS2_SUMMARY_XREF_SIZE;
			s->sum_num++;
			dbg_summary("xref added to summary\n");
			break;
#endif
		default:
			JFFS2_WARNING("UNKNOWN node type %u\n",
					    je16_to_cpu(item->u.nodetype));
			return 1;
	}
