static int bin_pe_init_sections(struct PE_(r_bin_pe_obj_t)* bin) {
	int num_of_sections = bin->nt_headers->file_header.NumberOfSections;
	int sections_size;
	if (num_of_sections<1) {
		//eprintf("Warning: Invalid number of sections\n");
		return true;
	}
	sections_size = sizeof (PE_(image_section_header)) * num_of_sections;

	if (sections_size > bin->size) {
		eprintf ("Invalid NumberOfSections value\n");
		return false;
	}
	if (!(bin->section_header = malloc (sections_size))) {
		r_sys_perror ("malloc (section header)");
		return false;
	}
	if (r_buf_read_at (bin->b, bin->dos_header->e_lfanew + 4 + sizeof (PE_(image_file_header)) +
				bin->nt_headers->file_header.SizeOfOptionalHeader,
				(ut8*)bin->section_header, sections_size) == -1) {
		eprintf ("Warning: read (sections)\n");
		return false;
	}
#if 0
Each symbol table entry includes a name, storage class, type, value and section number. Short names (8 characters or fewer) are stored directly in the symbol table; longer names are stored as an paddr into the string table at the end of the COFF object.

================================================================
COFF SYMBOL TABLE RECORDS (18 BYTES)
================================================================
record
paddr

struct symrec {
	union {
		char string[8]; // short name
		struct {
			ut32 seros;
			ut32 stridx;
		} stridx;
	} name;
	ut32 value;
	ut16 secnum;
	ut16 symtype;
	ut8 symclass;
	ut8 numaux;
}
	   -------------------------------------------------------
   0  |                  8-char symbol name                   |
	  |          or 32-bit zeroes followed by 32-bit          |
	  |                 index into string table               |
	   -------------------------------------------------------
   8  |                     symbol value                      |
	   -------------------------------------------------------
  0Ch |       section number      |         symbol type       |
	   -------------------------------------------------------
  10h |  sym class  |   num aux   |
	   ---------------------------
  12h

#endif
	return true;
}
