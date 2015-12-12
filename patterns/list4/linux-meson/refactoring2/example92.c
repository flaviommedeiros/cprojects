#ifdef CSR_SUPPORT_WEXT
if (!interfacePriv->wait_netdev_change)
#endif
    {
#ifdef CONFIG_NET_SCHED
        if (netif_running(priv->netdev[interfaceTag])) {
            netif_tx_schedule_all(priv->netdev[interfaceTag]);
        }
#endif
        uf_process_rx_pending_queue(priv, queue, peer_address, 1,interfaceTag);
    }
