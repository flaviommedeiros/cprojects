if ((DescriptorSize = CALLBACK_USB_GetDescriptor(USB_ControlRequest.wValue, USB_ControlRequest.wIndex,
	                                                 &DescriptorPointer
	#if defined(ARCH_HAS_MULTI_ADDRESS_SPACE) && \
	    !(defined(USE_FLASH_DESCRIPTORS) || defined(USE_EEPROM_DESCRIPTORS) || defined(USE_RAM_DESCRIPTORS))
	                                                 , &DescriptorAddressSpace
	#endif
													 )) == NO_DESCRIPTOR)
	{
		return;
	}
