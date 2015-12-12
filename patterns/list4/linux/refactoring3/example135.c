switch (ev_code) {
		case FSE_AZ_EV_CODE_RX_EV:
			efx_farch_handle_rx_event(channel, &event);
			if (++spent == budget)
				goto out;
			break;
		case FSE_AZ_EV_CODE_TX_EV:
			tx_packets += efx_farch_handle_tx_event(channel,
								&event);
			if (tx_packets > efx->txq_entries) {
				spent = budget;
				goto out;
			}
			break;
		case FSE_AZ_EV_CODE_DRV_GEN_EV:
			efx_farch_handle_generated_event(channel, &event);
			break;
		case FSE_AZ_EV_CODE_DRIVER_EV:
			efx_farch_handle_driver_event(channel, &event);
			break;
#ifdef CONFIG_SFC_SRIOV
		case FSE_CZ_EV_CODE_USER_EV:
			efx_siena_sriov_event(channel, &event);
			break;
#endif
		case FSE_CZ_EV_CODE_MCDI_EV:
			efx_mcdi_process_event(channel, &event);
			break;
		case FSE_AZ_EV_CODE_GLOBAL_EV:
			if (efx->type->handle_global_event &&
			    efx->type->handle_global_event(channel, &event))
				break;
			/* else fall through */
		default:
			netif_err(channel->efx, hw, channel->efx->net_dev,
				  "channel %d unknown event type %d (data "
				  EFX_QWORD_FMT ")\n", channel->channel,
				  ev_code, EFX_QWORD_VAL(event));
		}
