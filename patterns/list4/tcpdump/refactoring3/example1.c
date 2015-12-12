switch (fhtype) {
	case FHT_AUSPEX:
	    fsidp->Fsid_dev.Minor = fhp[7];
	    fsidp->Fsid_dev.Major = fhp[6];
	    fsidp->fsid_code = 0;

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "Auspex";
	    break;

	case FHT_BSD44:
	    fsidp->Fsid_dev.Minor = fhp[0];
	    fsidp->Fsid_dev.Major = fhp[1];
	    fsidp->fsid_code = 0;

	    *inop = make_uint32(fhp[15], fhp[14], fhp[13], fhp[12]);

	    if (osnamep)
		*osnamep = "BSD 4.4";
	    break;

	case FHT_DECOSF:
	    fsidp->fsid_code = make_uint32(fhp[7], fhp[6], fhp[5], fhp[4]);
			/* XXX could ignore 3 high-order bytes */

	    temp = make_uint32(fhp[3], fhp[2], fhp[1], fhp[0]);
	    fsidp->Fsid_dev.Minor = temp & 0xFFFFF;
	    fsidp->Fsid_dev.Major = (temp>>20) & 0xFFF;

	    *inop = make_uint32(fhp[15], fhp[14], fhp[13], fhp[12]);
	    if (osnamep)
		*osnamep = "OSF";
	    break;

	case FHT_IRIX4:
	    fsidp->Fsid_dev.Minor = fhp[3];
	    fsidp->Fsid_dev.Major = fhp[2];
	    fsidp->fsid_code = 0;

	    *inop = make_uint32(fhp[8], fhp[9], fhp[10], fhp[11]);

	    if (osnamep)
		*osnamep = "IRIX4";
	    break;

	case FHT_IRIX5:
	    fsidp->Fsid_dev.Minor = make_uint16(fhp[2], fhp[3]);
	    fsidp->Fsid_dev.Major = make_uint16(fhp[0], fhp[1]);
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "IRIX5";
	    break;

#ifdef notdef
	case FHT_SUNOS3:
	    /*
	     * XXX - none of the heuristics above return this.
	     * Are there any SunOS 3.x systems around to care about?
	     */
	    if (osnamep)
		*osnamep = "SUNOS3";
	    break;
#endif

	case FHT_SUNOS4:
	    fsidp->Fsid_dev.Minor = fhp[3];
	    fsidp->Fsid_dev.Major = fhp[2];
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "SUNOS4";
	    break;

	case FHT_SUNOS5:
	    temp = make_uint16(fhp[0], fhp[1]);
	    fsidp->Fsid_dev.Major = (temp>>2) &  0x3FFF;
	    temp = make_uint24(fhp[1], fhp[2], fhp[3]);
	    fsidp->Fsid_dev.Minor = temp & 0x3FFFF;
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "SUNOS5";
	    break;

	case FHT_ULTRIX:
	    fsidp->fsid_code = 0;
	    fsidp->Fsid_dev.Minor = fhp[0];
	    fsidp->Fsid_dev.Major = fhp[1];

	    temp = make_uint32(fhp[7], fhp[6], fhp[5], fhp[4]);
	    *inop = temp;
	    if (osnamep)
		*osnamep = "Ultrix";
	    break;

	case FHT_VMSUCX:
	    /* No numeric file system ID, so hash on the device-name */
	    if (sizeof(*fsidp) >= 14) {
		if (sizeof(*fsidp) > 14)
		    memset((char *)fsidp, 0, sizeof(*fsidp));
		/* just use the whole thing */
		memcpy((char *)fsidp, (const char *)fh, 14);
	    }
	    else {
		uint32_t tempa[4];	/* at least 16 bytes, maybe more */

		memset((char *)tempa, 0, sizeof(tempa));
		memcpy((char *)tempa, (const char *)fh, 14); /* ensure alignment */
		fsidp->Fsid_dev.Minor = tempa[0] + (tempa[1]<<1);
		fsidp->Fsid_dev.Major = tempa[2] + (tempa[3]<<1);
		fsidp->fsid_code = 0;
	    }

	    /* VMS file ID is: (RVN, FidHi, FidLo) */
	    *inop = make_uint32(fhp[26], fhp[27], fhp[23], fhp[22]);

	    /* Caller must save (and null-terminate?) this value */
	    if (fsnamep)
		*fsnamep = (const char *)&(fhp[1]);

	    if (osnamep)
		*osnamep = "VMS";
	    break;

	case FHT_AIX32:
	    fsidp->Fsid_dev.Minor = make_uint16(fhp[2], fhp[3]);
	    fsidp->Fsid_dev.Major = make_uint16(fhp[0], fhp[1]);
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "AIX32";
	    break;

	case FHT_HPUX9:
	    fsidp->Fsid_dev.Major = fhp[0];
	    temp = make_uint24(fhp[1], fhp[2], fhp[3]);
	    fsidp->Fsid_dev.Minor = temp;
	    fsidp->fsid_code = make_uint32(fhp[4], fhp[5], fhp[6], fhp[7]);

	    *inop = make_uint32(fhp[12], fhp[13], fhp[14], fhp[15]);

	    if (osnamep)
		*osnamep = "HPUX9";
	    break;

	case FHT_UNKNOWN:
#ifdef DEBUG
	    /* XXX debugging */
	    for (i = 0; i < 32; i++)
		(void)fprintf(stderr, "%x.", fhp[i]);
	    (void)fprintf(stderr, "\n");
#endif
	    /* Save the actual handle, so it can be display with -u */
	    for (i = 0; i < 32; i++)
	    	(void)snprintf(&(fsidp->Opaque_Handle[i*2]), 3, "%.2X", fhp[i]);

	    /* XXX for now, give "bogus" values to aid debugging */
	    fsidp->fsid_code = 0;
	    fsidp->Fsid_dev.Minor = 257;
	    fsidp->Fsid_dev.Major = 257;
	    *inop = 1;

	    /* display will show this string instead of (257,257) */
	    if (fsnamep)
		*fsnamep = "Unknown";

	    if (osnamep)
		*osnamep = "Unknown";
	    break;

	}
