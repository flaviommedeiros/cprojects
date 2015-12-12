#ifdef HAVE_MMX
if(video->have_mmx)
	{
		video->mpeg3_zigzag_scan_table = mpeg3_zig_zag_scan_mmx;
		video->mpeg3_alternate_scan_table = mpeg3_alternate_scan_mmx;
	}
	else
#endif
	{
		video->mpeg3_zigzag_scan_table = mpeg3_zig_zag_scan_nommx;
		video->mpeg3_alternate_scan_table = mpeg3_alternate_scan_nommx;
	}
