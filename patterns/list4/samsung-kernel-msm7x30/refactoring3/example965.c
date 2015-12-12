switch (je16_to_cpu(node->u.nodetype)) {
		case JFFS2_NODETYPE_INODE: {
			struct jffs2_sum_inode_mem *temp =
				kmalloc(sizeof(struct jffs2_sum_inode_mem), GFP_KERNEL);

			if (!temp)
				goto no_mem;

			temp->nodetype = node->i.nodetype;
			temp->inode = node->i.ino;
			temp->version = node->i.version;
			temp->offset = cpu_to_je32(ofs);
			temp->totlen = node->i.totlen;
			temp->next = NULL;

			return jffs2_sum_add_mem(c->summary, (union jffs2_sum_mem *)temp);
		}

		case JFFS2_NODETYPE_DIRENT: {
			struct jffs2_sum_dirent_mem *temp =
				kmalloc(sizeof(struct jffs2_sum_dirent_mem) + node->d.nsize, GFP_KERNEL);

			if (!temp)
				goto no_mem;

			temp->nodetype = node->d.nodetype;
			temp->totlen = node->d.totlen;
			temp->offset = cpu_to_je32(ofs);
			temp->pino = node->d.pino;
			temp->version = node->d.version;
			temp->ino = node->d.ino;
			temp->nsize = node->d.nsize;
			temp->type = node->d.type;
			temp->next = NULL;

			switch (count) {
				case 1:
					memcpy(temp->name,node->d.name,node->d.nsize);
					break;

				case 2:
					memcpy(temp->name,invecs[1].iov_base,node->d.nsize);
					break;

				default:
					BUG();	/* impossible count value */
					break;
			}

			return jffs2_sum_add_mem(c->summary, (union jffs2_sum_mem *)temp);
		}
#ifdef CONFIG_JFFS2_FS_XATTR
		case JFFS2_NODETYPE_XATTR: {
			struct jffs2_sum_xattr_mem *temp;
			temp = kmalloc(sizeof(struct jffs2_sum_xattr_mem), GFP_KERNEL);
			if (!temp)
				goto no_mem;

			temp->nodetype = node->x.nodetype;
			temp->xid = node->x.xid;
			temp->version = node->x.version;
			temp->totlen = node->x.totlen;
			temp->offset = cpu_to_je32(ofs);
			temp->next = NULL;

			return jffs2_sum_add_mem(c->summary, (union jffs2_sum_mem *)temp);
		}
		case JFFS2_NODETYPE_XREF: {
			struct jffs2_sum_xref_mem *temp;
			temp = kmalloc(sizeof(struct jffs2_sum_xref_mem), GFP_KERNEL);
			if (!temp)
				goto no_mem;
			temp->nodetype = node->r.nodetype;
			temp->offset = cpu_to_je32(ofs);
			temp->next = NULL;

			return jffs2_sum_add_mem(c->summary, (union jffs2_sum_mem *)temp);
		}
#endif
		case JFFS2_NODETYPE_PADDING:
			dbg_summary("node PADDING\n");
			c->summary->sum_padded += je32_to_cpu(node->u.totlen);
			break;

		case JFFS2_NODETYPE_CLEANMARKER:
			dbg_summary("node CLEANMARKER\n");
			break;

		case JFFS2_NODETYPE_SUMMARY:
			dbg_summary("node SUMMARY\n");
			break;

		default:
			/* If you implement a new node type you should also implement
			   summary support for it or disable summary.
			*/
			BUG();
			break;
	}
