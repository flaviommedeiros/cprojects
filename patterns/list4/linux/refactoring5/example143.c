#ifdef CONFIG_CPU_MICROMIPS
if (mm_insn_16bit(ip->halfword[0]))
				{
					unsigned short tmp;

					if (ip->halfword[0] & mm_addiusp_func)
					{
						tmp = (((ip->halfword[0] >> 1) & 0x1ff) << 2);
						info->frame_size = -(signed short)(tmp | ((tmp & 0x100) ? 0xfe00 : 0));
					} else {
						tmp = (ip->halfword[0] >> 1);
						info->frame_size = -(signed short)(tmp & 0xf);
					}
					ip = (void *) &ip->halfword[1];
					ip--;
				} else
#endif
				info->frame_size = - ip->i_format.simmediate;
