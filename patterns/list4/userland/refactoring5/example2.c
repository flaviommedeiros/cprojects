#ifdef WORKAROUND_HW2038
if (khrn_image_is_brcm1(format) || khrn_image_is_brcm2(format)) {
      uint32_t log2_brcm2_width = khrn_image_get_log2_brcm2_width(format);
      uint32_t log2_brcm2_height = khrn_image_get_log2_brcm2_height(format);
      uint32_t width_in_brcm2s = (width + ((1 << log2_brcm2_width) - 1)) >> log2_brcm2_width;
      uint32_t height_in_brcm2s = (height + ((1 << log2_brcm2_height) - 1)) >> log2_brcm2_height;
      uint32_t hw2038_size =
         ((((height_in_brcm2s - 1) >> 3) << 7) +
         ((width_in_brcm2s - 1) >> 3) + 1) << 6;
      size = _max(size, hw2038_size);
   }
