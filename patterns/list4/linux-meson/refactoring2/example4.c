#if(PEBBLES_ES1_ZONE_WORKAROUND == ENABLE)
if((RegisterRead(REG__STATE)& BIT__SCDT)            //check sync status
            &&ConfigureZone())
#endif
        {
#if (CONF__ODCK_LIMITED==ENABLE)
     RegisterModify(REG__SYS_PSTOP,BIT__PSTOP_EN, SET);      //enable PSTOP feature
     RegisterModify(REG__DRIVE_CNTL, MSK__ODCK_STRENGTH,SET);    //clear the ODCK first
#endif// #if (CONF__ODCK_LIMITED==ENABLE)

            RegisterModify(REG__HDMI_MUTE, BIT__VIDM, CLEAR);
            CurrentStatus.VideoState = STATE_VIDEO__ON;
            DEBUG_PRINT(("Video on\n"));
#if (PEBBLES_VIDEO_STATUS_2ND_CHECK==ENABLE)
            TIMER_Set(TIMER__VIDEO, VIDEO_STABLITY_CHECK_INTERVAL);  // start the video timer
            CurrentStatus.VideoStabilityCheckCount = 0;
#endif//#if (PEBBLES_VIDEO_STATUS_2ND_CHECK==ENABLE)

        }
