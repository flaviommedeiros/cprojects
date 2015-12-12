static struct rte_eth_conf ethdev_conf = {
    .link_speed = 0,    /* ETH_LINK_SPEED_10[0|00|000], or 0 for autonegotation */
    .link_duplex = 0,   /* ETH_LINK_[HALF_DUPLEX|FULL_DUPLEX], or 0 for autonegotation */
    .rxmode = { /* Port RX configuration. */
        /* The multi-queue packet distribution mode to be used, e.g. RSS. */
        .mq_mode            = ETH_MQ_RX_RSS,
        .max_rx_pkt_len     = ETHER_MAX_LEN, /* Only used if jumbo_frame enabled */
        .header_split       = 0, /* Disable Header Split */
        .hw_ip_checksum     = 1, /* Enable IP/UDP/TCP checksum offload */
        .hw_vlan_filter     = 0, /* Disabel VLAN filter */
        .hw_vlan_strip      = 0, /* Disable VLAN strip (might be enabled with --vlan argument) */
        .hw_vlan_extend     = 0, /* Disable Extended VLAN */
        .jumbo_frame        = 0, /* Disable Jumbo Frame Receipt */
        .hw_strip_crc       = 0, /* Disable CRC stripping by hardware */
        .enable_scatter     = 0, /* Disable scatter packets rx handler */
    },
    .rx_adv_conf = {
        .rss_conf = { /* Port RSS configuration */
            .rss_key            = NULL, /* If not NULL, 40-byte hash key */
            .rss_key_len        = 0,    /* Hash key length in bytes */
            /* Hash functions to apply */
            .rss_hf             = ETH_RSS_IP | ETH_RSS_UDP | ETH_RSS_TCP,
        },
    },
    .txmode = { /* Port TX configuration. */
        .mq_mode            = ETH_MQ_TX_NONE, /* TX multi-queues mode */
        /* For i40e specifically */
        .pvid               = 0,
        .hw_vlan_reject_tagged      = 0, /* If set, reject sending out tagged pkts */
        .hw_vlan_reject_untagged    = 0, /* If set, reject sending out untagged pkts */
        .hw_vlan_insert_pvid        = 0, /* If set, enable port based VLAN insertion */
    },
    .fdir_conf = {
#if VR_DPDK_USE_HW_FILTERING
        .mode = RTE_FDIR_MODE_PERFECT,          /* Flow Director mode. */
        .status = RTE_FDIR_REPORT_STATUS,       /* How to report FDIR hash. */
#else
        .mode = RTE_FDIR_MODE_NONE,
        .status = RTE_FDIR_NO_REPORT_STATUS,
#endif
        .pballoc = RTE_FDIR_PBALLOC_64K,        /* Space for FDIR filters. */
        /* Offset of flexbytes field in RX packets (in 16-bit word units). */
        /* TODO: flow director API has changed since DPDK 1.7 */
//        .flexbytes_offset = VR_DPDK_MPLS_OFFSET,
        /* RX queue of packets matching a "drop" filter in perfect mode. */
        .drop_queue = 0,
        .flex_conf = {
        },
    },
};
