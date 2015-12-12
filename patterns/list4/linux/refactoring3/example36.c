switch(buf[0]) {
	case EP1_CMD_GET_DEVICE_INFO:
	 	memcpy(&cdev->spec, buf+1, sizeof(struct caiaq_device_spec));
		cdev->spec.fw_version = le16_to_cpu(cdev->spec.fw_version);
		dev_dbg(dev, "device spec (firmware %d): audio: %d in, %d out, "
			"MIDI: %d in, %d out, data alignment %d\n",
			cdev->spec.fw_version,
			cdev->spec.num_analog_audio_in,
			cdev->spec.num_analog_audio_out,
			cdev->spec.num_midi_in,
			cdev->spec.num_midi_out,
			cdev->spec.data_alignment);

		cdev->spec_received++;
		wake_up(&cdev->ep1_wait_queue);
		break;
	case EP1_CMD_AUDIO_PARAMS:
		cdev->audio_parm_answer = buf[1];
		wake_up(&cdev->ep1_wait_queue);
		break;
	case EP1_CMD_MIDI_READ:
		snd_usb_caiaq_midi_handle_input(cdev, buf[1], buf + 3, buf[2]);
		break;
	case EP1_CMD_READ_IO:
		if (cdev->chip.usb_id ==
			USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AUDIO8DJ)) {
			if (urb->actual_length > sizeof(cdev->control_state))
				urb->actual_length = sizeof(cdev->control_state);
			memcpy(cdev->control_state, buf + 1, urb->actual_length);
			wake_up(&cdev->ep1_wait_queue);
			break;
		}
#ifdef CONFIG_SND_USB_CAIAQ_INPUT
	case EP1_CMD_READ_ERP:
	case EP1_CMD_READ_ANALOG:
		snd_usb_caiaq_input_dispatch(cdev, buf, urb->actual_length);
#endif
		break;
	}
