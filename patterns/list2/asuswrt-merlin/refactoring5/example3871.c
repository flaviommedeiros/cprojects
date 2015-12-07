#ifdef CONFIG_NCPFS_EXTRAS
if (server->m.flags & NCP_MOUNT_EXTRAS) {
				/* any non-default execute bit set */
				if (newmode & ~server->m.file_mode & S_IXUGO)
					info.attributes |= aSHARED | aSYSTEM;
				/* read for group/world and not in default file_mode */
				else if (newmode & ~server->m.file_mode & S_IRUGO)
					info.attributes |= aSHARED;
			} else
#endif
				newmode &= server->m.file_mode;
