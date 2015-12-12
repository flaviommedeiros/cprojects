private int
history_load(TYPE(History) *h, const char *fname)
{
	FILE *fp;
	char *line;
	size_t sz, max_size;
	char *ptr;
	int i = -1;
	TYPE(HistEvent) ev;
#ifdef WIDECHAR
	static ct_buffer_t conv;
#endif

	if ((fp = fopen(fname, "r")) == NULL)
		return i;

	if ((line = fgetln(fp, &sz)) == NULL)
		goto done;

	if (strncmp(line, hist_cookie, sz) != 0)
		goto done;

	ptr = h_malloc((max_size = 1024) * sizeof(*ptr));
	if (ptr == NULL)
		goto done;
	for (i = 0; (line = fgetln(fp, &sz)) != NULL; i++) {
		char c = line[sz];

		if (sz != 0 && line[sz - 1] == '\n')
			line[--sz] = '\0';
		else
			line[sz] = '\0';

		if (max_size < sz) {
			char *nptr;
			max_size = (sz + 1024) & (size_t)~1023;
			nptr = h_realloc(ptr, max_size * sizeof(*ptr));
			if (nptr == NULL) {
				i = -1;
				goto oomem;
			}
			ptr = nptr;
		}
		(void) strunvis(ptr, line);
		line[sz] = c;
		if (HENTER(h, &ev, ct_decode_string(ptr, &conv)) == -1) {
			i = -1;
			goto oomem;
		}
	}
oomem:
	h_free(ptr);
done:
	(void) fclose(fp);
	return i;
}
