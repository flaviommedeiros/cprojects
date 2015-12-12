#if !defined(JPEG_LIB_MK1)
if( sp->cinfo.d.data_precision == 12 )
#endif
		{
			line_work_buf = (JSAMPROW)
			    _TIFFmalloc(sizeof(short) * sp->cinfo.d.output_width
			    * sp->cinfo.d.num_components );
		}
