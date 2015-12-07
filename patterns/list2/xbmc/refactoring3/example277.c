switch (vgmstream->meta_type) {
        case meta_RSTM:
            snprintf(temp,TEMPSIZE,"Nintendo RSTM header");
            break;
        case meta_STRM:
            snprintf(temp,TEMPSIZE,"Nintendo STRM header");
            break;
        case meta_ADX_03:
            snprintf(temp,TEMPSIZE,"CRI ADX header type 03");
            break;
        case meta_ADX_04:
            snprintf(temp,TEMPSIZE,"CRI ADX header type 04");
            break;
        case meta_ADX_05:
            snprintf(temp,TEMPSIZE,"CRI ADX header type 05");
            break;
        case meta_AIX:
            snprintf(temp,TEMPSIZE,"CRI AIX header");
            break;
        case meta_AAX:
            snprintf(temp,TEMPSIZE,"CRI AAX header");
            break;
        case meta_DSP_AGSC:
            snprintf(temp,TEMPSIZE,"Retro Studios AGSC header");
            break;
        case meta_NGC_ADPDTK:
            snprintf(temp,TEMPSIZE,"assumed Nintendo ADP by .adp extension and valid first frame");
            break;
        case meta_RSF:
            snprintf(temp,TEMPSIZE,"assumed Retro Studios RSF by .rsf extension and valid first bytes");
            break;
        case meta_AFC:
            snprintf(temp,TEMPSIZE,"Nintendo AFC header");
            break;
        case meta_AST:
            snprintf(temp,TEMPSIZE,"Nintendo AST header");
            break;
        case meta_HALPST:
            snprintf(temp,TEMPSIZE,"HAL Laboratory HALPST header");
            break;
        case meta_DSP_RS03:
            snprintf(temp,TEMPSIZE,"Retro Studios RS03 header");
            break;
        case meta_DSP_STD:
            snprintf(temp,TEMPSIZE,"Standard Nintendo DSP header");
            break;
        case meta_DSP_CSTR:
            snprintf(temp,TEMPSIZE,"Namco Cstr header");
            break;
        case meta_GCSW:
            snprintf(temp,TEMPSIZE,"GCSW header");
            break;
        case meta_PS2_SShd:
            snprintf(temp,TEMPSIZE,"SShd header");
            break;
		case meta_PS2_NPSF:
            snprintf(temp,TEMPSIZE,"Namco Production Sound File (NPSF) header");
            break;
        case meta_RWSD:
            snprintf(temp,TEMPSIZE,"Nintendo RWSD header (single stream)");
            break;
        case meta_RWAR:
            snprintf(temp,TEMPSIZE,"Nintendo RWAR header (single RWAV stream)");
            break;
        case meta_RWAV:
            snprintf(temp,TEMPSIZE,"Nintendo RWAV header");
            break;
        case meta_PSX_XA:
            snprintf(temp,TEMPSIZE,"RIFF/CDXA header");
            break;
		case meta_PS2_RXW:
            snprintf(temp,TEMPSIZE,"RXWS header)");
            break;
		case meta_PS2_RAW:
            snprintf(temp,TEMPSIZE,"assumed RAW Interleaved PCM by .int extension");
            break;
		case meta_PS2_OMU:
            snprintf(temp,TEMPSIZE,"Alter Echo OMU Header");
            break;
        case meta_DSP_STM:
            snprintf(temp,TEMPSIZE,"Nintendo STM header");
            break;
        case meta_PS2_EXST:
            snprintf(temp,TEMPSIZE,"EXST header");
            break;
        case meta_PS2_SVAG:
            snprintf(temp,TEMPSIZE,"Konami SVAG header");
            break;
        case meta_PS2_MIB:
            snprintf(temp,TEMPSIZE,"assumed MIB Interleaved file by .mib extension");
            break;
        case meta_PS2_MIB_MIH:
            snprintf(temp,TEMPSIZE,"assumed MIB with MIH Info Header file by .mib+.mih extension");
            break;
        case meta_DSP_MPDSP:
            snprintf(temp,TEMPSIZE,"Single DSP header stereo by .mpdsp extension");
            break;
        case meta_PS2_MIC:
            snprintf(temp,TEMPSIZE,"assume KOEI MIC file by .mic extension");
            break;
        case meta_DSP_JETTERS:
            snprintf(temp,TEMPSIZE,"Double DSP header stereo by _lr.dsp extension");
            break;
        case meta_DSP_MSS:
            snprintf(temp,TEMPSIZE,"Double DSP header stereo by .mss extension");
            break;
        case meta_DSP_GCM:
            snprintf(temp,TEMPSIZE,"Double DSP header stereo by .gcm extension");
            break;
		case meta_DSP_WII_IDSP:
            snprintf(temp,TEMPSIZE,"Wii IDSP Double DSP header");
            break;
        case meta_RSTM_SPM:
            snprintf(temp,TEMPSIZE,"Nintendo RSTM header and .brstmspm extension");
            break;
        case meta_RAW:
            snprintf(temp,TEMPSIZE,"assumed RAW PCM file by .raw extension");
            break;
		case meta_PS2_VAGi:
            snprintf(temp,TEMPSIZE,"Sony VAG Interleaved header (VAGi)");
            break;
		case meta_PS2_VAGp:
            snprintf(temp,TEMPSIZE,"Sony VAG Mono header (VAGp)");
            break;
		case meta_PS2_VAGs:
            snprintf(temp,TEMPSIZE,"Sony VAG Stereo header (VAGp)");
            break;
		case meta_PS2_VAGm:
            snprintf(temp,TEMPSIZE,"Sony VAG Mono header (VAGm)");
            break;
		case meta_PS2_pGAV:
            snprintf(temp,TEMPSIZE,"Sony VAG Stereo Little Endian header (pGAV)");
            break;
		case meta_PSX_GMS:
            snprintf(temp,TEMPSIZE,"assumed Grandia GMS file by .gms extension");
            break;
		case meta_PS2_STR:
            snprintf(temp,TEMPSIZE,"assumed STR + STH File by .str & .sth extension");
            break;
		case meta_PS2_ILD:
            snprintf(temp,TEMPSIZE,"ILD header");
            break;
		case meta_PS2_PNB:
            snprintf(temp,TEMPSIZE,"assumed PNB (PsychoNauts Bgm File) by .pnb extension");
            break;
		case meta_XBOX_WAVM:
            snprintf(temp,TEMPSIZE,"assumed Xbox WAVM file by .wavm extension");
            break;
		case meta_XBOX_RIFF:
            snprintf(temp,TEMPSIZE,"Xbox RIFF/WAVE file with 0x0069 Codec ID");
            break;
		case meta_DSP_STR:
            snprintf(temp,TEMPSIZE,"assumed Conan Gamecube STR File by .str extension");
            break;
		case meta_EAXA_R2:
            snprintf(temp,TEMPSIZE,"Electronic Arts XA R2");
            break;
		case meta_EAXA_R3:
            snprintf(temp,TEMPSIZE,"Electronic Arts XA R3");
            break;
		case meta_EA_ADPCM:
            snprintf(temp,TEMPSIZE,"Electronic Arts XA R1");
            break;
		case meta_EA_IMA:
            snprintf(temp,TEMPSIZE,"Electronic Arts container with IMA blocks");
            break;
		case meta_EAXA_PSX:
            snprintf(temp,TEMPSIZE,"Electronic Arts With PSX ADPCM");
            break;
		case meta_EA_PCM:
            snprintf(temp,TEMPSIZE,"Electronic Arts With PCM");
            break;
		case meta_CFN:
            snprintf(temp,TEMPSIZE,"Namco CAF Header");
            break;
		case meta_PS2_VPK:
            snprintf(temp,TEMPSIZE,"VPK Header");
            break;
        case meta_GENH:
            snprintf(temp,TEMPSIZE,"GENH Generic Header");
            break;
#ifdef VGM_USE_VORBIS
        case meta_ogg_vorbis:
            snprintf(temp,TEMPSIZE,"Ogg Vorbis");
            break;
        case meta_OGG_SLI:
            snprintf(temp,TEMPSIZE,"Ogg Vorbis with .sli (start,length) for looping");
            break;
        case meta_OGG_SLI2:
            snprintf(temp,TEMPSIZE,"Ogg Vorbis with .sli (from,to) for looping");
            break;
        case meta_OGG_SFL:
            snprintf(temp,TEMPSIZE,"Ogg Vorbis with SFPL for looping");
            break;
        case meta_um3_ogg:
            snprintf(temp,TEMPSIZE,"Ogg Vorbis, Ultramarine3 \"encryption\"");
            break;
#endif
        case meta_DSP_SADB:
            snprintf(temp,TEMPSIZE,"sadb header");
            break;
        case meta_SADL:
            snprintf(temp,TEMPSIZE,"sadl header");
            break;
        case meta_PS2_BMDX:
            snprintf(temp,TEMPSIZE,"Beatmania .bmdx header");
            break;
        case meta_DSP_WSI:
            snprintf(temp,TEMPSIZE,".wsi header");
            break;
        case meta_AIFC:
            snprintf(temp,TEMPSIZE,"Audio Interchange File Format AIFF-C");
            break;
        case meta_AIFF:
            snprintf(temp,TEMPSIZE,"Audio Interchange File Format");
            break;
        case meta_STR_SNDS:
            snprintf(temp,TEMPSIZE,".str SNDS SHDR chunk");
            break;
        case meta_WS_AUD:
            snprintf(temp,TEMPSIZE,"Westwood Studios .aud header");
            break;
        case meta_WS_AUD_old:
            snprintf(temp,TEMPSIZE,"Westwood Studios .aud (old) header");
            break;
#ifdef VGM_USE_MPEG
        case meta_AHX:
            snprintf(temp,TEMPSIZE,"CRI AHX header");
            break;
#endif
        case meta_PS2_IVB:
            snprintf(temp,TEMPSIZE,"IVB/BVII header");
            break;
        case meta_PS2_SVS:
            snprintf(temp,TEMPSIZE,"Square SVS header");
            break;
        case meta_RIFF_WAVE:
            snprintf(temp,TEMPSIZE,"RIFF WAVE header");
            break;
        case meta_RIFF_WAVE_POS:
            snprintf(temp,TEMPSIZE,"RIFF WAVE header and .pos for looping");
            break;
        case meta_NWA:
            snprintf(temp,TEMPSIZE,"Visual Art's NWA header");
            break;
        case meta_NWA_NWAINFOINI:
            snprintf(temp,TEMPSIZE,"Visual Art's NWA header and NWAINFO.INI for looping");
            break;
        case meta_NWA_GAMEEXEINI:
            snprintf(temp,TEMPSIZE,"Visual Art's NWA header and Gameexe.ini for looping");
            break;
        case meta_XSS:
            snprintf(temp,TEMPSIZE,"Dino Crisis 3 XSS File");
            break;
        case meta_HGC1:
            snprintf(temp,TEMPSIZE,"Knights of the Temple 2 hgC1 Header");
            break;
        case meta_AUS:
            snprintf(temp,TEMPSIZE,"Capcom AUS Header");
            break;
        case meta_RWS:
            snprintf(temp,TEMPSIZE,"RWS Header");
            break;
        case meta_EACS_PC:
            snprintf(temp,TEMPSIZE,"EACS Header (PC)");
            break;
        case meta_EACS_PSX:
            snprintf(temp,TEMPSIZE,"EACS Header (PSX)");
            break;
        case meta_EACS_SAT:
            snprintf(temp,TEMPSIZE,"EACS Header (SATURN)");
            break;
		case meta_SL3:
            snprintf(temp,TEMPSIZE,"SL3 Header");
            break;
		case meta_FSB1:
            snprintf(temp,TEMPSIZE,"FMOD Sample Bank (FSB1) Header");
            break;
		case meta_FSB3:
            snprintf(temp,TEMPSIZE,"FMOD Sample Bank (FSB3) Header");
            break;
		case meta_FSB4:
            snprintf(temp,TEMPSIZE,"FMOD Sample Bank (FSB4) Header");
            break;
		case meta_RWX:
            snprintf(temp,TEMPSIZE,"RWX Header");
            break;
		case meta_XWB:
            snprintf(temp,TEMPSIZE,"XWB WBND Header");
            break;
		case meta_XA30:
            snprintf(temp,TEMPSIZE,"XA30 Header");
            break;
		case meta_MUSC:
            snprintf(temp,TEMPSIZE,"MUSC Header");
            break;
		case meta_MUSX_V004:
            snprintf(temp,TEMPSIZE,"MUSX / Version 004 Header");
            break;
		case meta_MUSX_V006:
            snprintf(temp,TEMPSIZE,"MUSX / Version 006 Header");
            break;
		case meta_MUSX_V010:
            snprintf(temp,TEMPSIZE,"MUSX / Version 010 Header");
            break;
		case meta_MUSX_V201:
            snprintf(temp,TEMPSIZE,"MUSX / Version 201 Header");
            break;
		case meta_LEG:
            snprintf(temp,TEMPSIZE,"Legaia 2 - Duel Saga LEG Header");
            break;
		case meta_FILP:
            snprintf(temp,TEMPSIZE,"Bio Hazard - Gun Survivor FILp Header");
            break;
		case meta_IKM:
            snprintf(temp,TEMPSIZE,"Zwei!! IKM Header");
            break;
		case meta_SFS:
            snprintf(temp,TEMPSIZE,"Baroque SFS Header");
            break;
		case meta_DVI:
            snprintf(temp,TEMPSIZE,"DVI Header");
            break;
		case meta_KCEY:
            snprintf(temp,TEMPSIZE,"KCEYCOMP Header");
            break;
		case meta_BG00:
            snprintf(temp,TEMPSIZE,"Falcom BG00 Header");
            break;
		case meta_PS2_RSTM:
            snprintf(temp,TEMPSIZE,"Rockstar Games RSTM Header");
            break;
        case meta_ACM:
            snprintf(temp,TEMPSIZE,"InterPlay ACM Header");
            break;
        case meta_MUS_ACM:
            snprintf(temp,TEMPSIZE,"MUS playlist and multiple InterPlay ACM Headered files");
            break;
		case meta_PS2_KCES:
            snprintf(temp,TEMPSIZE,"Konami KCES Header");
            break;
        case meta_PS2_DXH:
            snprintf(temp,TEMPSIZE,"Tokobot Plus DXH Header");
            break;
        case meta_PS2_PSH:
            snprintf(temp,TEMPSIZE,"Dawn of Mana - Seiken Densetsu 4 PSH Header");
            break;
        case meta_RIFF_WAVE_labl_Marker:
            snprintf(temp,TEMPSIZE,"RIFF WAVE header with loop markers");
            break;
        case meta_RIFF_WAVE_smpl:
            snprintf(temp,TEMPSIZE,"RIFF WAVE header with sample looping info");
            break;
		case meta_PCM:
            snprintf(temp,TEMPSIZE,"PCM file with custom header");
            break;
		case meta_PS2_RKV:
            snprintf(temp,TEMPSIZE,"Legacy of Kain - Blood Omen 2 RKV Header");
            break;
		case meta_PS2_PSW:
            snprintf(temp,TEMPSIZE,"Rayman Raving Rabbids Riff Container File");
            break;
		case meta_PS2_VAS:
            snprintf(temp,TEMPSIZE,"Pro Baseball Spirits 5 VAS Header");
            break;
		case meta_PS2_TEC:
            snprintf(temp,TEMPSIZE,"assumed TECMO badflagged stream by .tec extension");
            break;
		case meta_XBOX_WVS:
            snprintf(temp,TEMPSIZE,"Metal Arms WVS Header");
            break;
		case meta_XBOX_STMA:
			snprintf(temp,TEMPSIZE,"Midnight Club 2 STMA Header");
			break;
		case meta_XBOX_MATX:
			snprintf(temp,TEMPSIZE,"assumed Matrix file by .matx extension");
			break;
        case meta_DE2:
            snprintf(temp,TEMPSIZE,"gurumin .de2 with embedded funky RIFF");
            break;
		case meta_VS:
            snprintf(temp,TEMPSIZE,"Men in Black VS Header");
            break;
        case meta_DC_STR:
            snprintf(temp,TEMPSIZE,"Sega Stream Asset Builder header");
            break;
        case meta_DC_STR_V2:
            snprintf(temp,TEMPSIZE,"variant of Sega Stream Asset Builder header");
            break;
        case meta_XBOX_XMU:
            snprintf(temp,TEMPSIZE,"XMU header");
            break;
        case meta_XBOX_XVAS:
            snprintf(temp,TEMPSIZE,"assumed TMNT file by .xvas extension");
            break;
		case meta_PS2_XA2:
            snprintf(temp,TEMPSIZE,"assumed XA2 file by .xa2 extension");
            break;
		case meta_DC_IDVI:
            snprintf(temp,TEMPSIZE,"IDVI Header");
            break;
		case meta_NGC_YMF:
            snprintf(temp,TEMPSIZE,"YMF DSP Header");
            break;
		case meta_PS2_CCC:
            snprintf(temp,TEMPSIZE,"CCC Header");
            break;
		case meta_PSX_FAG:
            snprintf(temp,TEMPSIZE,"FAG Header");
            break;
		case meta_PS2_MIHB:
            snprintf(temp,TEMPSIZE,"Merged MIH+MIB");
            break;
        case meta_DSP_WII_MUS:
            snprintf(temp,TEMPSIZE,"mus header");
            break;
        case meta_WII_SNG:
            snprintf(temp,TEMPSIZE,"SNG DSP Header");
            break;
		case meta_RSD2VAG:
            snprintf(temp,TEMPSIZE,"RSD2/VAG Header");
            break;
		case meta_RSD2PCMB:
            snprintf(temp,TEMPSIZE,"RSD2/PCMB Header");
            break;
		case meta_RSD2XADP:
            snprintf(temp,TEMPSIZE,"RSD2/XADP Header");
            break;
		case meta_RSD3PCM:
            snprintf(temp,TEMPSIZE,"RSD3/PCM Header");
            break;
		case meta_RSD4PCMB:
            snprintf(temp,TEMPSIZE,"RSD4/PCMB Header");
            break;
		case meta_RSD4PCM:
            snprintf(temp,TEMPSIZE,"RSD4/PCM Header");
            break;
		case meta_RSD4VAG:
            snprintf(temp,TEMPSIZE,"RSD4/VAG Header");
            break;
		case meta_RSD6XADP:
            snprintf(temp,TEMPSIZE,"RSD6/XADP Header");
            break;
		case meta_RSD6VAG:
            snprintf(temp,TEMPSIZE,"RSD6/VAG Header");
            break;
        case meta_RSD6WADP:
            snprintf(temp,TEMPSIZE,"RSD6/WADP Header");
            break;
		case meta_DC_ASD:
            snprintf(temp,TEMPSIZE,"ASD Header");
            break;
		case meta_NAOMI_SPSD:
            snprintf(temp,TEMPSIZE,"SPSD Header");
            break;
        case meta_FFXI_BGW:
            snprintf(temp,TEMPSIZE,"BGW BGMStream header");
            break;
        case meta_FFXI_SPW:
            snprintf(temp,TEMPSIZE,"SPW SeWave header");
            break;
        case meta_PS2_ASS:
            snprintf(temp,TEMPSIZE,"ASS Header");
            break;
		case meta_IDSP:
            snprintf(temp,TEMPSIZE,"IDSP Header");
            break;
		case meta_IDSP2:
            snprintf(temp,TEMPSIZE,"IDSP Header");
            break;
		case meta_WAA_WAC_WAD_WAM:
            snprintf(temp,TEMPSIZE,"WAA/WAC/WAD/WAM RIFF Header");
            break;
		case meta_PS2_SEG:
            snprintf(temp,TEMPSIZE,"SEG (PS2) Header");
            break;
		case meta_NDS_STRM_FFTA2:
            snprintf(temp,TEMPSIZE,"Final Fantasy Tactics A2 RIFF Header");
            break;
		case meta_STR_ASR:
            snprintf(temp,TEMPSIZE,"Donkey Kong Jet Race KNON/WII Header");
            break;
		case meta_ZWDSP:
            snprintf(temp,TEMPSIZE,"Zack and Wiki custom DSP Header");
            break;
		case meta_GCA:
            snprintf(temp,TEMPSIZE,"GCA DSP Header");
            break;
		case meta_SPT_SPD:
            snprintf(temp,TEMPSIZE,"SPT+SPD DSP Header");
            break;
		case meta_ISH_ISD:
            snprintf(temp,TEMPSIZE,"ISH+ISD DSP Header");
            break;
		case meta_YDSP:
            snprintf(temp,TEMPSIZE,"YDSP Header");
            break;
		case meta_MSVP:
            snprintf(temp,TEMPSIZE,"MSVP Header");
            break;
		case meta_NGC_SSM:
            snprintf(temp,TEMPSIZE,"SSM DSP Header");
            break;
		case meta_PS2_JOE:
            snprintf(temp,TEMPSIZE,"Disney/Pixar JOE Header");
            break;
		case meta_VGS:
            snprintf(temp,TEMPSIZE,"Guitar Hero Encore Rocks the 80's Header");
            break;
		case meta_DC_WAV_DCS:
            snprintf(temp,TEMPSIZE,"Evil Twin WAV+DCS Header");
            break;
		case meta_WII_SMP:
            snprintf(temp,TEMPSIZE,"SMP DSP Header");
            break;
		case meta_EMFF_PS2:
		case meta_EMFF_NGC:
            snprintf(temp,TEMPSIZE,"Eidos Music File Format Header");
            break;
		case meta_THP:
            snprintf(temp,TEMPSIZE,"THP Movie File Format Header");
            break;
		case meta_STS_WII:
            snprintf(temp,TEMPSIZE,"Shikigami no Shiro (WII) Header");
            break;
		case meta_PS2_P2BT:
            snprintf(temp,TEMPSIZE,"Pop'n'Music 7 Header");
            break;
		case meta_PS2_GBTS:
            snprintf(temp,TEMPSIZE,"Pop'n'Music 9 Header");
            break;
		case meta_NGC_IADP:
            snprintf(temp,TEMPSIZE,"Dr MUTO Header");
            break;
        case meta_RSTM_shrunken:
            snprintf(temp,TEMPSIZE,"Nintendo RSTM header, corrupted by Atlus");
            break;
        case meta_RIFF_WAVE_MWV:
            snprintf(temp,TEMPSIZE,"RIFF WAVE header with .mwv flavoring");
            break;
        case meta_FFCC_STR:
            snprintf(temp,TEMPSIZE,"Final Fantasy: Crystal Chronicles STR header");
            break;
        default:
            snprintf(temp,TEMPSIZE,"THEY SHOULD HAVE SENT A POET");
    }
