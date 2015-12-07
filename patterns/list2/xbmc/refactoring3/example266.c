switch (vgmstream->layout_type) {
        case layout_interleave:
        case layout_interleave_shortblock:
            render_vgmstream_interleave(buffer,sample_count,vgmstream);
            break;
#ifdef VGM_USE_VORBIS
        case layout_ogg_vorbis:
#endif
#ifdef VGM_USE_MPEG
        case layout_fake_mpeg:
        case layout_mpeg:
#endif
        case layout_dtk_interleave:
        case layout_none:
            render_vgmstream_nolayout(buffer,sample_count,vgmstream);
            break;
        case layout_ast_blocked:
        case layout_halpst_blocked:
		case layout_xa_blocked:
		case layout_ea_blocked:
		case layout_eacs_blocked:
		case layout_caf_blocked:
        case layout_wsi_blocked:
        case layout_str_snds_blocked:
        case layout_ws_aud_blocked:
		case layout_matx_blocked:
        case layout_de2_blocked:
		case layout_vs_blocked:
		case layout_emff_ps2_blocked:
		case layout_emff_ngc_blocked:
		case layout_gsb_blocked:
		case layout_xvas_blocked:
		case layout_thp_blocked:
		case layout_filp_blocked:
            render_vgmstream_blocked(buffer,sample_count,vgmstream);
            break;
        case layout_interleave_byte:
            render_vgmstream_interleave_byte(buffer,sample_count,vgmstream);
            break;
        case layout_acm:
        case layout_mus_acm:
            render_vgmstream_mus_acm(buffer,sample_count,vgmstream);
            break;
        case layout_aix:
            render_vgmstream_aix(buffer,sample_count,vgmstream);
            break;
        case layout_aax:
            render_vgmstream_aax(buffer,sample_count,vgmstream);
            break;
    }
