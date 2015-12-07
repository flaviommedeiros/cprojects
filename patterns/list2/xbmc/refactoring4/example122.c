#if defined(__FreeBSD__) && !defined(__alpha__)
if(!output_text_code)
	output_text_code = safe_strdup(OUTPUT_TEXT_CODE);
