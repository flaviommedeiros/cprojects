switch (state) {
#ifndef CONFIG_MSM_OTG_ENABLE_A_WAIT_BCON_TIMEOUT
		case OTG_STATE_A_WAIT_BCON:
			if (test_bit(ID_A, &dev->inputs))
				msm_otg_set_power(xceiv, USB_IDCHG_MIN - 100);
			msm_otg_put_suspend(dev);
			break;
#endif
		case OTG_STATE_A_HOST:
			clear_bit(A_BUS_REQ, &dev->inputs);
			wake_lock(&dev->wlock);
			queue_work(dev->wq, &dev->sm_work);
			break;
		case OTG_STATE_B_PERIPHERAL:
			if (xceiv->otg->gadget->b_hnp_enable) {
				set_bit(A_BUS_SUSPEND, &dev->inputs);
				set_bit(B_BUS_REQ, &dev->inputs);
				wake_lock(&dev->wlock);
				queue_work(dev->wq, &dev->sm_work);
			}
			break;
		case OTG_STATE_A_PERIPHERAL:
			msm_otg_start_timer(dev, TA_BIDL_ADIS,
					A_BIDL_ADIS);
			break;
		default:
			break;
		}
