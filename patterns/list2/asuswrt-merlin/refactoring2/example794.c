# ifdef _LIBC
if (nrules == 0)
# endif
			  {
			    if (c1 != 1)
			      FREE_STACK_RETURN (REG_ECOLLATE);
			  }
# ifdef _LIBC
			else
			  {
			    const int32_t *table;
			    const int32_t *weights;
			    const int32_t *extra;
			    const int32_t *indirect;
			    wint_t *cp;

			    /* This #include defines a local function!  */
#  include <locale/weightwc.h>

			    if(delim == '=')
			      {
				/* We push the index for equivalence class.  */
				cp = (wint_t*)str;

				table = (const int32_t *)
				  _NL_CURRENT (LC_COLLATE,
					       _NL_COLLATE_TABLEWC);
				weights = (const int32_t *)
				  _NL_CURRENT (LC_COLLATE,
					       _NL_COLLATE_WEIGHTWC);
				extra = (const int32_t *)
				  _NL_CURRENT (LC_COLLATE,
					       _NL_COLLATE_EXTRAWC);
				indirect = (const int32_t *)
				  _NL_CURRENT (LC_COLLATE,
					       _NL_COLLATE_INDIRECTWC);

				idx = findidx ((const wint_t**)&cp);
				if (idx == 0 || cp < (wint_t*) str + c1)
				  /* This is no valid character.  */
				  FREE_STACK_RETURN (REG_ECOLLATE);

				str[0] = (wchar_t)idx;
			      }
			    else /* delim == '.' */
			      {
				/* We push collation sequence value
				   for collating symbol.  */
				int32_t table_size;
				const int32_t *symb_table;
				const unsigned char *extra;
				int32_t idx;
				int32_t elem;
				int32_t second;
				int32_t hash;
				char char_str[c1];

				/* We have to convert the name to a single-byte
				   string.  This is possible since the names
				   consist of ASCII characters and the internal
				   representation is UCS4.  */
				for (i = 0; i < c1; ++i)
				  char_str[i] = str[i];

				table_size =
				  _NL_CURRENT_WORD (LC_COLLATE,
						    _NL_COLLATE_SYMB_HASH_SIZEMB);
				symb_table = (const int32_t *)
				  _NL_CURRENT (LC_COLLATE,
					       _NL_COLLATE_SYMB_TABLEMB);
				extra = (const unsigned char *)
				  _NL_CURRENT (LC_COLLATE,
					       _NL_COLLATE_SYMB_EXTRAMB);

				/* Locate the character in the hashing table.  */
				hash = elem_hash (char_str, c1);

				idx = 0;
				elem = hash % table_size;
				second = hash % (table_size - 2);
				while (symb_table[2 * elem] != 0)
				  {
				    /* First compare the hashing value.  */
				    if (symb_table[2 * elem] == hash
					&& c1 == extra[symb_table[2 * elem + 1]]
					&& memcmp (char_str,
						   &extra[symb_table[2 * elem + 1]
							 + 1], c1) == 0)
				      {
					/* Yep, this is the entry.  */
					idx = symb_table[2 * elem + 1];
					idx += 1 + extra[idx];
					break;
				      }

				    /* Next entry.  */
				    elem += second;
				  }

				if (symb_table[2 * elem] != 0)
				  {
				    /* Compute the index of the byte sequence
				       in the table.  */
				    idx += 1 + extra[idx];
				    /* Adjust for the alignment.  */
				    idx = (idx + 3) & ~3;

				    str[0] = (wchar_t) idx + 4;
				  }
				else if (symb_table[2 * elem] == 0 && c1 == 1)
				  {
				    /* No valid character.  Match it as a
				       single byte character.  */
				    had_char_class = false;
				    BUF_PUSH(str[0]);
				    /* Update the length of characters  */
				    laststart[5]++;
				    range_start = str[0];

				    /* Throw away the ] at the end of the
				       collating symbol.  */
				    PATFETCH (c);
				    /* exit from the switch block.  */
				    continue;
				  }
				else
				  FREE_STACK_RETURN (REG_ECOLLATE);
			      }
			    datasize = 1;
			  }
