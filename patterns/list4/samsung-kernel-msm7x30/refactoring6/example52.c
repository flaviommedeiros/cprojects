if((pSession->handoffRequested)
#ifdef WLAN_FEATURE_VOWIFI_11R
/* In case of 11r - RIC, we request QoS and Hand-off at the same time hence the
   state may be SME_QOS_REQUESTED */
      && !pSession->ftHandoffInProgress
#endif
      )
   {
      VOS_TRACE(VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO_HIGH, 
                "%s: %d: no need for state transition, should "
                "already be in handoff state",
                __FUNCTION__, __LINE__);
      VOS_ASSERT(pSession->ac_info[0].curr_state == SME_QOS_HANDOFF);
      VOS_ASSERT(pSession->ac_info[1].curr_state == SME_QOS_HANDOFF);
      VOS_ASSERT(pSession->ac_info[2].curr_state == SME_QOS_HANDOFF);
      VOS_ASSERT(pSession->ac_info[3].curr_state == SME_QOS_HANDOFF);
      return eHAL_STATUS_SUCCESS;
   }
