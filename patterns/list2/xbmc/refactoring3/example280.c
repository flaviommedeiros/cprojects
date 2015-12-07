switch (coding) {
                case coding_PSX:
                case coding_PSX_badflags:
                case coding_PCM16BE:
                case coding_PCM16LE:
                case coding_SDX2:
                case coding_SDX2_int:
                case coding_DVI_IMA:
                case coding_IMA:
                case coding_PCM8:
                case coding_PCM8_U_int:
                case coding_AICA:
                case coding_INT_DVI_IMA:
                case coding_INT_IMA:
                    if (vgmstream->layout_type == layout_interleave) {
                        if (interleave >= 512) {
                            chstreamfile =
                                streamFile->open(streamFile,filename,interleave);
                        } else {
                            if (!chstreamfile)
                                chstreamfile =
                                    streamFile->open(streamFile,filename,STREAMFILE_DEFAULT_BUFFER_SIZE);
                        }
                        chstart_offset =
                            start_offset+vgmstream->interleave_block_size*i;
                    } else {
                        chstreamfile =
                            streamFile->open(streamFile,filename,
                                    STREAMFILE_DEFAULT_BUFFER_SIZE);
                    }
                    break;
                case coding_XBOX:
                case coding_MSADPCM:
                    /* xbox's "interleave" is a lie, all channels start at same
                     * offset */
                    chstreamfile =
                        streamFile->open(streamFile,filename,
                                STREAMFILE_DEFAULT_BUFFER_SIZE);
                    break;
                case coding_NGC_DTK:
                    if (!chstreamfile) 
                        chstreamfile =
                            streamFile->open(streamFile,filename,32*0x400);
                    break;
                case coding_NGC_DSP:
                    if (!chstreamfile) 
                        chstreamfile =
                            streamFile->open(streamFile,filename,STREAMFILE_DEFAULT_BUFFER_SIZE);

                    if (coef_type == 0) {
                        for (j=0;j<16;j++) {
                            vgmstream->ch[i].adpcm_coef[j] = read_16bitBE(coef[i]+j*2,streamFile);
                        }
                    } else if (coef_type == 1) {
                        for (j=0;j<8;j++) {
                            vgmstream->ch[i].adpcm_coef[j*2]=read_16bitBE(coef[i]+j*2,streamFile);
                            vgmstream->ch[i].adpcm_coef[j*2+1]=read_16bitBE(coef_splitted[i]+j*2,streamFile);
                        }
                    }
                    chstart_offset =start_offset+vgmstream->interleave_block_size*i;
                    break;

#ifdef VGM_USE_MPEG
                case coding_MPEG1_L3:
                    if (!chstreamfile)
                        chstreamfile =
                            streamFile->open(streamFile,filename,MPEG_BUFFER_SIZE);
                    break;
#endif
            }
