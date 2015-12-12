switch (je16_to_cpu(temp->u.nodetype)) {
			case JFFS2_NODETYPE_INODE: {
				struct jffs2_sum_inode_flash *sino_ptr = wpage;

				sino_ptr->nodetype = temp->i.nodetype;
				sino_ptr->inode = temp->i.inode;
				sino_ptr->version = temp->i.version;
				sino_ptr->offset = temp->i.offset;
				sino_ptr->totlen = temp->i.totlen;

				wpage += JFFS2_SUMMARY_INODE_SIZE;

				break;
			}

			case JFFS2_NODETYPE_DIRENT: {
				struct jffs2_sum_dirent_flash *sdrnt_ptr = wpage;

				sdrnt_ptr->nodetype = temp->d.nodetype;
				sdrnt_ptr->totlen = temp->d.totlen;
				sdrnt_ptr->offset = temp->d.offset;
				sdrnt_ptr->pino = temp->d.pino;
				sdrnt_ptr->version = temp->d.version;
				sdrnt_ptr->ino = temp->d.ino;
				sdrnt_ptr->nsize = temp->d.nsize;
				sdrnt_ptr->type = temp->d.type;

				memcpy(sdrnt_ptr->name, temp->d.name,
							temp->d.nsize);

				wpage += JFFS2_SUMMARY_DIRENT_SIZE(temp->d.nsize);

				break;
			}
#ifdef CONFIG_JFFS2_FS_XATTR
			case JFFS2_NODETYPE_XATTR: {
				struct jffs2_sum_xattr_flash *sxattr_ptr = wpage;

				temp = c->summary->sum_list_head;
				sxattr_ptr->nodetype = temp->x.nodetype;
				sxattr_ptr->xid = temp->x.xid;
				sxattr_ptr->version = temp->x.version;
				sxattr_ptr->offset = temp->x.offset;
				sxattr_ptr->totlen = temp->x.totlen;

				wpage += JFFS2_SUMMARY_XATTR_SIZE;
				break;
			}
			case JFFS2_NODETYPE_XREF: {
				struct jffs2_sum_xref_flash *sxref_ptr = wpage;

				temp = c->summary->sum_list_head;
				sxref_ptr->nodetype = temp->r.nodetype;
				sxref_ptr->offset = temp->r.offset;

				wpage += JFFS2_SUMMARY_XREF_SIZE;
				break;
			}
#endif
			default : {
				if ((je16_to_cpu(temp->u.nodetype) & JFFS2_COMPAT_MASK)
				    == JFFS2_FEATURE_RWCOMPAT_COPY) {
					dbg_summary("Writing unknown RWCOMPAT_COPY node type %x\n",
						    je16_to_cpu(temp->u.nodetype));
					jffs2_sum_disable_collecting(c->summary);
				} else {
					BUG();	/* unknown node in summary information */
				}
			}
		}
