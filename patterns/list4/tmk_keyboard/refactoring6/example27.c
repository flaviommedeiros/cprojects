if (CALLBACK_USB_GetDescriptor((DTYPE_Device << 8), 0, (void*)&DevDescriptorPtr
	#if defined(ARCH_HAS_MULTI_ADDRESS_SPACE) && \
	    !(defined(USE_FLASH_DESCRIPTORS) || defined(USE_EEPROM_DESCRIPTORS) || defined(USE_RAM_DESCRIPTORS))
	                               , &MemoryAddressSpace
	#endif
	                               ) == NO_DESCRIPTOR)
	{
		return;
	}
