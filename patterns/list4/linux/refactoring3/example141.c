switch (vsi->type) {
	case I40E_VSI_MAIN:
		/* The PF's main VSI is already setup as part of the
		 * device initialization, so we'll not bother with
		 * the add_vsi call, but we will retrieve the current
		 * VSI context.
		 */
		ctxt.seid = pf->main_vsi_seid;
		ctxt.pf_num = pf->hw.pf_id;
		ctxt.vf_num = 0;
		ret = i40e_aq_get_vsi_params(&pf->hw, &ctxt, NULL);
		ctxt.flags = I40E_AQ_VSI_TYPE_PF;
		if (ret) {
			dev_info(&pf->pdev->dev,
				 "couldn't get PF vsi config, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, ret),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
			return -ENOENT;
		}
		vsi->info = ctxt.info;
		vsi->info.valid_sections = 0;

		vsi->seid = ctxt.seid;
		vsi->id = ctxt.vsi_number;

		enabled_tc = i40e_pf_get_tc_map(pf);

		/* MFP mode setup queue map and update VSI */
		if ((pf->flags & I40E_FLAG_MFP_ENABLED) &&
		    !(pf->hw.func_caps.iscsi)) { /* NIC type PF */
			memset(&ctxt, 0, sizeof(ctxt));
			ctxt.seid = pf->main_vsi_seid;
			ctxt.pf_num = pf->hw.pf_id;
			ctxt.vf_num = 0;
			i40e_vsi_setup_queue_map(vsi, &ctxt, enabled_tc, false);
			ret = i40e_aq_update_vsi_params(hw, &ctxt, NULL);
			if (ret) {
				dev_info(&pf->pdev->dev,
					 "update vsi failed, err %s aq_err %s\n",
					 i40e_stat_str(&pf->hw, ret),
					 i40e_aq_str(&pf->hw,
						    pf->hw.aq.asq_last_status));
				ret = -ENOENT;
				goto err;
			}
			/* update the local VSI info queue map */
			i40e_vsi_update_queue_map(vsi, &ctxt);
			vsi->info.valid_sections = 0;
		} else {
			/* Default/Main VSI is only enabled for TC0
			 * reconfigure it to enable all TCs that are
			 * available on the port in SFP mode.
			 * For MFP case the iSCSI PF would use this
			 * flow to enable LAN+iSCSI TC.
			 */
			ret = i40e_vsi_config_tc(vsi, enabled_tc);
			if (ret) {
				dev_info(&pf->pdev->dev,
					 "failed to configure TCs for main VSI tc_map 0x%08x, err %s aq_err %s\n",
					 enabled_tc,
					 i40e_stat_str(&pf->hw, ret),
					 i40e_aq_str(&pf->hw,
						    pf->hw.aq.asq_last_status));
				ret = -ENOENT;
			}
		}
		break;

	case I40E_VSI_FDIR:
		ctxt.pf_num = hw->pf_id;
		ctxt.vf_num = 0;
		ctxt.uplink_seid = vsi->uplink_seid;
		ctxt.connection_type = I40E_AQ_VSI_CONN_TYPE_NORMAL;
		ctxt.flags = I40E_AQ_VSI_TYPE_PF;
		if ((pf->flags & I40E_FLAG_VEB_MODE_ENABLED) &&
		    (i40e_is_vsi_uplink_mode_veb(vsi))) {
			ctxt.info.valid_sections |=
			     cpu_to_le16(I40E_AQ_VSI_PROP_SWITCH_VALID);
			ctxt.info.switch_id =
			   cpu_to_le16(I40E_AQ_VSI_SW_ID_FLAG_ALLOW_LB);
		}
		i40e_vsi_setup_queue_map(vsi, &ctxt, enabled_tc, true);
		break;

	case I40E_VSI_VMDQ2:
		ctxt.pf_num = hw->pf_id;
		ctxt.vf_num = 0;
		ctxt.uplink_seid = vsi->uplink_seid;
		ctxt.connection_type = I40E_AQ_VSI_CONN_TYPE_NORMAL;
		ctxt.flags = I40E_AQ_VSI_TYPE_VMDQ2;

		/* This VSI is connected to VEB so the switch_id
		 * should be set to zero by default.
		 */
		if (i40e_is_vsi_uplink_mode_veb(vsi)) {
			ctxt.info.valid_sections |=
				cpu_to_le16(I40E_AQ_VSI_PROP_SWITCH_VALID);
			ctxt.info.switch_id =
				cpu_to_le16(I40E_AQ_VSI_SW_ID_FLAG_ALLOW_LB);
		}

		/* Setup the VSI tx/rx queue map for TC0 only for now */
		i40e_vsi_setup_queue_map(vsi, &ctxt, enabled_tc, true);
		break;

	case I40E_VSI_SRIOV:
		ctxt.pf_num = hw->pf_id;
		ctxt.vf_num = vsi->vf_id + hw->func_caps.vf_base_id;
		ctxt.uplink_seid = vsi->uplink_seid;
		ctxt.connection_type = I40E_AQ_VSI_CONN_TYPE_NORMAL;
		ctxt.flags = I40E_AQ_VSI_TYPE_VF;

		/* This VSI is connected to VEB so the switch_id
		 * should be set to zero by default.
		 */
		if (i40e_is_vsi_uplink_mode_veb(vsi)) {
			ctxt.info.valid_sections |=
				cpu_to_le16(I40E_AQ_VSI_PROP_SWITCH_VALID);
			ctxt.info.switch_id =
				cpu_to_le16(I40E_AQ_VSI_SW_ID_FLAG_ALLOW_LB);
		}

		ctxt.info.valid_sections |= cpu_to_le16(I40E_AQ_VSI_PROP_VLAN_VALID);
		ctxt.info.port_vlan_flags |= I40E_AQ_VSI_PVLAN_MODE_ALL;
		if (pf->vf[vsi->vf_id].spoofchk) {
			ctxt.info.valid_sections |=
				cpu_to_le16(I40E_AQ_VSI_PROP_SECURITY_VALID);
			ctxt.info.sec_flags |=
				(I40E_AQ_VSI_SEC_FLAG_ENABLE_VLAN_CHK |
				 I40E_AQ_VSI_SEC_FLAG_ENABLE_MAC_CHK);
		}
		/* Setup the VSI tx/rx queue map for TC0 only for now */
		i40e_vsi_setup_queue_map(vsi, &ctxt, enabled_tc, true);
		break;

#ifdef I40E_FCOE
	case I40E_VSI_FCOE:
		ret = i40e_fcoe_vsi_init(vsi, &ctxt);
		if (ret) {
			dev_info(&pf->pdev->dev, "failed to initialize FCoE VSI\n");
			return ret;
		}
		break;

#endif /* I40E_FCOE */
	default:
		return -ENODEV;
	}
