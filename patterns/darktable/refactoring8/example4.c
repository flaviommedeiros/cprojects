static const uint8_t _imageio_ldr_magic[] = {
  /* jpeg magics */
  0x00, 0x00, 0x02, 0xff, 0xd8, // SOI marker

#ifdef HAVE_OPENJPEG
  /* jpeg 2000, jp2 format */
  0x00, 0x00, 0x0c, 0x0,  0x0,  0x0,  0x0C, 0x6A, 0x50, 0x20, 0x20, 0x0D, 0x0A, 0x87, 0x0A,

  /* jpeg 2000, j2k format */
  0x00, 0x00, 0x05, 0xFF, 0x4F, 0xFF, 0x51, 0x00,
#endif

  /* png image */
  0x00, 0x01, 0x03, 0x50, 0x4E, 0x47, // ASCII 'PNG'


  /* Canon CR2/CRW is like TIFF with additional magic numbers so must come
     before tiff as an exclusion */

  /* Most CR2 */
  0x01, 0x00, 0x0a, 0x49, 0x49, 0x2a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x43, 0x52,

  // Older Canon RAW format with TIF Extension (i.e. 1Ds and 1D)
  0x01, 0x00, 0x0a, 0x4d, 0x4d, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x10, 0xba, 0xb0,

  // Older Canon RAW format with TIF Extension (i.e. D2000)
  0x01, 0x00, 0x0a, 0x4d, 0x4d, 0x00, 0x2a, 0x00, 0x00, 0x11, 0x34, 0x00, 0x04,

  // Older Canon RAW format with TIF Extension (i.e. DCS1)
  0x01, 0x00, 0x0a, 0x49, 0x49, 0x2a, 0x00, 0x00, 0x03, 0x00, 0x00, 0xff, 0x01,

  // Older Kodak RAW format with TIF Extension (i.e. DCS560C)
  0x01, 0x00, 0x0a, 0x4d, 0x4d, 0x00, 0x2a, 0x00, 0x00, 0x11, 0x76, 0x00, 0x04,

  // Older Kodak RAW format with TIF Extension (i.e. DCS460D)
  0x01, 0x00, 0x0a, 0x49, 0x49, 0x2a, 0x00, 0x00, 0x03, 0x00, 0x00, 0x7c, 0x01,

  /* tiff image, intel */
  0x00, 0x00, 0x04, 0x4d, 0x4d, 0x00, 0x2a,

  /* tiff image, motorola */
  0x00, 0x00, 0x04, 0x49, 0x49, 0x2a, 0x00
};
