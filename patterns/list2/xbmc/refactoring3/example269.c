switch (vgmstream->coding_type) {
        case coding_CRI_ADX:
        case coding_CRI_ADX_enc:
        case coding_L5_555:
            return 32;
        case coding_NGC_DSP:
            return 14;
        case coding_PCM16LE:
		case coding_PCM16LE_int:
        case coding_PCM16BE:
        case coding_PCM8:
		case coding_PCM8_int:
        case coding_PCM8_SB_int:
        case coding_PCM8_U_int:
#ifdef VGM_USE_VORBIS
        case coding_ogg_vorbis:
#endif
#ifdef VGM_USE_MPEG
        case coding_fake_MPEG2_L2:
        case coding_MPEG1_L1:
        case coding_MPEG1_L2:
        case coding_MPEG1_L3:
        case coding_MPEG2_L1:
        case coding_MPEG2_L2:
        case coding_MPEG2_L3:
        case coding_MPEG25_L1:
        case coding_MPEG25_L2:
        case coding_MPEG25_L3:
#endif
        case coding_SDX2:
        case coding_SDX2_int:
        case coding_ACM:
        case coding_NWA0:
        case coding_NWA1:
        case coding_NWA2:
        case coding_NWA3:
        case coding_NWA4:
        case coding_NWA5:
            return 1;
        case coding_NDS_IMA:
				return (vgmstream->interleave_block_size-4)*2;
        case coding_NGC_DTK:
            return 28;
        case coding_G721:
        case coding_DVI_IMA:
		case coding_EACS_IMA:
        case coding_IMA:
            return 1;
        case coding_INT_IMA:
		case coding_INT_DVI_IMA:
        case coding_AICA:
			return 2;
        case coding_NGC_AFC:
        case coding_FFXI:
            return 16;
        case coding_PSX:
        case coding_PSX_badflags:
        case coding_invert_PSX:
		case coding_XA:
            return 28;
		case coding_XBOX:
			return 64;
		case coding_EAXA:
			return 28;
		case coding_EA_ADPCM:
			return 14*vgmstream->channels;
        case coding_WS:
            /* only works if output sample size is 8 bit, which is always
               is for WS ADPCM */
            return vgmstream->ws_output_size;
        case coding_MSADPCM:
            return (vgmstream->interleave_block_size-(7-1)*vgmstream->channels)*2/vgmstream->channels;
        case coding_NDS_PROCYON:
            return 30;
        default:
            return 0;
    }
