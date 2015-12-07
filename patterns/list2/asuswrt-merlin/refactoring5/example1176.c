#ifdef RTCONFIG_BCMARM
if ((mf = mtd_open_old(mtdname, &mi)) >= 0) {
#else
	if ((mf = mtd_open(mtdname, &mi)) >= 0) {
#endif
			r = 1;
#if 1
			ei.length = mi.erasesize;
			for (ei.start = 0; ei.start < mi.size; ei.start += mi.erasesize) {
				printf("%sing 0x%x - 0x%x\n", erase ? "Eras" : "Unlock", ei.start, (ei.start + ei.length) - 1);
				fflush(stdout);

				if (!skipbb) {
					loff_t offset = ei.start;

					if ((ret = ioctl(mf, MEMGETBADBLOCK, &offset)) > 0) {
						printf("Skipping bad block at 0x%08x\n", ei.start);
						continue;
					} else if (ret < 0) {
						if (errno == EOPNOTSUPP) {
							skipbb = 1;	// Not supported by this device
						} else {
							perror("MEMGETBADBLOCK");
							r = 0;
							break;
						}
					}
				}
				if (ioctl(mf, MEMUNLOCK, &ei) != 0) {
//					perror("MEMUNLOCK");
//					r = 0;
//					break;
				}
				if (erase) {
					if (ioctl(mf, MEMERASE, &ei) != 0) {
						perror("MEMERASE");
						r = 0;
						break;
					}
				}
			}
#else
			ei.start = 0;
			ei.length = mi.size;

			printf("%sing 0x%x - 0x%x\n", erase ? "Eras" : "Unlock", ei.start, ei.length - 1);
			fflush(stdout);

			if (ioctl(mf, MEMUNLOCK, &ei) != 0) {
				perror("MEMUNLOCK");
				r = 0;
			}
			else if (erase) {
				if (ioctl(mf, MEMERASE, &ei) != 0) {
					perror("MEMERASE");
					r = 0;
				}
			}
#endif

			// checkme:
			char buf[2];
			read(mf, &buf, sizeof(buf));
			close(mf);
	}

	set_action(ACT_IDLE);

	if (r) printf("\"%s\" successfully %s.\n", mtdname, erase ? "erased" : "unlocked");
        else printf("\nError %sing MTD\n", erase ? "eras" : "unlock");

	sleep(1);
	return r;
}
