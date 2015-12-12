#ifdef USE_JPWL
if (j2k->cp->correct) {

		static int backup_tileno = 0;

		/* tileno is negative or larger than the number of tiles!!! */
		if ((tileno < 0) || (tileno >= (cp->tw * cp->th))) {
			opj_event_msg(j2k->cinfo, EVT_ERROR,
				"JPWL: bad tile number (%d out of a maximum of %d)\n",
				tileno, (cp->tw * cp->th));
			if (!JPWL_ASSUME) {
				opj_event_msg(j2k->cinfo, EVT_ERROR, "JPWL: giving up\n");
				return;
			}
			/* we try to correct */
			tileno = backup_tileno;
			opj_event_msg(j2k->cinfo, EVT_WARNING, "- trying to adjust this\n"
				"- setting tile number to %d\n",
				tileno);
		}

		/* keep your private count of tiles */
		backup_tileno++;
	}
  else
#endif /* USE_JPWL */
  {
    /* tileno is negative or larger than the number of tiles!!! */
    if ((tileno < 0) || (tileno >= (cp->tw * cp->th))) {
      opj_event_msg(j2k->cinfo, EVT_ERROR,
        "JPWL: bad tile number (%d out of a maximum of %d)\n",
        tileno, (cp->tw * cp->th));
      return;
    }
  }
