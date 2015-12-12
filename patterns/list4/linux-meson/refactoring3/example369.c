switch (ioctl_num) {
	case IOCTL_TX_MSG(SET_BYPASS_PWOFF):
		bpctl_cmd.status =
		    set_bypass_pwoff_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_BYPASS_PWOFF):
		bpctl_cmd.status = get_bypass_pwoff_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(SET_BYPASS_PWUP):
		bpctl_cmd.status =
		    set_bypass_pwup_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_BYPASS_PWUP):
		bpctl_cmd.status = get_bypass_pwup_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(SET_BYPASS_WD):
		bpctl_cmd.status =
		    set_bypass_wd_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_BYPASS_WD):
		bpctl_cmd.status =
		    get_bypass_wd_fn(pbpctl_dev, (int *)&(bpctl_cmd.data[0]));
		break;

	case IOCTL_TX_MSG(GET_WD_EXPIRE_TIME):
		bpctl_cmd.status =
		    get_wd_expire_time_fn(pbpctl_dev,
					  (int *)&(bpctl_cmd.data[0]));
		break;

	case IOCTL_TX_MSG(RESET_BYPASS_WD_TIMER):
		bpctl_cmd.status = reset_bypass_wd_timer_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(GET_WD_SET_CAPS):
		bpctl_cmd.status = get_wd_set_caps_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(SET_STD_NIC):
		bpctl_cmd.status =
		    set_std_nic_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_STD_NIC):
		bpctl_cmd.status = get_std_nic_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(SET_TAP):
		bpctl_cmd.status =
		    set_tap_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_TAP):
		bpctl_cmd.status = get_tap_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(GET_TAP_CHANGE):
		bpctl_cmd.status = get_tap_change_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(SET_DIS_TAP):
		bpctl_cmd.status =
		    set_dis_tap_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_DIS_TAP):
		bpctl_cmd.status = get_dis_tap_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(SET_TAP_PWUP):
		bpctl_cmd.status =
		    set_tap_pwup_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_TAP_PWUP):
		bpctl_cmd.status = get_tap_pwup_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(SET_WD_EXP_MODE):
		bpctl_cmd.status =
		    set_wd_exp_mode_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_WD_EXP_MODE):
		bpctl_cmd.status = get_wd_exp_mode_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(GET_DIS_BYPASS):
		bpctl_cmd.status = get_dis_bypass_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(SET_DIS_BYPASS):
		bpctl_cmd.status =
		    set_dis_bypass_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_BYPASS_CHANGE):
		bpctl_cmd.status = get_bypass_change_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(GET_BYPASS):
		bpctl_cmd.status = get_bypass_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(SET_BYPASS):
		bpctl_cmd.status =
		    set_bypass_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_BYPASS_CAPS):
		bpctl_cmd.status = get_bypass_caps_fn(pbpctl_dev);
		/*preempt_enable(); */
		/*rcu_read_unlock();*/
		spin_unlock_irqrestore(&bpvm_lock, flags);
		if (copy_to_user
		    (argp, (void *)&bpctl_cmd, sizeof(struct bpctl_cmd))) {
			/*unlock_bpctl();   */
			/*preempt_enable(); */
			ret = -EFAULT;
			goto bp_exit;
		}
		goto bp_exit;

	case IOCTL_TX_MSG(GET_BYPASS_SLAVE):
		bpctl_cmd.status =
		    get_bypass_slave_fn(pbpctl_dev, &pbpctl_dev_out);
		if (bpctl_cmd.status == 1) {
			bpctl_cmd.out_param[4] = pbpctl_dev_out->bus;
			bpctl_cmd.out_param[5] = pbpctl_dev_out->slot;
			bpctl_cmd.out_param[6] = pbpctl_dev_out->func;
			bpctl_cmd.out_param[7] = pbpctl_dev_out->ifindex;
		}
		break;

	case IOCTL_TX_MSG(IS_BYPASS):
		bpctl_cmd.status = is_bypass(pbpctl_dev);
		break;
	case IOCTL_TX_MSG(SET_TX):
		bpctl_cmd.status = set_tx_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;
	case IOCTL_TX_MSG(GET_TX):
		bpctl_cmd.status = get_tx_fn(pbpctl_dev);
		break;
	case IOCTL_TX_MSG(SET_WD_AUTORESET):
		bpctl_cmd.status =
		    set_wd_autoreset_fn(pbpctl_dev, bpctl_cmd.in_param[2]);

		break;
	case IOCTL_TX_MSG(GET_WD_AUTORESET):

		bpctl_cmd.status = get_wd_autoreset_fn(pbpctl_dev);
		break;
	case IOCTL_TX_MSG(SET_DISC):
		bpctl_cmd.status =
		    set_disc_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;
	case IOCTL_TX_MSG(GET_DISC):
		bpctl_cmd.status = get_disc_fn(pbpctl_dev);
		break;
	case IOCTL_TX_MSG(GET_DISC_CHANGE):
		bpctl_cmd.status = get_disc_change_fn(pbpctl_dev);
		break;
	case IOCTL_TX_MSG(SET_DIS_DISC):
		bpctl_cmd.status =
		    set_dis_disc_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;
	case IOCTL_TX_MSG(GET_DIS_DISC):
		bpctl_cmd.status = get_dis_disc_fn(pbpctl_dev);
		break;
	case IOCTL_TX_MSG(SET_DISC_PWUP):
		bpctl_cmd.status =
		    set_disc_pwup_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;
	case IOCTL_TX_MSG(GET_DISC_PWUP):
		bpctl_cmd.status = get_disc_pwup_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(GET_BYPASS_INFO):

		bpctl_cmd.status =
		    get_bypass_info_fn(pbpctl_dev, (char *)&bpctl_cmd.data,
				       (char *)&bpctl_cmd.out_param[4]);
		break;

	case IOCTL_TX_MSG(SET_TPL):
		bpctl_cmd.status =
		    set_tpl_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_TPL):
		bpctl_cmd.status = get_tpl_fn(pbpctl_dev);
		break;
	case IOCTL_TX_MSG(SET_BP_WAIT_AT_PWUP):
		bpctl_cmd.status =
		    set_bp_wait_at_pwup_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_BP_WAIT_AT_PWUP):
		bpctl_cmd.status = get_bp_wait_at_pwup_fn(pbpctl_dev);
		break;
	case IOCTL_TX_MSG(SET_BP_HW_RESET):
		bpctl_cmd.status =
		    set_bp_hw_reset_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_BP_HW_RESET):
		bpctl_cmd.status = get_bp_hw_reset_fn(pbpctl_dev);
		break;
#ifdef BP_SELF_TEST
	case IOCTL_TX_MSG(SET_BP_SELF_TEST):
		bpctl_cmd.status =
		    set_bp_self_test_fn(pbpctl_dev, bpctl_cmd.in_param[2]);

		break;
	case IOCTL_TX_MSG(GET_BP_SELF_TEST):
		bpctl_cmd.status = get_bp_self_test_fn(pbpctl_dev);
		break;

#endif
#if 0
	case IOCTL_TX_MSG(SET_DISC_PORT):
		bpctl_cmd.status =
		    set_disc_port_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_DISC_PORT):
		bpctl_cmd.status = get_disc_port_fn(pbpctl_dev);
		break;

	case IOCTL_TX_MSG(SET_DISC_PORT_PWUP):
		bpctl_cmd.status =
		    set_disc_port_pwup_fn(pbpctl_dev, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_DISC_PORT_PWUP):
		bpctl_cmd.status = get_disc_port_pwup_fn(pbpctl_dev);
		break;
#endif
	case IOCTL_TX_MSG(SET_BP_FORCE_LINK):
		bpctl_cmd.status =
		    set_bp_force_link_fn(dev_idx, bpctl_cmd.in_param[2]);
		break;

	case IOCTL_TX_MSG(GET_BP_FORCE_LINK):
		bpctl_cmd.status = get_bp_force_link_fn(dev_idx);
		break;

	default:
		/*    unlock_bpctl(); */

		ret = -EOPNOTSUPP;
		/* preempt_enable(); */
		/* rcu_read_unlock();*/
		spin_unlock_irqrestore(&bpvm_lock, flags);
		goto bp_exit;
	}
