#ifndef DISABLE_AUDIO_SUPPORT
if(IsHDMIRXHDMIMode())
    {
        if(pbAudioSampleFreq)
        {
            *pbAudioSampleFreq = HDMIRX_ReadI2C_Byte(REG_RX_FS)& M_Fs ;
        }

        if(pbValidCh)
        {
            *pbValidCh = HDMIRX_ReadI2C_Byte(REG_RX_AUDIO_CH_STAT);
            if(*pbValidCh & B_AUDIO_LAYOUT)
            {
                *pbValidCh &= M_AUDIO_CH ;
            }
            else
            {
                *pbValidCh = B_AUDIO_SRC_VALID_0 ;
            }
        }
        return TRUE ;
    }
    else
#endif
    {
        return FALSE ;
    }
