#ifdef USB_STM32F103_ENABLE_ALT_COPY
if (buffer->flags & USB_BUFFER_ARCH_ALT_COPY) {
    copy_to_hw_buffer(buffer, offset, len);
  } else
#endif    
    {
      const uint8_t *data;
      uint32_t *hw_data;
      if (len == 0) return;
      data = buffer->data;
      hw_data = ((u32*)USB_MEM_BASE) + offset/2;
      buffer->data += len;
      if (offset & 1) {
	*hw_data = (*hw_data & 0xff) | (*data++ << 8);
	hw_data++;
	len--;
      }
      while(len >= 2) {
	*hw_data++ = *((uint16_t*)data) ;
	data += 2;
	len -= 2;
      }
      if (len == 1) {
	*hw_data = *data++;
      }
    }
