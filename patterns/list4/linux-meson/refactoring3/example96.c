switch(VState)
    {
    case VSTATE_PwrOff:
        AcceptCDRReset = TRUE ;
        #ifdef AUTO_SEARCH_EQ_SETTING
        SyncDetectFailCounter = 0;
        SyncWaitCounter = 0;
        SyncCheckCounter = 0;
        #endif

        break ;
    case VSTATE_SWReset:
        // HDMIRX_WriteI2C_Byte(REG_RX_GEN_PKT_TYPE, 0x03); // set default general control packet received in 0xA8
        AssignVideoTimerTimeout(VSTATE_SWRESET_COUNT);
    	break ;
    case VSTATE_SyncWait:
        #ifdef AUTO_SEARCH_EQ_SETTING
        SyncWaitCounter++;
        #endif
        HDMIRX_WriteI2C_Byte(REG_RX_REGPKTFLAG_CTRL,0);
        SetIntMask1(~(B_SCDTOFF|B_VIDMODE_CHG),0);
        if(ucRevision >= 0xA3)
        {
            uc = HDMIRX_ReadI2C_Byte(0x3C);
            uc &= ~(1<<2);
            HDMIRX_WriteI2C_Byte(0x3C, uc);
        }
		bVSIpresent=FALSE ;
        SetVideoMute(ON);
        AssignVideoTimerTimeout(VSTATE_MISS_SYNC_COUNT);
        break ;
    #ifndef DISABLE_COLOR_DEPTH_RESET
    case VSTATE_ColorDetectReset:

        uc = HDMIRX_ReadI2C_Byte(REG_RX_INTERRUPT_MASK1) &(~B_SCDTOFF) ;
        HDMIRX_WriteI2C_Byte(REG_RX_INTERRUPT_MASK1, uc) ;
        ClearIntFlags(B_CLR_MODE_INT);
        uc = HDMIRX_ReadI2C_Byte(REG_RX_CDEPTH_CTRL) & (~B_RSTCD);
        HDMIRX_WriteI2C_Byte(REG_RX_CDEPTH_CTRL,B_RSTCD|uc) ;
        HDMIRX_WriteI2C_Byte(REG_RX_CDEPTH_CTRL,uc) ;
        AssignVideoTimerTimeout(MS_TimeOut(400));
        break ;
    #endif

    case VSTATE_SyncChecking:
        #ifdef AUTO_SEARCH_EQ_SETTING
        SyncCheckCounter++;
        #endif
        HDMIRX_WriteI2C_Byte(REG_RX_GEN_PKT_TYPE, 0x81); // set default general control packet received in 0xA8
        HDMIRX_WriteI2C_Byte(REG_RX_REGPKTFLAG_CTRL, B_INT_GENERAL_EVERY) ;
        AssignVideoTimerTimeout(VSATE_CONFIRM_SCDT_COUNT);
        HDMIRX_ReadI2C_Byte(REG_RX_CHANNEL_ERR) ; // read 0x85 for clear CDR counter in reg9A.
        HDMIRX_DEBUG_PRINTF(("switch VSTATE_SyncChecking, reg9A = %02X\n",(int)HDMIRX_ReadI2C_Byte(0x9A))) ;
        break ;
	case VSTATE_HDCP_Reset:
        SetVideoMute(ON);
		AssignVideoTimerTimeout(HDCP_WAITING_TIMEOUT);
		break ;
    case VSTATE_VideoOn:

        #ifdef AUTO_SEARCH_EQ_SETTING
        VideoOnTick = 0;
        EccErrorCounter = 0;
        #endif

        SetIntMask1(~(B_SCDTOFF|B_VIDMODE_CHG),(B_SCDTOFF|B_VIDMODE_CHG));
        AssignVideoTimerTimeout(5);
        // AcceptCDRReset = TRUE ;

        AssignVideoTimerTimeout(CDRRESET_TIMEOUT);
        if(!NewAVIInfoFrameF)
        {
            SetVideoInputFormatWithoutInfoFrame(F_MODE_RGB24);
            SetColorimetryByMode(/*&SyncInfo*/);
            SetColorSpaceConvert();
        }

        if(!IsHDMIRXHDMIMode())
        {
            SetIntMask1(~(B_SCDTOFF|B_PWR5VOFF),(B_SCDTOFF|B_PWR5VOFF));
            SetVideoMute(OFF); // turned on Video.
            SwitchAudioState(ASTATE_AudioOff);
            NewAVIInfoFrameF = FALSE ;
        }
        else
        {

            if(NewAVIInfoFrameF)
            {
                SetNewInfoVideoOutput();
            }

        #ifdef SUPPORT_REPEATER
            if(bHDCPMode & HDCP_REPEATER)
            {
                SetIntMask3(0,B_ECCERR|B_R_AUTH_DONE|B_R_AUTH_START);
        	}
        	else
        #endif // SUPPORT_REPEATER
        	{
                SetIntMask3(~(B_R_AUTH_DONE|B_R_AUTH_START),B_ECCERR);
        	}
            SetIntMask2(~(B_NEW_AVI_PKG|B_PKT_SET_MUTE|B_PKT_CLR_MUTE),(B_NEW_AVI_PKG|B_PKT_SET_MUTE|B_PKT_CLR_MUTE));
            SetIntMask1(~(B_SCDTOFF|B_PWR5VOFF),(B_SCDTOFF|B_PWR5VOFF));
            SetIntMask4(0,B_M_RXCKON_DET);

            MuteByPKG =(HDMIRX_ReadI2C_Byte(REG_RX_VID_INPUT_ST)& B_AVMUTE)?TRUE:FALSE ;
            bIgnoreVideoChgEvent = MuteByPKG ;

            SetVideoMute(MuteByPKG); // turned on Video.
            ucHDMIAudioErrorCount = 0 ;
            // 2009/02/10 added by Jau-Chih.Tseng@ite.com.tw
            ucAudioSampleClock=DEFAULT_START_FIXED_AUD_SAMPLEFREQ ;
            // ucAudioSampleClock=3 ;
            //~Jau-Chih.Tseng@ite.com.tw 2009/02/10
            uc = HDMIRX_ReadI2C_Byte(REG_RX_AUDIO_CTRL);
            uc &= ~B_FORCE_FS ;
            HDMIRX_WriteI2C_Byte(REG_RX_AUDIO_CTRL, uc);

            uc = HDMIRX_ReadI2C_Byte(REG_RX_MCLK_CTRL)&(~B_CTSINI_EN);
            HDMIRX_WriteI2C_Byte(REG_RX_MCLK_CTRL, uc);

            HDMIRX_DEBUG_PRINTF2(("[%s:%d] reg%02X = %02X\n",__FILE__,__LINE__,(int)REG_RX_AUDIO_CTRL,(int)uc));

			#ifndef DISABLE_AUDIO_SUPPORT
				EnableAudio();
			#else
            	SwitchAudioState(ASTATE_AudioOff);
			#endif
        }

		currHTotal = s_CurrentVM.HTotal ;
		currXcnt = s_CurrentVM.xCnt ;
		currScanMode = s_CurrentVM.ScanMode ;

        break ;
    }
