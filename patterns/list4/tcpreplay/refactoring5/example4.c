#ifdef BECtl
if (osize == 0) {
	/*  Buffer acquired directly through acqfcn. */
	struct bdhead *bd;

	bd = BDH(((char *) buf) - sizeof(struct bdhead));
	osize = bd->tsize - sizeof(struct bdhead);
    } else
#endif
	osize -= sizeof(struct bhead);
