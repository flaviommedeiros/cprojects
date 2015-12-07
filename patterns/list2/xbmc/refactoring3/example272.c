switch (vgmstream->coding_type) {
        case coding_PCM16BE:
            snprintf(temp,TEMPSIZE,"Big Endian 16-bit PCM");
            break;
        case coding_PCM16LE:
            snprintf(temp,TEMPSIZE,"Little Endian 16-bit PCM");
            break;
        case coding_PCM16LE_int:
            snprintf(temp,TEMPSIZE,"Little Endian 16-bit PCM with 2 byte interleave");
            break;
        case coding_PCM8:
            snprintf(temp,TEMPSIZE,"8-bit PCM");
            break;
        case coding_PCM8_U_int:
            snprintf(temp,TEMPSIZE,"8-bit unsigned PCM with 1 byte interleave");
            break;
        case coding_PCM8_int:
            snprintf(temp,TEMPSIZE,"8-bit PCM with 1 byte interleave");
            break;
        case coding_PCM8_SB_int:
            snprintf(temp,TEMPSIZE,"8-bit PCM with sign bit, 1 byte interleave");
            break;
        case coding_NGC_DSP:
            snprintf(temp,TEMPSIZE,"Gamecube \"DSP\" 4-bit ADPCM");
            break;
        case coding_CRI_ADX:
            snprintf(temp,TEMPSIZE,"CRI ADX 4-bit ADPCM");
            break;
        case coding_CRI_ADX_enc:
            snprintf(temp,TEMPSIZE,"encrypted CRI ADX 4-bit ADPCM");
            break;
        case coding_NDS_IMA:
            snprintf(temp,TEMPSIZE,"NDS-style 4-bit IMA ADPCM");
            break;
        case coding_NGC_DTK:
            snprintf(temp,TEMPSIZE,"Gamecube \"ADP\"/\"DTK\" 4-bit ADPCM");
            break;
        case coding_G721:
            snprintf(temp,TEMPSIZE,"CCITT G.721 4-bit ADPCM");
            break;
        case coding_NGC_AFC:
            snprintf(temp,TEMPSIZE,"Gamecube \"AFC\" 4-bit ADPCM");
            break;
        case coding_PSX:
            snprintf(temp,TEMPSIZE,"Playstation 4-bit ADPCM");
            break;
        case coding_PSX_badflags:
            snprintf(temp,TEMPSIZE,"Playstation 4-bit ADPCM with bad flags");
            break;
        case coding_invert_PSX:
            snprintf(temp,TEMPSIZE,"BMDX \"encrypted\" Playstation 4-bit ADPCM");
            break;
        case coding_FFXI:
            snprintf(temp,TEMPSIZE,"FFXI Playstation-ish 4-bit ADPCM");
            break;
        case coding_XA:
            snprintf(temp,TEMPSIZE,"CD-ROM XA 4-bit ADPCM");
            break;
		case coding_XBOX:
            snprintf(temp,TEMPSIZE,"XBOX 4-bit IMA ADPCM");
            break;
		case coding_EAXA:
            snprintf(temp,TEMPSIZE,"Electronic Arts XA Based 4-bit ADPCM");
            break;
		case coding_EA_ADPCM:
            snprintf(temp,TEMPSIZE,"Electronic Arts XA Based (R1) 4-bit ADPCM");
            break;
#ifdef VGM_USE_VORBIS
        case coding_ogg_vorbis:
            snprintf(temp,TEMPSIZE,"Vorbis");
            break;
#endif
        case coding_SDX2:
            snprintf(temp,TEMPSIZE,"Squareroot-delta-exact (SDX2) 8-bit DPCM");
            break;
        case coding_SDX2_int:
            snprintf(temp,TEMPSIZE,"Squareroot-delta-exact (SDX2) 8-bit DPCM with 1 byte interleave");
            break;
        case coding_DVI_IMA:
            snprintf(temp,TEMPSIZE,"Intel DVI 4-bit IMA ADPCM");
            break;
        case coding_INT_DVI_IMA:
            snprintf(temp,TEMPSIZE,"Interleaved Intel DVI 4-bit IMA ADPCM");
            break;
		case coding_EACS_IMA:
            snprintf(temp,TEMPSIZE,"EACS 4-bit IMA ADPCM");
            break;
        case coding_INT_IMA:
            snprintf(temp,TEMPSIZE,"Interleaved 4-bit IMA ADPCM");
            break;
        case coding_IMA:
            snprintf(temp,TEMPSIZE,"4-bit IMA ADPCM");
            break;
        case coding_WS:
            snprintf(temp,TEMPSIZE,"Westwood Studios DPCM");
            break;
#ifdef VGM_USE_MPEG
        case coding_fake_MPEG2_L2:
            snprintf(temp,TEMPSIZE,"MPEG-2 Layer II Audio");
            break;
        case coding_MPEG1_L1:
            snprintf(temp,TEMPSIZE,"MPEG-1 Layer I Audio");
            break;
        case coding_MPEG1_L2:
            snprintf(temp,TEMPSIZE,"MPEG-1 Layer II Audio");
            break;
        case coding_MPEG1_L3:
            snprintf(temp,TEMPSIZE,"MPEG-1 Layer III Audio (MP3)");
            break;
        case coding_MPEG2_L1:
            snprintf(temp,TEMPSIZE,"MPEG-2 Layer I Audio");
            break;
        case coding_MPEG2_L2:
            snprintf(temp,TEMPSIZE,"MPEG-2 Layer II Audio");
            break;
        case coding_MPEG2_L3:
            snprintf(temp,TEMPSIZE,"MPEG-2 Layer III Audio (MP3)");
            break;
        case coding_MPEG25_L1:
            snprintf(temp,TEMPSIZE,"MPEG-2.5 Layer I Audio");
            break;
        case coding_MPEG25_L2:
            snprintf(temp,TEMPSIZE,"MPEG-2.5 Layer II Audio");
            break;
        case coding_MPEG25_L3:
            snprintf(temp,TEMPSIZE,"MPEG-2.5 Layer III Audio (MP3)");
            break;
#endif
        case coding_ACM:
            snprintf(temp,TEMPSIZE,"InterPlay ACM");
            break;
        case coding_NWA0:
            snprintf(temp,TEMPSIZE,"NWA DPCM Level 0");
            break;
        case coding_NWA1:
            snprintf(temp,TEMPSIZE,"NWA DPCM Level 1");
            break;
        case coding_NWA2:
            snprintf(temp,TEMPSIZE,"NWA DPCM Level 2");
            break;
        case coding_NWA3:
            snprintf(temp,TEMPSIZE,"NWA DPCM Level 3");
            break;
        case coding_NWA4:
            snprintf(temp,TEMPSIZE,"NWA DPCM Level 4");
            break;
        case coding_NWA5:
            snprintf(temp,TEMPSIZE,"NWA DPCM Level 5");
            break;
        case coding_MSADPCM:
            snprintf(temp,TEMPSIZE,"Microsoft 4-bit ADPCM");
            break;
        case coding_AICA:
            snprintf(temp,TEMPSIZE,"Yamaha AICA 4-bit ADPCM");
            break;
        case coding_NDS_PROCYON:
            snprintf(temp,TEMPSIZE,"Procyon Studio Digital Sound Elements NDS 4-bit APDCM");
            break;
        case coding_L5_555:
            snprintf(temp,TEMPSIZE,"Level-5 0x555 ADPCM");
            break;
        default:
            snprintf(temp,TEMPSIZE,"CANNOT DECODE");
    }
