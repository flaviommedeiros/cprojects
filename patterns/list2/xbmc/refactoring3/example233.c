switch(cmd)
    {
      case WRD_LYRIC:
	p = wrd_event2string(wrd_args[0]);
	len = strlen(p);
	text = (char *)new_segment(&tmpbuffer, SAFE_CONVERT_LENGTH(len));

	/*This must be not good thing,but as far as I know no wrd file 
	  written in EUC-JP code can be found,And Hankaku kana required 
	  for layout of charactor and ASCII art.*/

	code_convert(p, text, SAFE_CONVERT_LENGTH(len), "SJIS", "JISK");
	AddLine(text,0);
	reuse_mblock(&tmpbuffer);
	break;
      case WRD_NL: /* Newline */
	AddLine("\n",0);
	break;
      case WRD_COLOR:
	txtclr_preserve=wrd_args[0];
	/*This length is at most 20 ; this is much lesser than LINEBUF*/
	snprintf(line_buf,LINEBUF,"\033[%dm", txtclr_preserve);
	AddLine(line_buf,0);
	break;
      case WRD_END: /* Never call */
	break;
      case WRD_ESC:
	AddLine("\033[",0);
	AddLine(wrd_event2string(wrd_args[0]),0);
	break;
      case WRD_EXEC:
	/*I don't spawn another program*/
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@EXEC(%s)", wrd_event2string(wrd_args[0]));
	break;
      case WRD_FADE:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@FADE(%d,%d,%d)", wrd_args[0], wrd_args[1], wrd_args[2]);
	x_Fade(wrd_args,wrd_argc-1,-1,-1);
	break;
      case WRD_FADESTEP:
#if 0
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@FADESTEP(%d/%d)", wrd_args[0], wrd_args[1]);
#endif
	x_Fade(NULL,0,wrd_args[0],wrd_args[1]);
	break;
      case WRD_GCIRCLE:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@GCIRCLE(%d,%d,%d,%d,%d,%d)",
		  wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3],
		  wrd_args[4], wrd_args[5]);
	x_GCircle(wrd_args,wrd_argc-1);
	break;
      case WRD_GCLS:
	x_Gcls(wrd_args[0]);
	break;
      case WRD_GINIT:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG, "@GINIT()");
	break;
      case WRD_GLINE:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@GLINE(%d,%d,%d,%d,%d,%d,%d)",
	       wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3], wrd_args[4],
	       wrd_args[5], wrd_args[6]);
	/*GRPH_LINE_MODE=1*/
	x_Gline(wrd_args,wrd_argc-1);
	break;
      case WRD_GMODE:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@GMODE(%d)", wrd_args[0]);
	x_GMode(wrd_args[0]);
	break;
      case WRD_GMOVE:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@GMOVE(%d,%d,%d,%d,%d,%d,%d,%d,%d)",
	       wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3], wrd_args[4],
	       wrd_args[5], wrd_args[6], wrd_args[7], wrd_args[8]);
	wrd_args[0] &= ~0x7;
	wrd_args[4] &= ~0x7;  
	wrd_args[2] |= 0x7;
 	x_GMove(wrd_args[0], wrd_args[1], wrd_args[2],
		wrd_args[3], wrd_args[4],wrd_args[5],
		wrd_args[6], wrd_args[7], wrd_args[8]);
	break;
      case WRD_GON:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@GON(%d)", wrd_args[0]);
	x_Gon(wrd_args[0]);
	break;
      case WRD_GSCREEN:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@GSCREEN(%d,%d)", wrd_args[0], wrd_args[1]);
	x_Gscreen(wrd_args[0],wrd_args[1]);
	break;
      case WRD_INKEY:
	inkey_flag = 1;
	ctl->cmsg(CMSG_INFO, VERB_DEBUG, "@INKEY - begin");
	break;
      case WRD_OUTKEY:
	inkey_flag = 0;
	ctl->cmsg(CMSG_INFO, VERB_DEBUG, "@INKEY - end");
	break;
      case WRD_LOCATE:
	/*Length is At most 40*/
	snprintf(line_buf,LINEBUF,"\033[%d;%dH", wrd_args[1], wrd_args[0]);
	AddLine(line_buf,0);
	break;
      case WRD_LOOP: /* Never call */
	break;
      case WRD_MAG:
  	{
	  magdata *m;
	  p = (char *)new_segment(&tmpbuffer, MIN_MBLOCK_SIZE);
	  snprintf(p, MIN_MBLOCK_SIZE-1, "@MAG(%s", wrd_event2string(wrd_args[0]));
	  p[MIN_MBLOCK_SIZE-1] = '\0'; /* fail safe */
	  for(i = 1; i < 5; i++)
	  {
	      if(wrd_args[i] == WRD_NOARG)
		  strncat(p, ",*", MIN_MBLOCK_SIZE - strlen(p) - 1);
	      else {
		  char q[CHAR_BIT*sizeof(int)];
		  snprintf(q, sizeof(q)-1, ",%d", wrd_args[i]);
		  strncat(p, q, MIN_MBLOCK_SIZE - strlen(p) - 1);
	      }
	  }
	  strncat(p, ")", MIN_MBLOCK_SIZE - strlen(p) - 1);
	  ctl->cmsg(CMSG_INFO, VERB_VERBOSE, "%s", p);
	  m=mag_search(wrd_event2string(wrd_args[0]));
	  if(m!=NULL){
	    x_Mag(m,wrd_args[1],wrd_args[2],wrd_args[3],wrd_args[4]);
	  }
	  reuse_mblock(&tmpbuffer);
	  break;
  	}
      case WRD_MIDI: /* Never call */
	break;
      case WRD_OFFSET: /* Never call */
	break;
      case WRD_PAL:
	x_Pal(wrd_args,wrd_argc-1);
	break;
      case WRD_PALCHG:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@PALCHG(%s)", wrd_event2string(wrd_args[0]));
	break;
      case WRD_PALREV:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@PALREV(%d)", wrd_args[0]);
	x_Palrev(wrd_args[0]);
	break;
      case WRD_PATH:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@PATH(%s)", wrd_event2string(wrd_args[0]));
	wrd_add_path(wrd_event2string(wrd_args[0]), 0);
	break;
      case WRD_PLOAD:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@PLOAD(%s)", wrd_event2string(wrd_args[0]));
	x_PLoad(wrd_event2string(wrd_args[0]));
	break;
      case WRD_REM:
	p = wrd_event2string(wrd_args[0]);
	len = strlen(p);
	text = (char *)new_segment(&tmpbuffer, SAFE_CONVERT_LENGTH(len));
	code_convert(p, text, SAFE_CONVERT_LENGTH(len), NULL, NULL);
	ctl->cmsg(CMSG_INFO, VERB_DEBUG, "@REM %s", text);
	reuse_mblock(&tmpbuffer);
	break;
      case WRD_REMARK:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@REMARK(%s)", wrd_event2string(wrd_args[0]));
	break;
      case WRD_REST: /* Never call */
	break;
      case WRD_SCREEN: /* Not supported */
	break;
      case WRD_SCROLL:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@SCROLL(%d,%d,%d,%d,%d,%d,%d)",
		  wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3],
		  wrd_args[4], wrd_args[5], wrd_args[6]);
	break;
      case WRD_STARTUP:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@STARTUP(%d)", wrd_args[0]);
	wrd_init_path();
	inkey_flag = 0;
	x_Startup(wrd_args[0]);
	load_default_graphics(current_file_info->filename);
	break;
      case WRD_STOP: /* Never call */
	break;
      case WRD_TCLS:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@TCLS(%d,%d,%d,%d,%d,%d)",
		  wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3],
		  wrd_args[4], wrd_args[5]);
	{
	  char fillbuf[1024];
	  int xdiff;
	  xdiff=wrd_args[2]-wrd_args[0]+1;
	  if(xdiff>80)
	    xdiff = 79-wrd_args[0]+1;
	  if(xdiff<0||xdiff>80)
	    break;
	  fillbuf[0]=0x1b;
	  fillbuf[1]='[';
	  fillbuf[2]='s';
	  fillbuf[3]=0;
	  AddLine(fillbuf,0);
	  i=wrd_args[4];
	  /*This Length is no more than 1024*/
	  sprintf(fillbuf,"\033[%dm",i);
	  AddLine(fillbuf,0);
	  memset(fillbuf,wrd_args[5],xdiff);/*X2-X1*/
	  fillbuf[xdiff]=0;
	  for(i=wrd_args[1];i<=wrd_args[3];i++){/*Y1 to Y2*/
	    snprintf(line_buf,LINEBUF,"\033[%d;%dH",i,wrd_args[0]);
/*X1to....*/
	    AddLine(line_buf,0);
	    AddLine(fillbuf,0);
	  }
	  fillbuf[0]=0x1b;
	  fillbuf[1]='[';
	  fillbuf[2]='u';
	  fillbuf[3]=0;
	  AddLine(fillbuf,0);
	}
	break;
      case WRD_TON:
	ctl->cmsg(CMSG_INFO, VERB_DEBUG,
		  "@TON(%d)", wrd_args[0]);
	x_Ton(wrd_args[0]);
	break;
      case WRD_WAIT: /* Never call */
	break;
      case WRD_WMODE: /* Never call */
	break;

	/* Ensyutsukun */
      case WRD_eFONTM:
	print_ecmd("FONTM", wrd_args, 1);
	break;
      case WRD_eFONTP:
	print_ecmd("FONTP", wrd_args, 4);
	break;
      case WRD_eFONTR:
	print_ecmd("FONTR", wrd_args, 17);
	break;
      case WRD_eGSC:
	print_ecmd("GSC", wrd_args, 1);
	break;
      case WRD_eLINE:
	print_ecmd("LINE", wrd_args, 1);
	break;
      case WRD_ePAL:
	print_ecmd("PAL", wrd_args, 2);
	break;
      case WRD_eREGSAVE:
	print_ecmd("REGSAVE", wrd_args, 17);
	break;
      case WRD_eSCROLL:
	print_ecmd("SCROLL",wrd_args, 2);
	break;
      case WRD_eTEXTDOT:
	print_ecmd("TEXTDOT", wrd_args, 1);
	break;
      case WRD_eTMODE:
	print_ecmd("TMODE", wrd_args, 1);
	break;
      case WRD_eTSCRL:
	print_ecmd("TSCRL", wrd_args, 0);
	break;
      case WRD_eVCOPY:
	print_ecmd("VCOPY", wrd_args, 9);
	x_VCopy(wrd_args[0],wrd_args[1],wrd_args[2],wrd_args[3]
		,wrd_args[4],wrd_args[5],wrd_args[6],wrd_args[7],wrd_args[8]);
	break;
      case WRD_eVSGET:
	print_ecmd("VSGET", wrd_args, 4);
	x_VSget(wrd_args,4);
	break;
      case WRD_eVSRES:
	print_ecmd("VSRES", wrd_args, 0);
	x_VRel();
	break;
      case WRD_eXCOPY:
	if(wrd_argc < 9)
	    break;
	x_XCopy(wrd_args[0],wrd_args[1],wrd_args[2],wrd_args[3],wrd_args[4],
		wrd_args[5],wrd_args[6],wrd_args[7],wrd_args[8],
		wrd_args + 9, wrd_argc - 9);
	break;

	/* Extensionals */
      case WRD_START_SKIP:
	if(current_wrd_mode == WRD_TRACE_MIMPI)
	    x_RedrawControl(0);
#ifdef ENABLE_SHERRY
	else if(current_wrd_mode == WRD_TRACE_SHERRY)
	    x_sry_redraw_ctl(0);
#endif /* ENABLE_SHERRY */
	break;
      case WRD_END_SKIP:
	if(current_wrd_mode == WRD_TRACE_MIMPI)
	    x_RedrawControl(1);
#ifdef ENABLE_SHERRY
	else if(current_wrd_mode == WRD_TRACE_SHERRY)
	    x_sry_redraw_ctl(1);
#endif /* ENABLE_SHERRY */
	break;
#ifdef ENABLE_SHERRY
      case WRD_SHERRY_UPDATE:
	x_sry_update();
	break;
#endif /* ENABLE_SHERRY */
    }
