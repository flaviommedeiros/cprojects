#ifdef HAVE_XINPUT
if (IsXInputDevice(&lpddi->guidProduct))
		{
			dev_list[num_devices].lpDIDevice = NULL;
			dev_list[num_devices].is_xinput_device = TRUE;
			dev_list[num_devices].user_index=((int *)pvRef)[0];
			((int *)pvRef)[0]++;
			num_devices++;
		}
		else
#endif
		{
			dev_list[num_devices].is_xinput_device = FALSE;
			if (SUCCEEDED(IDirectInput8_CreateDevice(lpDI8, &lpddi->guidInstance, &dev_list[num_devices].lpDIDevice,
				NULL) ))
			   num_devices++;
		}
