switch(buf[0]) {
	case EP1_CMD_GET_DEVICE_INFO:
	 	memcpy(&dev->spec, buf+1, sizeof(struct caiaq_device_spec));
		dev->spec.fw_version = le16_to_cpu(dev->spec.fw_version);
		debug("device spec (firmware %d): audio: %d in, %d out, "
			"MIDI: %d in, %d out, data alignment %d\n",
			dev->spec.fw_version,
			dev->spec.num_analog_audio_in,
			dev->spec.num_analog_audio_out,
			dev->spec.num_midi_in,
			dev->spec.num_midi_out,
			dev->spec.data_alignment);

		dev->spec_received++;
		wake_up(&dev->ep1_wait_queue);
		break;
	case EP1_CMD_AUDIO_PARAMS:
		dev->audio_parm_answer = buf[1];
		wake_up(&dev->ep1_wait_queue);
		break;
	case EP1_CMD_MIDI_READ:
		snd_usb_caiaq_midi_handle_input(dev, buf[1], buf + 3, buf[2]);
		break;
	case EP1_CMD_READ_IO:
		if (dev->chip.usb_id ==
			USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AUDIO8DJ)) {
			if (urb->actual_length > sizeof(dev->control_state))
				urb->actual_length = sizeof(dev->control_state);
			memcpy(dev->control_state, buf + 1, urb->actual_length);
			wake_up(&dev->ep1_wait_queue);
			break;
		}
#ifdef CONFIG_SND_USB_CAIAQ_INPUT
	case EP1_CMD_READ_ERP:
	case EP1_CMD_READ_ANALOG:
		snd_usb_caiaq_input_dispatch(dev, buf, urb->actual_length);
#endif
		break;
	}
