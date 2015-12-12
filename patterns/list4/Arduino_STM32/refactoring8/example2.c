void dfu_load_file(struct dfu_file *file, enum suffix_req check_suffix, enum prefix_req check_prefix)
{
	off_t offset;
	int f;
	int i;
	int res;

	file->size.prefix = 0;
	file->size.suffix = 0;

	/* default values, if no valid suffix is found */
	file->bcdDFU = 0;
	file->idVendor = 0xffff; /* wildcard value */
	file->idProduct = 0xffff; /* wildcard value */
	file->bcdDevice = 0xffff; /* wildcard value */

	/* default values, if no valid prefix is found */
	file->lmdfu_address = 0;

	free(file->firmware);

	if (!strcmp(file->name, "-")) {
		int read_bytes;

#ifdef WIN32
		_setmode( _fileno( stdin ), _O_BINARY );
#endif
		file->firmware = (uint8_t*) dfu_malloc(STDIN_CHUNK_SIZE);
		read_bytes = fread(file->firmware, 1, STDIN_CHUNK_SIZE, stdin);
		file->size.total = read_bytes;
		while (read_bytes == STDIN_CHUNK_SIZE) {
			file->firmware = (uint8_t*) realloc(file->firmware, file->size.total + STDIN_CHUNK_SIZE);
			if (!file->firmware)
				err(EX_IOERR, "Could not allocate firmware buffer");
			read_bytes = fread(file->firmware + file->size.total, 1, STDIN_CHUNK_SIZE, stdin);
			file->size.total += read_bytes;
		}
		if (verbose)
			printf("Read %i bytes from stdin\n", file->size.total);
		/* Never require suffix when reading from stdin */
		check_suffix = MAYBE_SUFFIX;
	} else {
		f = open(file->name, O_RDONLY | O_BINARY);
		if (f < 0)
			err(EX_IOERR, "Could not open file %s for reading", file->name);

		offset = lseek(f, 0, SEEK_END);

		if ((int)offset < 0 || (int)offset != offset)
			err(EX_IOERR, "File size is too big");

		if (lseek(f, 0, SEEK_SET) != 0)
			err(EX_IOERR, "Could not seek to beginning");

		file->size.total = offset;
		file->firmware = dfu_malloc(file->size.total);

		if (read(f, file->firmware, file->size.total) != file->size.total) {
			err(EX_IOERR, "Could not read %d bytes from %s",
			    file->size.total, file->name);
		}
		close(f);
	}

	/* Check for possible DFU file suffix by trying to parse one */
	{
		uint32_t crc = 0xffffffff;
		const uint8_t *dfusuffix;
		int missing_suffix = 0;
		const char *reason;

		if (file->size.total < DFU_SUFFIX_LENGTH) {
			reason = "File too short for DFU suffix";
			missing_suffix = 1;
			goto checked;
		}

		dfusuffix = file->firmware + file->size.total -
		    DFU_SUFFIX_LENGTH;

		for (i = 0; i < file->size.total - 4; i++)
			crc = crc32_byte(crc, file->firmware[i]);

		if (dfusuffix[10] != 'D' ||
		    dfusuffix[9]  != 'F' ||
		    dfusuffix[8]  != 'U') {
			reason = "Invalid DFU suffix signature";
			missing_suffix = 1;
			goto checked;
		}

		file->dwCRC = (dfusuffix[15] << 24) +
		    (dfusuffix[14] << 16) +
		    (dfusuffix[13] << 8) +
		    dfusuffix[12];

		if (file->dwCRC != crc) {
			reason = "DFU suffix CRC does not match";
			missing_suffix = 1;
			goto checked;
		}

		/* At this point we believe we have a DFU suffix
		   so we require further checks to succeed */

		file->bcdDFU = (dfusuffix[7] << 8) + dfusuffix[6];

		if (verbose)
			printf("DFU suffix version %x\n", file->bcdDFU);

		file->size.suffix = dfusuffix[11];

		if (file->size.suffix < DFU_SUFFIX_LENGTH) {
			errx(EX_IOERR, "Unsupported DFU suffix length %d",
			    file->size.suffix);
		}

		if (file->size.suffix > file->size.total) {
			errx(EX_IOERR, "Invalid DFU suffix length %d",
			    file->size.suffix);
		}

		file->idVendor	= (dfusuffix[5] << 8) + dfusuffix[4];
		file->idProduct = (dfusuffix[3] << 8) + dfusuffix[2];
		file->bcdDevice = (dfusuffix[1] << 8) + dfusuffix[0];

checked:
		if (missing_suffix) {
			if (check_suffix == NEEDS_SUFFIX) {
				warnx("%s", reason);
				errx(EX_IOERR, "Valid DFU suffix needed");
			} else if (check_suffix == MAYBE_SUFFIX) {
				warnx("%s", reason);
				warnx("A valid DFU suffix will be required in "
				      "a future dfu-util release!!!");
			}
		} else {
			if (check_suffix == NO_SUFFIX) {
				errx(EX_SOFTWARE, "Please remove existing DFU suffix before adding a new one.\n");
			}
		}
	}
	res = probe_prefix(file);
	if ((res || file->size.prefix == 0) && check_prefix == NEEDS_PREFIX)
		errx(EX_IOERR, "Valid DFU prefix needed");
	if (file->size.prefix && check_prefix == NO_PREFIX)
		errx(EX_IOERR, "A prefix already exists, please delete it first");
	if (file->size.prefix && verbose) {
		uint8_t *data = file->firmware;
		if (file->prefix_type == LMDFU_PREFIX)
			printf("Possible TI Stellaris DFU prefix with "
				   "the following properties\n"
				   "Address:        0x%08x\n"
				   "Payload length: %d\n",
				   file->lmdfu_address,
				   data[4] | (data[5] << 8) |
				   (data[6] << 16) | (data[7] << 14));
		else if (file->prefix_type == LPCDFU_UNENCRYPTED_PREFIX)
			printf("Possible unencrypted NXP LPC DFU prefix with "
				   "the following properties\n"
				   "Payload length: %d kiByte\n",
				   data[2] >>1 | (data[3] << 7) );
		else
			errx(EX_IOERR, "Unknown DFU prefix type");
	}
}
