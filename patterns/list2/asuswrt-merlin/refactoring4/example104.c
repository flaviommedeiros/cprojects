#ifndef LINUX_2_6_36
if (fw->target != target_num(entry, &handle))
#else
				if (fw->target != target_num(entry, handle))
#endif /* linux-2.6.36 */
					continue;
