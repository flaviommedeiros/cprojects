if (VOS_STATUS_SUCCESS != vos_mq_post_message(
#ifndef FEATURE_WLAN_INTEGRATED_SOC
        VOS_MODULE_ID_HAL,
#else
        VOS_MODULE_ID_WDA,
#endif
                                    (vos_msg_t *)&ftmMsg)) {
        hddLog(VOS_TRACE_LEVEL_ERROR,"%s: : Failed to post Msg to HAL\n",__func__);

        return VOS_STATUS_E_FAILURE;
    }
