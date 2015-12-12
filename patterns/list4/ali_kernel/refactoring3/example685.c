switch (je16_to_cpu(((struct jffs2_sum_unknown_flash *)sp)->nodetype)) {
			case JFFS2_NODETYPE_INODE: {
				struct jffs2_sum_inode_flash *spi;
				spi = sp;

				ino = je32_to_cpu(spi->inode);

				dbg_summary("Inode at 0x%08x-0x%08x\n",
					    jeb->offset + je32_to_cpu(spi->offset),
					    jeb->offset + je32_to_cpu(spi->offset) + je32_to_cpu(spi->totlen));

				ic = jffs2_scan_make_ino_cache(c, ino);
				if (!ic) {
					JFFS2_NOTICE("scan_make_ino_cache failed\n");
					return -ENOMEM;
				}

				sum_link_node_ref(c, jeb, je32_to_cpu(spi->offset) | REF_UNCHECKED,
						  PAD(je32_to_cpu(spi->totlen)), ic);

				*pseudo_random += je32_to_cpu(spi->version);

				sp += JFFS2_SUMMARY_INODE_SIZE;

				break;
			}

			case JFFS2_NODETYPE_DIRENT: {
				struct jffs2_sum_dirent_flash *spd;
				int checkedlen;
				spd = sp;

				dbg_summary("Dirent at 0x%08x-0x%08x\n",
					    jeb->offset + je32_to_cpu(spd->offset),
					    jeb->offset + je32_to_cpu(spd->offset) + je32_to_cpu(spd->totlen));


				/* This should never happen, but https://dev.laptop.org/ticket/4184 */
				checkedlen = strnlen(spd->name, spd->nsize);
				if (!checkedlen) {
					printk(KERN_ERR "Dirent at %08x has zero at start of name. Aborting mount.\n",
					       jeb->offset + je32_to_cpu(spd->offset));
					return -EIO;
				}
				if (checkedlen < spd->nsize) {
					printk(KERN_ERR "Dirent at %08x has zeroes in name. Truncating to %d chars\n",
					       jeb->offset + je32_to_cpu(spd->offset), checkedlen);
				}


				fd = jffs2_alloc_full_dirent(checkedlen+1);
				if (!fd)
					return -ENOMEM;

				memcpy(&fd->name, spd->name, checkedlen);
				fd->name[checkedlen] = 0;

				ic = jffs2_scan_make_ino_cache(c, je32_to_cpu(spd->pino));
				if (!ic) {
					jffs2_free_full_dirent(fd);
					return -ENOMEM;
				}

				fd->raw = sum_link_node_ref(c, jeb,  je32_to_cpu(spd->offset) | REF_UNCHECKED,
							    PAD(je32_to_cpu(spd->totlen)), ic);

				fd->next = NULL;
				fd->version = je32_to_cpu(spd->version);
				fd->ino = je32_to_cpu(spd->ino);
				fd->nhash = full_name_hash(fd->name, checkedlen);
				fd->type = spd->type;

				jffs2_add_fd_to_list(c, fd, &ic->scan_dents);

				*pseudo_random += je32_to_cpu(spd->version);

				sp += JFFS2_SUMMARY_DIRENT_SIZE(spd->nsize);

				break;
			}
#ifdef CONFIG_JFFS2_FS_XATTR
			case JFFS2_NODETYPE_XATTR: {
				struct jffs2_xattr_datum *xd;
				struct jffs2_sum_xattr_flash *spx;

				spx = (struct jffs2_sum_xattr_flash *)sp;
				dbg_summary("xattr at %#08x-%#08x (xid=%u, version=%u)\n", 
					    jeb->offset + je32_to_cpu(spx->offset),
					    jeb->offset + je32_to_cpu(spx->offset) + je32_to_cpu(spx->totlen),
					    je32_to_cpu(spx->xid), je32_to_cpu(spx->version));

				xd = jffs2_setup_xattr_datum(c, je32_to_cpu(spx->xid),
								je32_to_cpu(spx->version));
				if (IS_ERR(xd))
					return PTR_ERR(xd);
				if (xd->version > je32_to_cpu(spx->version)) {
					/* node is not the newest one */
					struct jffs2_raw_node_ref *raw
						= sum_link_node_ref(c, jeb, je32_to_cpu(spx->offset) | REF_UNCHECKED,
								    PAD(je32_to_cpu(spx->totlen)), NULL);
					raw->next_in_ino = xd->node->next_in_ino;
					xd->node->next_in_ino = raw;
				} else {
					xd->version = je32_to_cpu(spx->version);
					sum_link_node_ref(c, jeb, je32_to_cpu(spx->offset) | REF_UNCHECKED,
							  PAD(je32_to_cpu(spx->totlen)), (void *)xd);
				}
				*pseudo_random += je32_to_cpu(spx->xid);
				sp += JFFS2_SUMMARY_XATTR_SIZE;

				break;
			}
			case JFFS2_NODETYPE_XREF: {
				struct jffs2_xattr_ref *ref;
				struct jffs2_sum_xref_flash *spr;

				spr = (struct jffs2_sum_xref_flash *)sp;
				dbg_summary("xref at %#08x-%#08x\n",
					    jeb->offset + je32_to_cpu(spr->offset),
					    jeb->offset + je32_to_cpu(spr->offset) + 
					    (uint32_t)PAD(sizeof(struct jffs2_raw_xref)));

				ref = jffs2_alloc_xattr_ref();
				if (!ref) {
					JFFS2_NOTICE("allocation of xattr_datum failed\n");
					return -ENOMEM;
				}
				ref->next = c->xref_temp;
				c->xref_temp = ref;

				sum_link_node_ref(c, jeb, je32_to_cpu(spr->offset) | REF_UNCHECKED,
						  PAD(sizeof(struct jffs2_raw_xref)), (void *)ref);

				*pseudo_random += ref->node->flash_offset;
				sp += JFFS2_SUMMARY_XREF_SIZE;

				break;
			}
#endif
			default : {
				uint16_t nodetype = je16_to_cpu(((struct jffs2_sum_unknown_flash *)sp)->nodetype);
				JFFS2_WARNING("Unsupported node type %x found in summary! Exiting...\n", nodetype);
				if ((nodetype & JFFS2_COMPAT_MASK) == JFFS2_FEATURE_INCOMPAT)
					return -EIO;

				/* For compatible node types, just fall back to the full scan */
				c->wasted_size -= jeb->wasted_size;
				c->free_size += c->sector_size - jeb->free_size;
				c->used_size -= jeb->used_size;
				c->dirty_size -= jeb->dirty_size;
				jeb->wasted_size = jeb->used_size = jeb->dirty_size = 0;
				jeb->free_size = c->sector_size;

				jffs2_free_jeb_node_refs(c, jeb);
				return -ENOTRECOVERABLE;
			}
		}
