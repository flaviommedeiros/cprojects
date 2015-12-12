switch(je16_to_cpu(node->nodetype)) {
		case JFFS2_NODETYPE_INODE:
			if (buf_ofs + buf_len < ofs + sizeof(struct jffs2_raw_inode)) {
				buf_len = min_t(uint32_t, buf_size, jeb->offset + c->sector_size - ofs);
				D1(printk(KERN_DEBUG "Fewer than %zd bytes (inode node) left to end of buf. Reading 0x%x at 0x%08x\n",
					  sizeof(struct jffs2_raw_inode), buf_len, ofs));
				err = jffs2_fill_scan_buf(c, buf, ofs, buf_len);
				if (err)
					return err;
				buf_ofs = ofs;
				node = (void *)buf;
			}
			err = jffs2_scan_inode_node(c, jeb, (void *)node, ofs, s);
			if (err) return err;
			ofs += PAD(je32_to_cpu(node->totlen));
			break;

		case JFFS2_NODETYPE_DIRENT:
			if (buf_ofs + buf_len < ofs + je32_to_cpu(node->totlen)) {
				buf_len = min_t(uint32_t, buf_size, jeb->offset + c->sector_size - ofs);
				D1(printk(KERN_DEBUG "Fewer than %d bytes (dirent node) left to end of buf. Reading 0x%x at 0x%08x\n",
					  je32_to_cpu(node->totlen), buf_len, ofs));
				err = jffs2_fill_scan_buf(c, buf, ofs, buf_len);
				if (err)
					return err;
				buf_ofs = ofs;
				node = (void *)buf;
			}
			err = jffs2_scan_dirent_node(c, jeb, (void *)node, ofs, s);
			if (err) return err;
			ofs += PAD(je32_to_cpu(node->totlen));
			break;

#ifdef CONFIG_JFFS2_FS_XATTR
		case JFFS2_NODETYPE_XATTR:
			if (buf_ofs + buf_len < ofs + je32_to_cpu(node->totlen)) {
				buf_len = min_t(uint32_t, buf_size, jeb->offset + c->sector_size - ofs);
				D1(printk(KERN_DEBUG "Fewer than %d bytes (xattr node)"
					  " left to end of buf. Reading 0x%x at 0x%08x\n",
					  je32_to_cpu(node->totlen), buf_len, ofs));
				err = jffs2_fill_scan_buf(c, buf, ofs, buf_len);
				if (err)
					return err;
				buf_ofs = ofs;
				node = (void *)buf;
			}
			err = jffs2_scan_xattr_node(c, jeb, (void *)node, ofs, s);
			if (err)
				return err;
			ofs += PAD(je32_to_cpu(node->totlen));
			break;
		case JFFS2_NODETYPE_XREF:
			if (buf_ofs + buf_len < ofs + je32_to_cpu(node->totlen)) {
				buf_len = min_t(uint32_t, buf_size, jeb->offset + c->sector_size - ofs);
				D1(printk(KERN_DEBUG "Fewer than %d bytes (xref node)"
					  " left to end of buf. Reading 0x%x at 0x%08x\n",
					  je32_to_cpu(node->totlen), buf_len, ofs));
				err = jffs2_fill_scan_buf(c, buf, ofs, buf_len);
				if (err)
					return err;
				buf_ofs = ofs;
				node = (void *)buf;
			}
			err = jffs2_scan_xref_node(c, jeb, (void *)node, ofs, s);
			if (err)
				return err;
			ofs += PAD(je32_to_cpu(node->totlen));
			break;
#endif	/* CONFIG_JFFS2_FS_XATTR */

		case JFFS2_NODETYPE_CLEANMARKER:
			D1(printk(KERN_DEBUG "CLEANMARKER node found at 0x%08x\n", ofs));
			if (je32_to_cpu(node->totlen) != c->cleanmarker_size) {
				printk(KERN_NOTICE "CLEANMARKER node found at 0x%08x has totlen 0x%x != normal 0x%x\n",
				       ofs, je32_to_cpu(node->totlen), c->cleanmarker_size);
				if ((err = jffs2_scan_dirty_space(c, jeb, PAD(sizeof(struct jffs2_unknown_node)))))
					return err;
				ofs += PAD(sizeof(struct jffs2_unknown_node));
			} else if (jeb->first_node) {
				printk(KERN_NOTICE "CLEANMARKER node found at 0x%08x, not first node in block (0x%08x)\n", ofs, jeb->offset);
				if ((err = jffs2_scan_dirty_space(c, jeb, PAD(sizeof(struct jffs2_unknown_node)))))
					return err;
				ofs += PAD(sizeof(struct jffs2_unknown_node));
			} else {
				jffs2_link_node_ref(c, jeb, ofs | REF_NORMAL, c->cleanmarker_size, NULL);

				ofs += PAD(c->cleanmarker_size);
			}
			break;

		case JFFS2_NODETYPE_PADDING:
			if (jffs2_sum_active())
				jffs2_sum_add_padding_mem(s, je32_to_cpu(node->totlen));
			if ((err = jffs2_scan_dirty_space(c, jeb, PAD(je32_to_cpu(node->totlen)))))
				return err;
			ofs += PAD(je32_to_cpu(node->totlen));
			break;

		default:
			switch (je16_to_cpu(node->nodetype) & JFFS2_COMPAT_MASK) {
			case JFFS2_FEATURE_ROCOMPAT:
				printk(KERN_NOTICE "Read-only compatible feature node (0x%04x) found at offset 0x%08x\n", je16_to_cpu(node->nodetype), ofs);
				c->flags |= JFFS2_SB_FLAG_RO;
				if (!(jffs2_is_readonly(c)))
					return -EROFS;
				if ((err = jffs2_scan_dirty_space(c, jeb, PAD(je32_to_cpu(node->totlen)))))
					return err;
				ofs += PAD(je32_to_cpu(node->totlen));
				break;

			case JFFS2_FEATURE_INCOMPAT:
				printk(KERN_NOTICE "Incompatible feature node (0x%04x) found at offset 0x%08x\n", je16_to_cpu(node->nodetype), ofs);
				return -EINVAL;

			case JFFS2_FEATURE_RWCOMPAT_DELETE:
				D1(printk(KERN_NOTICE "Unknown but compatible feature node (0x%04x) found at offset 0x%08x\n", je16_to_cpu(node->nodetype), ofs));
				if ((err = jffs2_scan_dirty_space(c, jeb, PAD(je32_to_cpu(node->totlen)))))
					return err;
				ofs += PAD(je32_to_cpu(node->totlen));
				break;

			case JFFS2_FEATURE_RWCOMPAT_COPY: {
				D1(printk(KERN_NOTICE "Unknown but compatible feature node (0x%04x) found at offset 0x%08x\n", je16_to_cpu(node->nodetype), ofs));

				jffs2_link_node_ref(c, jeb, ofs | REF_PRISTINE, PAD(je32_to_cpu(node->totlen)), NULL);

				/* We can't summarise nodes we don't grok */
				jffs2_sum_disable_collecting(s);
				ofs += PAD(je32_to_cpu(node->totlen));
				break;
				}
			}
		}
