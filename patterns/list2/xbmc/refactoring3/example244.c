switch(cmd)
    {
    case WRD_LYRIC:
    case WRD_NL:
		if(cmd == WRD_NL)
			text = "\n";
		else{
			p = wrd_event2string(wrd_args[0]);
			len = strlen(p);
			text = (char *)new_segment(&tmpbuffer, SAFE_CONVERT_LENGTH(len));
			code_convert(p, text, SAFE_CONVERT_LENGTH(len), NULL, NULL);
		}
		len = strlen(text);
		if( len ){
		mac_wrd_DrawText(text, text[len-1]=='\n'? len-1:len);
		if( text[len-1]=='\n' ){
			dev_newline();
		}
		ctl->cmsg(CMSG_INFO, VERB_VERBOSE, "%s", text);
		}
		reuse_mblock(&tmpbuffer);
		break;
      case WRD_COLOR:
		mac_wrd_color(wrd_args[0]);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE, "@COLOR(%d)", wrd_args[0]));
	break;
      case WRD_END: /* Never call */
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,"@END"));
	break;
      case WRD_ESC:
      	mac_wrd_event_esc(wrd_args[0]);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@ESC(%s)", wrd_event2string(wrd_args[0])));
	break;
      case WRD_EXEC:
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@EXEC(%s)", wrd_event2string(wrd_args[0])));
	break;
      case WRD_FADE:
	mac_wrd_fade(wrd_args[0], wrd_args[1], wrd_args[2]);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@FADE(%d,%d,%d)", wrd_args[0], wrd_args[1], wrd_args[2]));
	break;
      case WRD_FADESTEP:
	wrd_fadestep(wrd_args[0], WRD_MAXFADESTEP);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@FADESTEP(%d/%d)", wrd_args[0], WRD_MAXFADESTEP));
	break;
      case WRD_GCIRCLE:
	dev_gcircle(wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3],
		  wrd_args[4], wrd_args[5]);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@GCIRCLE(%d,%d,%d,%d,%d,%d)",
		  wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3],
		  wrd_args[4], wrd_args[5]));
	break;
      case WRD_GCLS:
	dev_clear_graphics(wrd_args[0]? wrd_args[0]:0xFF);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@GCLS(%d)", wrd_args[0]));
	break;
      case WRD_GINIT:
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE, "@GINIT()"));
	break;
      case WRD_GLINE:
	dev_gline(wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3], wrd_args[4],
	       wrd_args[5], wrd_args[6],graphicWorld[activeGraphics]);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@GLINE(%d,%d,%d,%d,%d,%d,%d)",
	       wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3], wrd_args[4],
	       wrd_args[5], wrd_args[6]));
	break;
      case WRD_GMODE:
	DEV_SET_GMODE(wrd_args[0]);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@GMODE(%d)", wrd_args[0]));
	break;
      case WRD_GMOVE:
	wrd_args[0] &= ~0x7;  wrd_args[4] &= ~0x7;  
	wrd_args[2] |= 0x7;
	dev_gmove(wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3], wrd_args[4],
	       wrd_args[5], graphicWorld[wrd_args[6]], graphicWorld[wrd_args[7]],
	       wrd_args[8], 0, gmode_mask, 0,0,0);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@GMOVE(%d,%d, %d,%d, %d,%d, %d,%d,%d)",
	       wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3], wrd_args[4],
	       wrd_args[5], wrd_args[6], wrd_args[7], wrd_args[8]));
	break;
      case WRD_GON:
	dev_gon(wrd_args[0]);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@GON(%d)", wrd_args[0]));
	break;
      case WRD_GSCREEN:
	dev_gscreen(wrd_args[0], wrd_args[1]);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@GSCREEN(%d,%d)", wrd_args[0], wrd_args[1]));
	break;
      case WRD_INKEY:
	inkey_flag = 1;
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE, "@INKEY - begin"));
	break;
      case WRD_OUTKEY:
	inkey_flag = 0;
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE, "@INKEY - end"));
	break;
      case WRD_LOCATE:
		dev_move_coursor(wrd_args[0], wrd_args[1]);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@LOCATE(%d,%d)", wrd_args[0], wrd_args[1]));
	break;
      case WRD_LOOP: /* Never call */
	break;
    case WRD_MAG:
   	wrd_mag(wrd_event2string(wrd_args[0]), wrd_args[1], wrd_args[2], wrd_args[3], wrd_args[4]);
/* 	p = (char *)new_segment(&tmpbuffer, MIN_MBLOCK_SIZE); */
/* 	strcpy(p, "@MAG("); */
/* 	strcat(p, wrd_event2string(wrd_args[0])); */
/* 	strcat(p, ","); */
/* 	for(i = 1; i < 3; i++) */
/* 	{ */
/* 	    if(wrd_args[i] == WRD_NOARG) */
/* 		strcat(p, "*,"); */
/* 	    else */
/* 		sprintf(p + strlen(p), "%d,", wrd_args[i]); */
/* 	} */
/* 	sprintf(p + strlen(p), "%d,%d)", wrd_args[3], wrd_args[4]); */
/* 	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE, "%s", p)); */
/* 	reuse_mblock(&tmpbuffer); */
	break;
      case WRD_MIDI: /* Never call */
	break;
      case WRD_OFFSET: /* Never call */
	break;
      case WRD_PAL:
/*       	mac_wrd_pal( wrd_args[0], &wrd_args[1]); */
/* 	p = (char *)new_segment(&tmpbuffer, MIN_MBLOCK_SIZE); */
/* 	sprintf(p, "@PAL(%03x", wrd_args[0]); */
/* 	for(i = 1; i < 17; i++) */
/* 	    sprintf(p + strlen(p), ",%03x", wrd_args[i]); */
/* 	strcat(p, ")"); */
/* 	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE, "%s", p)); */
/* 	reuse_mblock(&tmpbuffer); */
	break;
      case WRD_PALCHG:
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@PALCHG(%s)", wrd_event2string(wrd_args[0])));
	break;
      case WRD_PALREV:
	dev_palrev(wrd_args[0]);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@PALREV(%d)", wrd_args[0]));
	break;
      case WRD_PATH:
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@PATH(%s)", wrd_event2string(wrd_args[0])));
	break;
      case WRD_PLOAD:
   	wrd_pho(wrd_event2string(wrd_args[0]));
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@PLOAD(%s)", wrd_event2string(wrd_args[0])));
	break;
      case WRD_REM:
	p = wrd_event2string(wrd_args[0]);
	len = strlen(p);
	text = (char *)new_segment(&tmpbuffer, SAFE_CONVERT_LENGTH(len));
	code_convert(p, text, SAFE_CONVERT_LENGTH(len), NULL, NULL);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE, "@REM %s", text));
	reuse_mblock(&tmpbuffer);
	break;
      case WRD_REMARK:
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@REMARK(%s)", wrd_event2string(wrd_args[0])));
	break;
      case WRD_REST: /* Never call */
	break;
      case WRD_SCREEN: /* Not supported */
	break;
      case WRD_SCROLL:
	dev_text_scroll(wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3],
					wrd_args[4], wrd_args[5], wrd_args[6], 1);
	dev_remake_disp(portRect);
	dev_redisp(portRect);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@SCROLL(%d,%d,%d,%d,%d,%d,%d)",
		  wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3],
		  wrd_args[4], wrd_args[5], wrd_args[6]));
	break;
      case WRD_STARTUP:
	dev_init(wrd_args[0]);
	dev_init_text_color();
	wrd_load_default_image();
	inkey_flag = 0;
	dev_set_height(400);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@STARTUP(%d)", wrd_args[0]));
	break;
      case WRD_STOP: /* Never call */
	break;
      case WRD_TCLS:
	dev_text_clear(wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3],wrd_args[4],wrd_args[5], true);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@TCLS(%d,%d,%d,%d,%d,%d)",
		  wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3],
		  wrd_args[4], wrd_args[5]));
	break;
      case WRD_TON:
	wrd_ton=wrd_args[0];
	dev_remake_disp(portRect);
	dev_redisp(portRect);
	WRD_DEBUG((CMSG_INFO, VERB_VERBOSE,
		  "@TON(%d)", wrd_args[0]));
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
	wrd_args[0] &= ~0x7;  wrd_args[4] &= ~0x7;  
	wrd_args[2] |= 0x7;
	dev_gmove(wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3],
		wrd_args[4],wrd_args[5],
	       graphicWorld[wrd_args[6]+(wrd_args[8]? 2:0)],
	       graphicWorld[wrd_args[7]+ (wrd_args[8]? 0:2)], 0/*normal copy*/,0,gmode_mask,
	       0,0,0 );
			//ignore mode in this version, always EMS->GVRAM
	print_ecmd("VCOPY", wrd_args, 9);
	break;
      case WRD_eVSGET:
	dev_vsget(wrd_args[0]);
	print_ecmd("VSGE", wrd_args, 4);
	break;
      case WRD_eVSRES:
	print_ecmd("VSRES", wrd_args, 0);
	break;
      case WRD_eXCOPY:
	dev_gmove(wrd_args[0], wrd_args[1], wrd_args[2], wrd_args[3], wrd_args[4],
	     		wrd_args[5], graphicWorld[wrd_args[6]], graphicWorld[wrd_args[7]],
	       		wrd_args[8]+0x10, 0/*trans*/, gmode_mask, 0,0,0 );	
	print_ecmd("XCOPY", wrd_args, 14);
	break;

	/* Extensionals */
      case WRD_START_SKIP:
	    mac_RedrawControl(0);
	ctl->cmsg(CMSG_INFO, VERB_VERBOSE,
		  "WRD START SKIP");
	break;
      case WRD_END_SKIP:
	    mac_RedrawControl(1);
	ctl->cmsg(CMSG_INFO, VERB_VERBOSE,
		  "WRD END SKIP");
	break;
#ifdef ENABLE_SHERRY
      case WRD_SHERRY_UPDATE:
	sry_update();
	break;
#endif
    }
