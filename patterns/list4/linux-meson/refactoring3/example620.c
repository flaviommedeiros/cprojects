switch (cmd) {

      case UNIFI_GET_UDI_ENABLE:
        unifi_trace(priv, UDBG4, "UniFi Get UDI Enable\n");

        down(&priv->udi_logging_mutex);
        int_param = (priv->logging_client == NULL) ? 0 : 1;
        up(&priv->udi_logging_mutex);

        if (put_user(int_param, (int*)arg))
        {
            unifi_error(priv, "UNIFI_GET_UDI_ENABLE: Failed to copy to user\n");
            r = -EFAULT;
            goto out;
        }
        break;

      case UNIFI_SET_UDI_ENABLE:
        unifi_trace(priv, UDBG4, "UniFi Set UDI Enable\n");
        if (get_user(int_param, (int*)arg))
        {
            unifi_error(priv, "UNIFI_SET_UDI_ENABLE: Failed to copy from user\n");
            r = -EFAULT;
            goto out;
        }

#ifdef CSR_WIFI_HIP_DEBUG_OFFLINE
        if (log_hip_signals) {
            unifi_error(priv, "omnicli cannot be used when log_hip_signals is used\n");
            r = -EFAULT;
            goto out;
        }
#endif

        down(&priv->udi_logging_mutex);
        if (int_param) {
            pcli->event_hook = udi_log_event;
            unifi_set_udi_hook(priv->card, logging_handler);
            /* Log all signals by default */
            for (i = 0; i < SIG_FILTER_SIZE; i++) {
                pcli->signal_filter[i] = 0xFFFF;
            }
            priv->logging_client = pcli;

        } else {
            priv->logging_client = NULL;
            pcli->event_hook = NULL;
        }
        up(&priv->udi_logging_mutex);

        break;

      case UNIFI_SET_MIB:
        unifi_trace(priv, UDBG4, "UniFi Set MIB\n");
#if (defined CSR_SUPPORT_SME) && (defined CSR_SUPPORT_WEXT)
        /* Read first 2 bytes and check length */
        if (copy_from_user((void*)varbind, (void*)arg, 2)) {
            unifi_error(priv,
                        "UNIFI_SET_MIB: Failed to copy in varbind header\n");
            r = -EFAULT;
            goto out;
        }
        vblen = varbind[1];
        if ((vblen + 2) > MAX_VARBIND_LENGTH) {
            unifi_error(priv,
                        "UNIFI_SET_MIB: Varbind too long (%d, limit %d)\n",
                        (vblen+2), MAX_VARBIND_LENGTH);
            r = -EINVAL;
            goto out;
        }
        /* Read rest of varbind */
        if (copy_from_user((void*)(varbind+2), (void*)(arg+2), vblen)) {
            unifi_error(priv, "UNIFI_SET_MIB: Failed to copy in varbind\n");
            r = -EFAULT;
            goto out;
        }

        /* send to SME */
        vblen += 2;
        r = sme_mgt_mib_set(priv, varbind, vblen);
        if (r) {
            goto out;
        }
#else
        unifi_notice(priv, "UNIFI_SET_MIB: Unsupported.\n");
#endif /* CSR_SUPPORT_WEXT */
        break;

      case UNIFI_GET_MIB:
        unifi_trace(priv, UDBG4, "UniFi Get MIB\n");
#if (defined CSR_SUPPORT_SME) && (defined CSR_SUPPORT_WEXT)
        /* Read first 2 bytes and check length */
        if (copy_from_user((void*)varbind, (void*)arg, 2)) {
            unifi_error(priv, "UNIFI_GET_MIB: Failed to copy in varbind header\n");
            r = -EFAULT;
            goto out;
        }
        vblen = varbind[1];
        if ((vblen+2) > MAX_VARBIND_LENGTH) {
            unifi_error(priv, "UNIFI_GET_MIB: Varbind too long (%d, limit %d)\n",
                        (vblen+2), MAX_VARBIND_LENGTH);
            r = -EINVAL;
            goto out;
        }
        /* Read rest of varbind */
        if (copy_from_user((void*)(varbind+2), (void*)(arg+2), vblen)) {
            unifi_error(priv, "UNIFI_GET_MIB: Failed to copy in varbind\n");
            r = -EFAULT;
            goto out;
        }

        vblen += 2;
        r = sme_mgt_mib_get(priv, varbind, &vblen);
        if (r) {
            goto out;
        }
        /* copy out varbind */
        if (vblen > MAX_VARBIND_LENGTH) {
            unifi_error(priv,
                        "UNIFI_GET_MIB: Varbind result too long (%d, limit %d)\n",
                        vblen, MAX_VARBIND_LENGTH);
            r = -EINVAL;
            goto out;
        }
        if (copy_to_user((void*)arg, varbind, vblen)) {
            r = -EFAULT;
            goto out;
        }
#else
        unifi_notice(priv, "UNIFI_GET_MIB: Unsupported.\n");
#endif /* CSR_SUPPORT_WEXT */
        break;

      case UNIFI_CFG:
#if (defined CSR_SUPPORT_SME)
        if (get_user(cfg_cmd, (unifi_cfg_command_t*)arg))
        {
            unifi_error(priv, "UNIFI_CFG: Failed to get the command\n");
            r = -EFAULT;
            goto out;
        }

        unifi_trace(priv, UDBG1, "UNIFI_CFG: Command is %d (t=%u) sz=%d\n",
                    cfg_cmd, jiffies_to_msecs(jiffies), sizeof(unifi_cfg_command_t));
        switch (cfg_cmd) {
          case UNIFI_CFG_POWER:
            r = unifi_cfg_power(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_POWERSAVE:
            r = unifi_cfg_power_save(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_POWERSUPPLY:
            r = unifi_cfg_power_supply(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_FILTER:
            r = unifi_cfg_packet_filters(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_GET:
            r = unifi_cfg_get_info(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_WMM_QOSINFO:
            r = unifi_cfg_wmm_qos_info(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_WMM_ADDTS:
            r = unifi_cfg_wmm_addts(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_WMM_DELTS:
            r = unifi_cfg_wmm_delts(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_STRICT_DRAFT_N:
            r = unifi_cfg_strict_draft_n(priv, (unsigned char*)arg);
            break;
          case UNIFI_CFG_ENABLE_OKC:
            r = unifi_cfg_enable_okc(priv, (unsigned char*)arg);
            break;
#ifdef CSR_SUPPORT_SME
          case UNIFI_CFG_CORE_DUMP:
            CsrWifiRouterCtrlWifiOffIndSend(priv->CSR_WIFI_SME_IFACEQUEUE,0,CSR_WIFI_SME_CONTROL_INDICATION_ERROR);
            unifi_trace(priv, UDBG2, "UNIFI_CFG_CORE_DUMP: sent wifi off indication\n");
            break;
#endif
#ifdef CSR_SUPPORT_WEXT_AP
          case UNIFI_CFG_SET_AP_CONFIG:
            r= unifi_cfg_set_ap_config(priv,(unsigned char*)arg);
            break;
#endif
          default:
            unifi_error(priv, "UNIFI_CFG: Unknown Command (%d)\n", cfg_cmd);
            r = -EINVAL;
            goto out;
        }
#endif

        break;

      case UNIFI_PUTEST:
        if (get_user(putest_cmd, (unifi_putest_command_t*)arg))
        {
            unifi_error(priv, "UNIFI_PUTEST: Failed to get the command\n");
            r = -EFAULT;
            goto out;
        }

        unifi_trace(priv, UDBG1, "UNIFI_PUTEST: Command is %s\n",
                    trace_putest_cmdid(putest_cmd));
        switch (putest_cmd) {
          case UNIFI_PUTEST_START:
            r = unifi_putest_start(priv, (unsigned char*)arg);
            break;
          case UNIFI_PUTEST_STOP:
            r = unifi_putest_stop(priv, (unsigned char*)arg);
            break;
          case UNIFI_PUTEST_SET_SDIO_CLOCK:
            r = unifi_putest_set_sdio_clock(priv, (unsigned char*)arg);
            break;
          case UNIFI_PUTEST_CMD52_READ:
            r = unifi_putest_cmd52_read(priv, (unsigned char*)arg);
            break;
          case UNIFI_PUTEST_CMD52_BLOCK_READ:
            r = unifi_putest_cmd52_block_read(priv, (unsigned char*)arg);
            break;
          case UNIFI_PUTEST_CMD52_WRITE:
            r = unifi_putest_cmd52_write(priv, (unsigned char*)arg);
            break;
          case UNIFI_PUTEST_DL_FW:
            r = unifi_putest_dl_fw(priv, (unsigned char*)arg);
            break;
          case UNIFI_PUTEST_DL_FW_BUFF:
            r = unifi_putest_dl_fw_buff(priv, (unsigned char*)arg);
            break;
          case UNIFI_PUTEST_COREDUMP_PREPARE:
            r = unifi_putest_coredump_prepare(priv, (unsigned char*)arg);
            break;
          case UNIFI_PUTEST_GP_READ16:
            r = unifi_putest_gp_read16(priv, (unsigned char*)arg);
            break;
          case UNIFI_PUTEST_GP_WRITE16:
            r = unifi_putest_gp_write16(priv, (unsigned char*)arg);
            break;
          default:
            unifi_error(priv, "UNIFI_PUTEST: Unknown Command (%d)\n", putest_cmd);
            r = -EINVAL;
            goto out;
        }

        break;
      case UNIFI_BUILD_TYPE:
        unifi_trace(priv, UDBG2, "UNIFI_BUILD_TYPE userspace=%s\n", build_type_to_string(*(unsigned char*)arg));
#ifndef CSR_SUPPORT_WEXT_AP
        if (UNIFI_BUILD_AP == *(unsigned char*)arg)
        {
            unifi_error(priv, "Userspace has AP support, which is incompatible\n");
        }
#endif

#ifndef CSR_SUPPORT_WEXT
        if (UNIFI_BUILD_WEXT == *(unsigned char*)arg)
        {
            unifi_error(priv, "Userspace has WEXT support, which is incompatible\n");
        }
#endif
        break;
      case UNIFI_INIT_HW:
        unifi_trace(priv, UDBG2, "UNIFI_INIT_HW.\n");
        priv->init_progress = UNIFI_INIT_NONE;

#if defined(CSR_SUPPORT_WEXT) || defined (CSR_NATIVE_LINUX)
        /* At this point we are ready to start the SME. */
        r = sme_mgt_wifi_on(priv);
        if (r) {
            goto out;
        }
#endif

        break;

      case UNIFI_INIT_NETDEV:
        {
            /* get the proper interfaceTagId */
            u16 interfaceTag=0;
            netInterface_priv_t *interfacePriv = priv->interfacePriv[interfaceTag];

            dev = priv->netdev[interfaceTag];
            unifi_trace(priv, UDBG2, "UNIFI_INIT_NETDEV.\n");

            if (copy_from_user((void*)dev->dev_addr, (void*)arg, 6)) {
                r = -EFAULT;
                goto out;
            }

            /* Attach the network device to the stack */
            if (!interfacePriv->netdev_registered)
            {
                r = uf_register_netdev(priv,interfaceTag);
                if (r) {
                    unifi_error(priv, "Failed to register the network device.\n");
                    goto out;
                }
            }

            /* Apply scheduled interrupt mode, if requested by module param */
            if (run_bh_once != -1) {
                unifi_set_interrupt_mode(priv->card, (u32)run_bh_once);
            }

            priv->init_progress = UNIFI_INIT_COMPLETED;

            /* Firmware initialisation is complete, so let the SDIO bus
             * clock be raised when convienent to the core.
             */
            unifi_request_max_sdio_clock(priv->card);

#ifdef CSR_SUPPORT_WEXT
            /* Notify the Android wpa_supplicant that we are ready */
            wext_send_started_event(priv);
#endif

            unifi_info(priv, "UniFi ready\n");

#ifdef ANDROID_BUILD
            /* Release the wakelock */
            unifi_trace(priv, UDBG1, "netdev_init: release wake lock\n");
            wake_unlock(&unifi_sdio_wake_lock);
#endif
#ifdef CSR_NATIVE_SOFTMAC /* For softmac dev, force-enable the network interface rather than wait for a connected-ind */
            {
                struct net_device *dev = priv->netdev[interfaceTag];
#ifdef CSR_SUPPORT_WEXT
                interfacePriv->wait_netdev_change = TRUE;
#endif
                netif_carrier_on(dev);
            }
#endif
        }
        break;
      case UNIFI_GET_INIT_STATUS:
        unifi_trace(priv, UDBG2, "UNIFI_GET_INIT_STATUS.\n");
        if (put_user(priv->init_progress, (int*)arg))
        {
            printk(KERN_ERR "UNIFI_GET_INIT_STATUS: Failed to copy to user\n");
            r = -EFAULT;
            goto out;
        }
        break;

      case UNIFI_KICK:
        unifi_trace(priv, UDBG4, "Kick UniFi\n");
        unifi_sdio_interrupt_handler(priv->card);
        break;

      case UNIFI_SET_DEBUG:
        unifi_debug = arg;
        unifi_trace(priv, UDBG4, "unifi_debug set to %d\n", unifi_debug);
        break;

      case UNIFI_SET_TRACE:
        /* no longer supported */
        r = -EINVAL;
        break;


      case UNIFI_SET_UDI_LOG_MASK:
        {
            unifiio_filter_t udi_filter;
            uint16_t *sig_ids_addr;
#define UF_MAX_SIG_IDS  128     /* Impose a sensible limit */

            if (copy_from_user((void*)(&udi_filter), (void*)arg, sizeof(udi_filter))) {
                r = -EFAULT;
                goto out;
            }
            if ((udi_filter.action < UfSigFil_AllOn) ||
                (udi_filter.action > UfSigFil_SelectOff))
            {
                printk(KERN_WARNING
                       "UNIFI_SET_UDI_LOG_MASK: Bad action value: %d\n",
                       udi_filter.action);
                r = -EINVAL;
                goto out;
            }
            /* No signal list for "All" actions */
            if ((udi_filter.action == UfSigFil_AllOn) ||
                (udi_filter.action == UfSigFil_AllOff))
            {
                udi_filter.num_sig_ids = 0;
            }

            if (udi_filter.num_sig_ids > UF_MAX_SIG_IDS) {
                printk(KERN_WARNING
                       "UNIFI_SET_UDI_LOG_MASK: too many signal ids (%d, max %d)\n",
                       udi_filter.num_sig_ids, UF_MAX_SIG_IDS);
                r = -EINVAL;
                goto out;
            }

            /* Copy in signal id list if given */
            if (udi_filter.num_sig_ids > 0) {
                /* Preserve userspace address of sig_ids array */
                sig_ids_addr = udi_filter.sig_ids;
                /* Allocate kernel memory for sig_ids and copy to it */
                udi_filter.sig_ids =
                    kmalloc(udi_filter.num_sig_ids * sizeof(uint16_t), GFP_KERNEL);
                if (!udi_filter.sig_ids) {
                    r = -ENOMEM;
                    goto out;
                }
                if (copy_from_user((void*)udi_filter.sig_ids,
                                   (void*)sig_ids_addr,
                                   udi_filter.num_sig_ids * sizeof(uint16_t)))
                {
                    kfree(udi_filter.sig_ids);
                    r = -EFAULT;
                    goto out;
                }
            }

            udi_set_log_filter(pcli, &udi_filter);

            if (udi_filter.num_sig_ids > 0) {
                kfree(udi_filter.sig_ids);
            }
        }
        break;

      case UNIFI_SET_AMP_ENABLE:
        unifi_trace(priv, UDBG4, "UniFi Set AMP Enable\n");
        if (get_user(int_param, (int*)arg))
        {
            unifi_error(priv, "UNIFI_SET_AMP_ENABLE: Failed to copy from user\n");
            r = -EFAULT;
            goto out;
        }

        if (int_param) {
            priv->amp_client = pcli;
        } else {
            priv->amp_client = NULL;
        }

        int_param = 0;
        buf = (u8*)&int_param;
        buf[0] = UNIFI_SOFT_COMMAND_Q_LENGTH - 1;
        buf[1] = UNIFI_SOFT_TRAFFIC_Q_LENGTH - 1;
        if (copy_to_user((void*)arg, &int_param, sizeof(int))) {
            r = -EFAULT;
            goto out;
        }
        break;

      case UNIFI_SET_UDI_SNAP_MASK:
        {
            unifiio_snap_filter_t snap_filter;

            if (copy_from_user((void*)(&snap_filter), (void*)arg, sizeof(snap_filter))) {
                r = -EFAULT;
                goto out;
            }

            if (pcli->snap_filter.count) {
                pcli->snap_filter.count = 0;
                kfree(pcli->snap_filter.protocols);
            }

            if (snap_filter.count == 0) {
                break;
            }

            pcli->snap_filter.protocols = kmalloc(snap_filter.count * sizeof(u16), GFP_KERNEL);
            if (!pcli->snap_filter.protocols) {
                r = -ENOMEM;
                goto out;
            }
            if (copy_from_user((void*)pcli->snap_filter.protocols,
                               (void*)snap_filter.protocols,
                               snap_filter.count * sizeof(u16)))
            {
                kfree(pcli->snap_filter.protocols);
                r = -EFAULT;
                goto out;
            }

            pcli->snap_filter.count = snap_filter.count;

        }
        break;

      case UNIFI_SME_PRESENT:
        {
            u8 ind;
            unifi_trace(priv, UDBG4, "UniFi SME Present IOCTL.\n");
            if (copy_from_user((void*)(&int_param), (void*)arg, sizeof(int)))
            {
                printk(KERN_ERR "UNIFI_SME_PRESENT: Failed to copy from user\n");
                r = -EFAULT;
                goto out;
            }

            priv->sme_is_present = int_param;
            if (priv->sme_is_present == 1) {
                ind = CONFIG_SME_PRESENT;
            } else {
                ind = CONFIG_SME_NOT_PRESENT;
            }
            /* Send an indication to the helper app. */
            ul_log_config_ind(priv, &ind, sizeof(u8));
        }
        break;

      case UNIFI_CFG_PERIOD_TRAFFIC:
      {
#if (defined CSR_SUPPORT_SME) && (defined CSR_SUPPORT_WEXT)
          CsrWifiSmeCoexConfig coexConfig;
#endif /* CSR_SUPPORT_SME && CSR_SUPPORT_WEXT */
        unifi_trace(priv, UDBG4, "UniFi Configure Periodic Traffic.\n");
#if (defined CSR_SUPPORT_SME) && (defined CSR_SUPPORT_WEXT)
        if (copy_from_user((void*)(&uchar_param), (void*)arg, sizeof(unsigned char))) {
            unifi_error(priv, "UNIFI_CFG_PERIOD_TRAFFIC: Failed to copy from user\n");
            r = -EFAULT;
            goto out;
        }

        if (uchar_param == 0) {
            r = sme_mgt_coex_config_get(priv, &coexConfig);
            if (r) {
                unifi_error(priv, "UNIFI_CFG_PERIOD_TRAFFIC: Get unifi_CoexInfoValue failed.\n");
                goto out;
            }
            if (copy_to_user((void*)(arg + 1),
                             (void*)&coexConfig,
                             sizeof(CsrWifiSmeCoexConfig))) {
                r = -EFAULT;
                goto out;
            }
            goto out;
        }

        if (copy_from_user((void*)(&coex_config), (void*)(arg + 1), sizeof(CsrWifiSmeCoexConfig)))
        {
            unifi_error(priv, "UNIFI_CFG_PERIOD_TRAFFIC: Failed to copy from user\n");
            r = -EFAULT;
            goto out;
        }

        coexConfig = coex_config;
        r = sme_mgt_coex_config_set(priv, &coexConfig);
        if (r) {
            unifi_error(priv, "UNIFI_CFG_PERIOD_TRAFFIC: Set unifi_CoexInfoValue failed.\n");
            goto out;
        }

#endif /* CSR_SUPPORT_SME && CSR_SUPPORT_WEXT */
        break;
      }
      case UNIFI_CFG_UAPSD_TRAFFIC:
        unifi_trace(priv, UDBG4, "UniFi Configure U-APSD Mask.\n");
#if (defined CSR_SUPPORT_SME) && (defined CSR_SUPPORT_WEXT)
        if (copy_from_user((void*)(&uchar_param), (void*)arg, sizeof(unsigned char))) {
            unifi_error(priv, "UNIFI_CFG_UAPSD_TRAFFIC: Failed to copy from user\n");
            r = -EFAULT;
            goto out;
        }
        unifi_trace(priv, UDBG4, "New U-APSD Mask: 0x%x\n", uchar_param);
#endif /* CSR_SUPPORT_SME && CSR_SUPPORT_WEXT */
        break;

#ifndef UNIFI_DISABLE_COREDUMP
      case UNIFI_COREDUMP_GET_REG:
        unifi_trace(priv, UDBG4, "Mini-coredump data request\n");
        {
            unifiio_coredump_req_t dump_req;    /* Public OS layer structure */
            unifi_coredump_req_t priv_req;      /* Private HIP structure */

            if (copy_from_user((void*)(&dump_req), (void*)arg, sizeof(dump_req))) {
                r = -EFAULT;
                goto out;
            }
            memset(&priv_req, 0, sizeof(priv_req));
            priv_req.index = dump_req.index;
            priv_req.offset = dump_req.offset;

            /* Convert OS-layer's XAP memory space ID to HIP's ID in case they differ */
            switch (dump_req.space) {
                case UNIFIIO_COREDUMP_MAC_REG: priv_req.space = UNIFI_COREDUMP_MAC_REG; break;
                case UNIFIIO_COREDUMP_PHY_REG: priv_req.space = UNIFI_COREDUMP_PHY_REG; break;
                case UNIFIIO_COREDUMP_SH_DMEM: priv_req.space = UNIFI_COREDUMP_SH_DMEM; break;
                case UNIFIIO_COREDUMP_MAC_DMEM: priv_req.space = UNIFI_COREDUMP_MAC_DMEM; break;
                case UNIFIIO_COREDUMP_PHY_DMEM: priv_req.space = UNIFI_COREDUMP_PHY_DMEM; break;
                case UNIFIIO_COREDUMP_TRIGGER_MAGIC: priv_req.space = UNIFI_COREDUMP_TRIGGER_MAGIC; break;
                default:
                  r = -EINVAL;
                  goto out;
            }

            if (priv_req.space == UNIFI_COREDUMP_TRIGGER_MAGIC) {
                /* Force a coredump grab now */
                unifi_trace(priv, UDBG2, "UNIFI_COREDUMP_GET_REG: Force capture\n");
                csrResult = unifi_coredump_capture(priv->card, &priv_req);
                r = CsrHipResultToStatus(csrResult);
                unifi_trace(priv, UDBG5, "UNIFI_COREDUMP_GET_REG: status %d\n", r);
            } else {
                /* Retrieve the appropriate register entry */
                csrResult = unifi_coredump_get_value(priv->card, &priv_req);
                r = CsrHipResultToStatus(csrResult);
                if (r) {
                    unifi_trace(priv, UDBG5, "UNIFI_COREDUMP_GET_REG: Status %d\n", r);
                    goto out;
                }
                /* Update the OS-layer structure with values returned in the private */
                dump_req.value = priv_req.value;
                dump_req.timestamp = priv_req.timestamp;
                dump_req.requestor = priv_req.requestor;
                dump_req.serial = priv_req.serial;
                dump_req.chip_ver = priv_req.chip_ver;
                dump_req.fw_ver = priv_req.fw_ver;
                dump_req.drv_build = 0;

                unifi_trace(priv, UDBG6,
                            "Dump: %d (seq %d): V:0x%04x (%d) @0x%02x:%04x = 0x%04x\n",
                            dump_req.index, dump_req.serial,
                            dump_req.chip_ver, dump_req.drv_build,
                            dump_req.space, dump_req.offset, dump_req.value);
            }
            if (copy_to_user((void*)arg, (void*)&dump_req, sizeof(dump_req))) {
                r = -EFAULT;
                goto out;
            }
        }
        break;
#endif
      default:
        r = -EINVAL;
    }
