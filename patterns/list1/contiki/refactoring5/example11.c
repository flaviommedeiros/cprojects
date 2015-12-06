#ifdef USB_STM32F103_ENABLE_ALT_COPY
if (buffer->flags & USB_BUFFER_ARCH_ALT_COPY) {
    copy_from_hw_buffer(buffer, offset, len);
  } else
#endif
    {
      uint8_t *data = buffer->data;
      const uint32_t *hw_data = ((u32*)USB_MEM_BASE) + offset/2;
      buffer->data += len;
      if (offset & 1) {
	*data++ = *hw_data++ >> 8;
	len--;
      }
      while(len >= 2) {
	*((uint16_t*)data) = *hw_data++;
	data += 2;
	len -= 2;
      }
      if (len == 1) {
	*data++ = *hw_data;
      }
    }
