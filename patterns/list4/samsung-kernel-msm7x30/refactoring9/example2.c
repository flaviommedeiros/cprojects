eHalStatus p2pRemainOnChannel(tHalHandle hHal, tANI_U8 sessionId,
         tANI_U8 channel, tANI_U32 duration,
        remainOnChanCallback callback, 
        void *pContext
#ifdef WLAN_FEATURE_P2P_INTERNAL
        , eP2PRemainOnChnReason reason
#endif
        )
{
    eHalStatus status = eHAL_STATUS_SUCCESS;
    tpAniSirGlobal pMac = PMAC_STRUCT(hHal);
    tSmeCmd *pRemainChlCmd = NULL;
    tANI_U32 phyMode;
  
    pRemainChlCmd = smeGetCommandBuffer(pMac);
    if(pRemainChlCmd == NULL)
        return eHAL_STATUS_FAILURE;
  
    if (SIR_BAND_5_GHZ == GetRFBand(channel))
    {
       phyMode = WNI_CFG_PHY_MODE_11A;
    }
    else
    {
       phyMode = WNI_CFG_PHY_MODE_11G;
    }
    
    cfgSetInt(pMac, WNI_CFG_PHY_MODE, phyMode);

    do
    {
        /* call set in context */
        pRemainChlCmd->command = eSmeCommandRemainOnChannel;
        pRemainChlCmd->sessionId = sessionId;
        pRemainChlCmd->u.remainChlCmd.chn = channel;
        pRemainChlCmd->u.remainChlCmd.duration = duration;
        pRemainChlCmd->u.remainChlCmd.callback = callback;
        pRemainChlCmd->u.remainChlCmd.callbackCtx = pContext;
    
        //Put it at the head of the Q if we just finish finding the peer and ready to send a frame
#ifdef WLAN_FEATURE_P2P_INTERNAL
        smePushCommand(pMac, pRemainChlCmd, (eP2PRemainOnChnReasonSendFrame == reason));
#else
        csrQueueSmeCommand(pMac, pRemainChlCmd, eANI_BOOLEAN_FALSE);
#endif
    } while(0);
  
    smsLog(pMac, LOGW, "exiting function %s\n", __FUNCTION__);
  
    return(status);
}
