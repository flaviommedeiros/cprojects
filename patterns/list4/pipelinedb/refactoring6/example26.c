if (input_filename
#ifdef YYDEBUG
		&& !yydebug
#endif
		)
	{
		/* "* 2" here is for escaping '\' and '"' below */
		char	   *line = mm_alloc(strlen("\n#line %d \"%s\"\n") + sizeof(int) * CHAR_BIT * 10 / 3 + strlen(input_filename) *2);
		char	   *src,
				   *dest;

		sprintf(line, "\n#line %d \"", yylineno);
		src = input_filename;
		dest = line + strlen(line);
		while (*src)
		{
			if (*src == '\\' || *src == '"')
				*dest++ = '\\';
			*dest++ = *src++;
		}
		*dest = '\0';
		strcat(dest, "\"\n");

		return line;
	}
