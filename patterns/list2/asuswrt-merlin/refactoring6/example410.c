if (!strncmp(model, "CD-ROM DRIVE:25", 15) ||
		    !strncmp(model, "CD-ROM DRIVE:36", 15) ||
		    !strncmp(model, "CD-ROM DRIVE:83", 15) ||
		    !strncmp(model, "CD-ROM DRIVE:84 ", 16)
#if 0
		/* my NEC 3x returns the read-raw data if a read-raw
		   is followed by a read for the same sector - aeb */
		    || !strncmp(model, "CD-ROM DRIVE:500", 16)
#endif
		    )
			/* these can't handle multisession, may hang */
			cd->cdi.mask |= CDC_MULTI_SESSION;
