switch (vgmstream->coding_type) {
        case coding_CRI_ADX:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_adx(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }

            break;
        case coding_CRI_ADX_enc:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_adx_enc(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }

            break;
        case coding_NGC_DSP:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_ngc_dsp(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_PCM16LE:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_pcm16LE(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_PCM16LE_int:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_pcm16LE_int(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_PCM16BE:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_pcm16BE(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_PCM8:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_pcm8(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_PCM8_int:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_pcm8_int(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_PCM8_SB_int:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_pcm8_sb_int(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_PCM8_U_int:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_pcm8_unsigned_int(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_NDS_IMA:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_nds_ima(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
		case coding_XBOX:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_xbox_ima(vgmstream,&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do,chan);
            }
            break;
        case coding_NGC_DTK:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_ngc_dtk(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do,chan);
            }
            break;
        case coding_G721:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_g721(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_NGC_AFC:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_ngc_afc(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_PSX:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_psx(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_PSX_badflags:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_psx_badflags(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_invert_PSX:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_invert_psx(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_FFXI:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_ffxi_adpcm(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
		case coding_XA:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_xa(vgmstream,buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do,chan);
            }
            break;
		case coding_EAXA:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_eaxa(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do,chan);
            }
            break;
		case coding_EA_ADPCM:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_ea_adpcm(vgmstream,buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do,chan);
            }
            break;
#ifdef VGM_USE_VORBIS
        case coding_ogg_vorbis:
            decode_ogg_vorbis(vgmstream->codec_data,
                    buffer+samples_written*vgmstream->channels,samples_to_do,
                    vgmstream->channels);
            break;
#endif
        case coding_SDX2:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_sdx2(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_SDX2_int:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_sdx2_int(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
		case coding_DVI_IMA:
		case coding_INT_DVI_IMA:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_dvi_ima(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
		case coding_EACS_IMA:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_eacs_ima(vgmstream,buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do,chan);
            }
            break;
		case coding_IMA:
        case coding_INT_IMA:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_ima(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_WS:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_ws(vgmstream,chan,buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
#ifdef VGM_USE_MPEG
        case coding_fake_MPEG2_L2:
            decode_fake_mpeg2_l2(
                    &vgmstream->ch[0],
                    vgmstream->codec_data,
                    buffer+samples_written*vgmstream->channels,samples_to_do);
            break;
        case coding_MPEG1_L1:
        case coding_MPEG1_L2:
        case coding_MPEG1_L3:
        case coding_MPEG2_L1:
        case coding_MPEG2_L2:
        case coding_MPEG2_L3:
        case coding_MPEG25_L1:
        case coding_MPEG25_L2:
        case coding_MPEG25_L3:
            decode_mpeg(
                    &vgmstream->ch[0],
                    vgmstream->codec_data,
                    buffer+samples_written*vgmstream->channels,samples_to_do,
                    vgmstream->channels);
            break;
#endif
        case coding_ACM:
            /* handled in its own layout, here to quiet compiler */
            break;
        case coding_NWA0:
        case coding_NWA1:
        case coding_NWA2:
        case coding_NWA3:
        case coding_NWA4:
        case coding_NWA5:
            decode_nwa(((nwa_codec_data*)vgmstream->codec_data)->nwa,
                    buffer+samples_written*vgmstream->channels,
                    samples_to_do
                    );
            break;
        case coding_MSADPCM:
            if (vgmstream->channels == 2) {
                decode_msadpcm_stereo(vgmstream,
                        buffer+samples_written*vgmstream->channels,
                        vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
		case coding_AICA:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_aica(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_NDS_PROCYON:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_nds_procyon(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }
            break;
        case coding_L5_555:
            for (chan=0;chan<vgmstream->channels;chan++) {
                decode_l5_555(&vgmstream->ch[chan],buffer+samples_written*vgmstream->channels+chan,
                        vgmstream->channels,vgmstream->samples_into_block,
                        samples_to_do);
            }

            break;
    }
