switch (c) {
			case 0: /* long opt with flag */
				break;
			case 'i':			/* input file */
			{
				char *infile = opj_optarg;
				parameters->decod_format = infile_format(infile);
				switch(parameters->decod_format) {
					case J2K_CFMT:
						break;
					case JP2_CFMT:
						break;
					case JPT_CFMT:
						break;
                                        case -2:
						fprintf(stderr, 
							"!! infile cannot be read: %s !!\n\n", 
							infile);
						return 1;
					default:
						fprintf(stderr, 
                            "[ERROR] Unknown input file format: %s \n"
                            "        Known file formats are *.j2k, *.jp2, *.jpc or *.jpt\n",
							infile);
						return 1;
				}
				if (opj_strcpy_s(parameters->infile, sizeof(parameters->infile), infile) != 0) {
					fprintf(stderr, "[ERROR] Path is too long\n");
					return 1;
				}
			}
			break;
				
				/* ----------------------------------------------------- */

			case 'o':			/* output file */
			{
				char *outfile = opj_optarg;
				parameters->cod_format = get_file_format(outfile);
				switch(parameters->cod_format) {
					case PGX_DFMT:
						break;
					case PXM_DFMT:
						break;
					case BMP_DFMT:
						break;
					case TIF_DFMT:
						break;
					case RAW_DFMT:
						break;
					case RAWL_DFMT:
						break;
					case TGA_DFMT:
						break;
					case PNG_DFMT:
						break;
					default:
						fprintf(stderr, "Unknown output format image %s [only *.png, *.pnm, *.pgm, *.ppm, *.pgx, *.bmp, *.tif, *.raw or *.tga]!!\n", outfile);
						return 1;
				}
				if (opj_strcpy_s(parameters->outfile, sizeof(parameters->outfile), outfile) != 0) {
					fprintf(stderr, "[ERROR] Path is too long\n");
					return 1;
				}
			}
			break;
			
				/* ----------------------------------------------------- */

			case 'O':			/* output format */
			{
				char outformat[50];
				char *of = opj_optarg;
				sprintf(outformat,".%s",of);
				img_fol->set_out_format = 1;
				parameters->cod_format = get_file_format(outformat);
				switch(parameters->cod_format) {
					case PGX_DFMT:
						img_fol->out_format = "pgx";
						break;
					case PXM_DFMT:
						img_fol->out_format = "ppm";
						break;
					case BMP_DFMT:
						img_fol->out_format = "bmp";
						break;
					case TIF_DFMT:
						img_fol->out_format = "tif";
						break;
					case RAW_DFMT:
						img_fol->out_format = "raw";
						break;
					case RAWL_DFMT:
						img_fol->out_format = "rawl";
						break;
					case TGA_DFMT:
						img_fol->out_format = "raw";
						break;
					case PNG_DFMT:
						img_fol->out_format = "png";
						break;
					default:
						fprintf(stderr, "Unknown output format image %s [only *.png, *.pnm, *.pgm, *.ppm, *.pgx, *.bmp, *.tif, *.raw or *.tga]!!\n", outformat);
						return 1;
						break;
				}
			}
			break;

				/* ----------------------------------------------------- */


			case 'r':		/* reduce option */
			{
				sscanf(opj_optarg, "%u", &(parameters->core.cp_reduce));
			}
			break;
			
				/* ----------------------------------------------------- */
      

			case 'l':		/* layering option */
			{
				sscanf(opj_optarg, "%u", &(parameters->core.cp_layer));
			}
			break;
			
				/* ----------------------------------------------------- */

			case 'h': 			/* display an help description */
				decode_help_display();
				return 1;				

            /* ----------------------------------------------------- */

			case 'y':			/* Image Directory path */
                {
					img_fol->imgdirpath = (char*)malloc(strlen(opj_optarg) + 1);
					strcpy(img_fol->imgdirpath,opj_optarg);
					img_fol->set_imgdir=1;
				}
				break;

				/* ----------------------------------------------------- */

			case 'd':     		/* Input decode ROI */
			{
				size_t size_optarg = (size_t)strlen(opj_optarg) + 1U;
				char *ROI_values = (char*) malloc(size_optarg);
				if (ROI_values == NULL) {
					fprintf(stderr, "[ERROR] Couldn't allocate memory\n");
					return 1;
				}
				ROI_values[0] = '\0';
				memcpy(ROI_values, opj_optarg, size_optarg);
				/*printf("ROI_values = %s [%d / %d]\n", ROI_values, strlen(ROI_values), size_optarg ); */
				parse_DA_values( ROI_values, &parameters->DA_x0, &parameters->DA_y0, &parameters->DA_x1, &parameters->DA_y1);

				free(ROI_values);
			}
			break;

			/* ----------------------------------------------------- */

			case 't':     		/* Input tile index */
			{
				sscanf(opj_optarg, "%u", &parameters->tile_index);
				parameters->nb_tile_to_decode = 1;
			}
			break;

				/* ----------------------------------------------------- */								

			case 'x':			/* Creation of index file */
				{
					if (opj_strcpy_s(parameters->indexfilename, sizeof(parameters->indexfilename), opj_optarg) != 0) {
						fprintf(stderr, "[ERROR] Path is too long\n");
						return 1;
					}
				}
				break;
				
				/* ----------------------------------------------------- */
			case 'p': /* Force precision */
				{
					if (!parse_precision(opj_optarg, parameters))
					{
						return 1;
					}
				}
				break;
				/* ----------------------------------------------------- */
				
				/* UniPG>> */
#ifdef USE_JPWL
			
			case 'W': 			/* activate JPWL correction */
			{
				char *token = NULL;

				token = strtok(opj_optarg, ",");
				while(token != NULL) {

					/* search expected number of components */
					if (*token == 'c') {

						static int compno;

						compno = JPWL_EXPECTED_COMPONENTS; /* predefined no. of components */

						if(sscanf(token, "c=%d", &compno) == 1) {
							/* Specified */
							if ((compno < 1) || (compno > 256)) {
								fprintf(stderr, "ERROR -> invalid number of components c = %d\n", compno);
								return 1;
							}
							parameters->jpwl_exp_comps = compno;

						} else if (!strcmp(token, "c")) {
							/* default */
							parameters->jpwl_exp_comps = compno; /* auto for default size */

						} else {
							fprintf(stderr, "ERROR -> invalid components specified = %s\n", token);
							return 1;
						};
					}

					/* search maximum number of tiles */
					if (*token == 't') {

						static int tileno;

						tileno = JPWL_MAXIMUM_TILES; /* maximum no. of tiles */

						if(sscanf(token, "t=%d", &tileno) == 1) {
							/* Specified */
							if ((tileno < 1) || (tileno > JPWL_MAXIMUM_TILES)) {
								fprintf(stderr, "ERROR -> invalid number of tiles t = %d\n", tileno);
								return 1;
							}
							parameters->jpwl_max_tiles = tileno;

						} else if (!strcmp(token, "t")) {
							/* default */
							parameters->jpwl_max_tiles = tileno; /* auto for default size */

						} else {
							fprintf(stderr, "ERROR -> invalid tiles specified = %s\n", token);
							return 1;
						};
					}

					/* next token or bust */
					token = strtok(NULL, ",");
				};
				parameters->jpwl_correct = OPJ_TRUE;
				fprintf(stdout, "JPWL correction capability activated\n");
				fprintf(stdout, "- expecting %d components\n", parameters->jpwl_exp_comps);
			}
			break;	
#endif /* USE_JPWL */
/* <<UniPG */            

				/* ----------------------------------------------------- */
			
        default:
            fprintf(stderr, "[WARNING] An invalid option has been ignored.\n");
            break;
		}
