#ifdef USE_JPWL
if (j2k->cp->correct) {

		/* totlen is negative or larger than the bytes left!!! */
		if ((totlen < 0) || (totlen > (cio_numbytesleft(cio) + 8))) {
			opj_event_msg(j2k->cinfo, EVT_ERROR,
				"JPWL: bad tile byte size (%d bytes against %d bytes left)\n",
				totlen, cio_numbytesleft(cio) + 8);
			if (!JPWL_ASSUME) {
				opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
				return;
			}
			/* we try to correct */
			totlen = 0;
			opj_event_msg(j2k->cinfo, EVT_WARNING, "- trying to adjust this\n"
				"- setting Psot to %d => assuming it is the last tile\n",
				totlen);
		}

	}
  else
#endif /* USE_JPWL */
  {
    /* totlen is negative or larger than the bytes left!!! */
    if ((totlen < 0) || (totlen > (cio_numbytesleft(cio) + 8))) {
      opj_event_msg(j2k->cinfo, EVT_ERROR,
        "JPWL: bad tile byte size (%d bytes against %d bytes left)\n",
        totlen, cio_numbytesleft(cio) + 8);
      return;
    }
  }
