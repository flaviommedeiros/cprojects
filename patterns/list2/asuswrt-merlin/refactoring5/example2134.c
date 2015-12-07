#ifdef CONFIG_JOLIET
if (sbi->s_joliet_level) {
				len = get_joliet_filename(de, tmpname, inode);
				p = tmpname;
			} else
#endif
			if (sbi->s_mapping == 'a') {
				len = get_acorn_filename(de, tmpname, inode);
				p = tmpname;
			} else
			if (sbi->s_mapping == 'n') {
				len = isofs_name_translate(de, tmpname, inode);
				p = tmpname;
			} else {
				p = de->name;
				len = de->name_len[0];
			}
