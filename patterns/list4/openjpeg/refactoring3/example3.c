switch (parameters.cod_format) {
		case PXM_DFMT:			/* PNM PGM PPM */
			if (imagetopnm(image, parameters.outfile, parameters.split_pnm)) {
                fprintf(stderr,"[ERROR] Outfile %s not generated\n",parameters.outfile);
        failed = 1;
			}
			else {
                fprintf(stdout,"[INFO] Generated Outfile %s\n",parameters.outfile);
			}
			break;

		case PGX_DFMT:			/* PGX */
			if(imagetopgx(image, parameters.outfile)){
                fprintf(stderr,"[ERROR] Outfile %s not generated\n",parameters.outfile);
        failed = 1;
			}
			else {
                fprintf(stdout,"[INFO] Generated Outfile %s\n",parameters.outfile);
			}
			break;

		case BMP_DFMT:			/* BMP */
			if(imagetobmp(image, parameters.outfile)){
                fprintf(stderr,"[ERROR] Outfile %s not generated\n",parameters.outfile);
        failed = 1;
			}
			else {
                fprintf(stdout,"[INFO] Generated Outfile %s\n",parameters.outfile);
			}
			break;
#ifdef OPJ_HAVE_LIBTIFF
		case TIF_DFMT:			/* TIFF */
			if(imagetotif(image, parameters.outfile)){
                fprintf(stderr,"[ERROR] Outfile %s not generated\n",parameters.outfile);
        failed = 1;
			}
			else {
                fprintf(stdout,"[INFO] Generated Outfile %s\n",parameters.outfile);
			}
			break;
#endif /* OPJ_HAVE_LIBTIFF */
		case RAW_DFMT:			/* RAW */
			if(imagetoraw(image, parameters.outfile)){
                fprintf(stderr,"[ERROR] Error generating raw file. Outfile %s not generated\n",parameters.outfile);
        failed = 1;
			}
			else {
                fprintf(stdout,"[INFO] Generated Outfile %s\n",parameters.outfile);
			}
			break;

		case RAWL_DFMT:			/* RAWL */
			if(imagetorawl(image, parameters.outfile)){
                fprintf(stderr,"[ERROR] Error generating rawl file. Outfile %s not generated\n",parameters.outfile);
        failed = 1;
			}
			else {
                fprintf(stdout,"[INFO] Generated Outfile %s\n",parameters.outfile);
			}
			break;

		case TGA_DFMT:			/* TGA */
			if(imagetotga(image, parameters.outfile)){
                fprintf(stderr,"[ERROR] Error generating tga file. Outfile %s not generated\n",parameters.outfile);
        failed = 1;
			}
			else {
                fprintf(stdout,"[INFO] Generated Outfile %s\n",parameters.outfile);
			}
			break;
#ifdef OPJ_HAVE_LIBPNG
		case PNG_DFMT:			/* PNG */
			if(imagetopng(image, parameters.outfile)){
                fprintf(stderr,"[ERROR] Error generating png file. Outfile %s not generated\n",parameters.outfile);
        failed = 1;
			}
			else {
                fprintf(stdout,"[INFO] Generated Outfile %s\n",parameters.outfile);
			}
			break;
#endif /* OPJ_HAVE_LIBPNG */
/* Can happen if output file is TIFF or PNG
 * and OPJ_HAVE_LIBTIF or OPJ_HAVE_LIBPNG is undefined
*/
			default:
                fprintf(stderr,"[ERROR] Outfile %s not generated\n",parameters.outfile);
        failed = 1;
		}
