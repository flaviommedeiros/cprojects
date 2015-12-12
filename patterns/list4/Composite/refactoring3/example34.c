switch (type & 0XFF)
	{
#ifdef HAVE_LIBJPEG
		case CCV_IO_JPEG_FILE:
			_ccv_read_jpeg_fd(fd, x, ctype);
			break;
#endif
#ifdef HAVE_LIBPNG
		case CCV_IO_PNG_FILE:
			_ccv_read_png_fd(fd, x, ctype);
			break;
#endif
		case CCV_IO_BMP_FILE:
			_ccv_read_bmp_fd(fd, x, ctype);
			break;
		case CCV_IO_BINARY_FILE:
			_ccv_read_binary_fd(fd, x, ctype);
	}
