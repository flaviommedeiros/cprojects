if ((proto == ETH_P_PAE)
#ifdef CSR_WIFI_SECURITY_WAPI_ENABLE
            || (proto == ETH_P_WAI)
#endif
       )
    {
        CSR_SIGNAL signal;
        CSR_MA_PACKET_REQUEST *req = &signal.u.MaPacketRequest;

        /* initialize signal to zero */
        memset(&signal, 0, sizeof(CSR_SIGNAL));

        /* Frame MA_PACKET request */
        signal.SignalPrimitiveHeader.SignalId = CSR_MA_PACKET_REQUEST_ID;
        signal.SignalPrimitiveHeader.ReceiverProcessId = 0;
        signal.SignalPrimitiveHeader.SenderProcessId = priv->netdev_client->sender_id;

        transmissionControl = req->TransmissionControl = 0;
#ifdef CSR_SUPPORT_SME
        if (eapolStore)
        {
            netInterface_priv_t *netpriv = (netInterface_priv_t *)netdev_priv(priv->netdev[interfaceTag]);

            /* Fill the MA-PACKET.req */

            req->Priority = priority;
            unifi_trace(priv, UDBG3, "Tx Frame with Priority: %x\n", req->Priority);

            /* rate selected by firmware */
            req->TransmitRate = 0;
            req->HostTag = CSR_WIFI_EAPOL_M4_HOST_TAG;
            /* RA address matching with address 1 of Mac header */
            memcpy(req->Ra.x, ((u8 *) bulkdata.d[0].os_data_ptr) + 4, ETH_ALEN);

            spin_lock(&priv->m4_lock);
            /* Store the M4-PACKET.req for later */
            interfacePriv->m4_signal = signal;
            interfacePriv->m4_bulk_data.net_buf_length = bulkdata.d[0].net_buf_length;
            interfacePriv->m4_bulk_data.data_length = bulkdata.d[0].data_length;
            interfacePriv->m4_bulk_data.os_data_ptr = bulkdata.d[0].os_data_ptr;
            interfacePriv->m4_bulk_data.os_net_buf_ptr = bulkdata.d[0].os_net_buf_ptr;
            spin_unlock(&priv->m4_lock);

            /* Signal the workqueue to call CsrWifiRouterCtrlM4ReadyToSendIndSend().
             * It cannot be called directly from the tx path because it
             * does a non-atomic kmalloc via the framework's CsrPmemAlloc().
             */
            queue_work(priv->unifi_workqueue, &netpriv->send_m4_ready_task);

            return 0;
        }
#endif
    }
