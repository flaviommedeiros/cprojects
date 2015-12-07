switch (coding) {
        case coding_PCM8_U_int:
            vgmstream->layout_type=layout_none;
            break;
        case coding_PCM16LE:
        case coding_PCM16BE:
        case coding_PCM8:
        case coding_SDX2:
        case coding_PSX:
        case coding_PSX_badflags:
        case coding_DVI_IMA:
        case coding_IMA:
        case coding_AICA:
            vgmstream->interleave_block_size = interleave;
            if (channel_count > 1)
            {
                if (coding == coding_SDX2) {
                    coding = coding_SDX2_int;
                    vgmstream->coding_type = coding_SDX2_int;
                }
                if(vgmstream->interleave_block_size==0xffffffff)
                    vgmstream->layout_type=layout_none;
                else {
                    vgmstream->layout_type = layout_interleave;
                    if(coding==coding_DVI_IMA)
                        coding=coding_INT_DVI_IMA;
                    if(coding==coding_IMA)
                        coding=coding_INT_IMA;
                }
            } else {
                vgmstream->layout_type = layout_none;
            }
            break;
        case coding_MSADPCM:
            if (channel_count != 2) goto fail;
            vgmstream->interleave_block_size = interleave;
            vgmstream->layout_type = layout_none;
            break;
        case coding_XBOX:
            vgmstream->layout_type = layout_none;
            break;
        case coding_NGC_DTK:
            vgmstream->layout_type = layout_dtk_interleave;
            break;
        case coding_NGC_DSP:
            if (dsp_interleave_type == 0) {
                vgmstream->layout_type = layout_interleave;
                vgmstream->interleave_block_size = interleave;
            } else if (dsp_interleave_type == 1) {
                vgmstream->layout_type = layout_interleave_byte;
                vgmstream->interleave_block_size = interleave;
            } else if (dsp_interleave_type == 2) {
                vgmstream->layout_type = layout_none;
            }
            break;
            
#ifdef VGM_USE_MPEG
        case coding_MPEG1_L3:
            vgmstream->layout_type = layout_mpeg;
            break;
#endif
    }
