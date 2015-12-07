switch (vgmstream->layout_type) {
        case layout_none:
            snprintf(temp,TEMPSIZE,"flat (no layout)");
            break;
        case layout_interleave:
            snprintf(temp,TEMPSIZE,"interleave");
            break;
        case layout_interleave_shortblock:
            snprintf(temp,TEMPSIZE,"interleave with short last block");
            break;
        case layout_interleave_byte:
            snprintf(temp,TEMPSIZE,"sub-frame interleave");
            break;
        case layout_dtk_interleave:
            snprintf(temp,TEMPSIZE,"ADP/DTK nibble interleave");
            break;
        case layout_ast_blocked:
            snprintf(temp,TEMPSIZE,"AST blocked");
            break;
        case layout_halpst_blocked:
            snprintf(temp,TEMPSIZE,"HALPST blocked");
            break;
		case layout_xa_blocked:
            snprintf(temp,TEMPSIZE,"CD-ROM XA");
            break;
		case layout_ea_blocked:
            snprintf(temp,TEMPSIZE,"Electronic Arts Audio Blocks");
            break;
		case layout_eacs_blocked:
            snprintf(temp,TEMPSIZE,"Electronic Arts (Old Version) Audio Blocks");
            break;
		case layout_caf_blocked:
            snprintf(temp,TEMPSIZE,"CAF blocked");
            break;
        case layout_wsi_blocked:
            snprintf(temp,TEMPSIZE,".wsi blocked");
            break;
        case layout_xvas_blocked:
            snprintf(temp,TEMPSIZE,".xvas blocked");
            break;
#ifdef VGM_USE_VORBIS
        case layout_ogg_vorbis:
            snprintf(temp,TEMPSIZE,"Ogg");
            break;
#endif
        case layout_str_snds_blocked:
            snprintf(temp,TEMPSIZE,".str SNDS blocked");
            break;
        case layout_ws_aud_blocked:
            snprintf(temp,TEMPSIZE,"Westwood Studios .aud blocked");
            break;
        case layout_matx_blocked:
            snprintf(temp,TEMPSIZE,"Matrix .matx blocked");
            break;
        case layout_de2_blocked:
            snprintf(temp,TEMPSIZE,"de2 blocked");
            break;
		case layout_vs_blocked:
            snprintf(temp,TEMPSIZE,"vs blocked");
            break;
        case layout_emff_ps2_blocked:
            snprintf(temp,TEMPSIZE,"EMFF (PS2) blocked");
            break;
        case layout_emff_ngc_blocked:
            snprintf(temp,TEMPSIZE,"EMFF (NGC/WII) blocked");
            break;
        case layout_gsb_blocked:
            snprintf(temp,TEMPSIZE,"GSB blocked");
            break;
        case layout_thp_blocked:
            snprintf(temp,TEMPSIZE,"THP Movie Audio blocked");
            break;
        case layout_filp_blocked:
            snprintf(temp,TEMPSIZE,"FILp blocked");
            break;
#ifdef VGM_USE_MPEG
        case layout_fake_mpeg:
            snprintf(temp,TEMPSIZE,"MPEG Audio stream with incorrect frame headers");
            break;
        case layout_mpeg:
            snprintf(temp,TEMPSIZE,"MPEG Audio stream");
            break;
#endif
        case layout_acm:
            snprintf(temp,TEMPSIZE,"ACM blocked");
            break;
        case layout_mus_acm:
            snprintf(temp,TEMPSIZE,"multiple ACM files, ACM blocked");
            break;
        case layout_aix:
            snprintf(temp,TEMPSIZE,"AIX interleave, internally 18-byte interleaved");
            break;
        case layout_aax:
            snprintf(temp,TEMPSIZE,"AAX blocked, 18-byte interleaved");
            break;
        default:
            snprintf(temp,TEMPSIZE,"INCONCEIVABLE");
    }
