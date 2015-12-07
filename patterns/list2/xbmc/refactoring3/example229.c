switch (eff)
      {
      case 0x01:		/* set tempo */
	UniEffect (UNI_S3MEFFECTA, inf);
	break;
      case 0x02:		/* set BPM */
	if (inf >= 0x20)
	  UniEffect (UNI_S3MEFFECTT, inf);
	break;
      case 0x03:		/* tone portamento */
	UniEffect (UNI_ITEFFECTG, inf);
	break;
      case 0x04:		/* porta + volslide */
	UniEffect (UNI_ITEFFECTG, inf);
	UniEffect (UNI_S3MEFFECTD, 0);
	break;
      case 0x05:		/* vibrato */
	UniPTEffect (0x4, inf);
	break;
      case 0x06:		/* vibrato + volslide */
	UniPTEffect (0x4, inf);
	UniEffect (UNI_S3MEFFECTD, 0);
	break;
      case 0x07:		/* fine vibrato */
	UniEffect (UNI_ITEFFECTU, inf);
	break;
      case 0x08:		/* tremolo */
	UniEffect (UNI_S3MEFFECTR, inf);
	break;
      case 0x09:		/* arpeggio */
	UniPTEffect (0x0, inf);
	break;
      case 0x0a:		/* panning */
	UniPTEffect (0x8, (inf >= 128) ? 255 : (inf << 1));
	break;
      case 0x0b:		/* pan slide */
	UniEffect (UNI_XMEFFECTP, inf);
	break;
      case 0x0c:		/* set channel volume */
	if (inf <= 64)
	  UniPTEffect (0xc, inf);
	break;
      case 0x0d:		/* volume slide */
	UniEffect (UNI_S3MEFFECTD, inf);
	break;
      case 0x0e:		/* fine volume slide */
	if (inf)
	  {
	    if (inf >> 4)
	      UniEffect (UNI_S3MEFFECTD, 0x0f | inf);
	    else
	      UniEffect (UNI_S3MEFFECTD, 0xf0 | inf);
	  }
	else
	  UniEffect (UNI_S3MEFFECTD, 0);
	break;
      case 0x0f:		/* set finetune */
	UniPTEffect (0xe, 0x50 | (inf >> 4));
	break;
#ifdef MIKMOD_DEBUG
      case 0x10:		/* note slide up */
      case 0x11:		/* not slide down */
	fprintf (stderr, "\rIMF effect 0x10/0x11 (note slide)"
		 " not implemented (eff=%2X inf=%2X)\n", eff, inf);
	break;
#endif
      case 0x12:		/* slide up */
	UniEffect (UNI_S3MEFFECTF, inf);
	break;
      case 0x13:		/* slide down */
	UniEffect (UNI_S3MEFFECTE, inf);
	break;
      case 0x14:		/* fine slide up */
	if (inf)
	  {
	    if (inf < 0x40)
	      UniEffect (UNI_S3MEFFECTF, 0xe0 | (inf / 4));
	    else
	      UniEffect (UNI_S3MEFFECTF, 0xf0 | (inf >> 4));
	  }
	else
	  UniEffect (UNI_S3MEFFECTF, 0);
	break;
      case 0x15:		/* fine slide down */
	if (inf)
	  {
	    if (inf < 0x40)
	      UniEffect (UNI_S3MEFFECTE, 0xe0 | (inf / 4));
	    else
	      UniEffect (UNI_S3MEFFECTE, 0xf0 | (inf >> 4));
	  }
	else
	  UniEffect (UNI_S3MEFFECTE, 0);
	break;
	/* 0x16 set filter cutoff (awe32) */
	/* 0x17 filter side + resonance (awe32) */
      case 0x18:		/* sample offset */
	UniPTEffect (0x9, inf);
	break;
#ifdef MIKMOD_DEBUG
      case 0x19:		/* set fine sample offset */
	fprintf (stderr, "\rIMF effect 0x19 (fine sample offset)"
		 " not implemented (inf=%2X)\n", inf);
	break;
#endif
      case 0x1a:		/* keyoff */
	UniWriteByte (UNI_KEYOFF);
	break;
      case 0x1b:		/* retrig */
	UniEffect (UNI_S3MEFFECTQ, inf);
	break;
      case 0x1c:		/* tremor */
	UniEffect (UNI_S3MEFFECTI, inf);
	break;
      case 0x1d:		/* position jump */
	UniPTEffect (0xb, inf);
	break;
      case 0x1e:		/* pattern break */
	UniPTEffect (0xd, (inf >> 4) * 10 + (inf & 0xf));
	break;
      case 0x1f:		/* set master volume */
	if (inf <= 64)
	  UniEffect (UNI_XMEFFECTG, inf);
	break;
      case 0x20:		/* master volume slide */
	UniEffect (UNI_XMEFFECTH, inf);
	break;
      case 0x21:		/* extended effects */
	switch (inf >> 4)
	  {
	  case 0x1:		/* set filter */
	  case 0x5:		/* vibrato waveform */
	  case 0x8:		/* tremolo waveform */
	    UniPTEffect (0xe, inf - 0x10);
	    break;
	  case 0xa:		/* pattern loop */
	    UniPTEffect (0xe, 0x60 | (inf & 0xf));
	    break;
	  case 0xb:		/* pattern delay */
	    UniPTEffect (0xe, 0xe0 | (inf & 0xf));
	    break;
	  case 0x3:		/* glissando */
	  case 0xc:		/* note cut */
	  case 0xd:		/* note delay */
	  case 0xf:		/* invert loop */
	    UniPTEffect (0xe, inf);
	    break;
	  case 0xe:		/* ignore envelope */
	    UniEffect (UNI_ITEFFECTS0, 0x77);	/* vol */
	    UniEffect (UNI_ITEFFECTS0, 0x79);	/* pan */
	    UniEffect (UNI_ITEFFECTS0, 0x7b);	/* pit */
	    break;
	  }
	break;
	/* 0x22 chorus (awe32) */
	/* 0x23 reverb (awe32) */
      }
