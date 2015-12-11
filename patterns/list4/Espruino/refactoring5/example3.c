#ifdef USE_USB_HID
if (epnum == (HID_IN_EP&0x7F)) {
    /* Ensure that the FIFO is empty before a new transfer, this condition could
    be caused by  a new transfer before the end of the previous transfer */
    handle->hidState = HID_IDLE;
  } else
#endif
  {
    // USB CDC
    handle->cdcState &= ~CDC_WRITE_TX_WAIT;
  }
