# ifdef _LIBC
if (nrules == 0)
# endif
			  {
			    if (c1 != 1)
			      FREE_STACK_RETURN (REG_ECOLLATE);

			    /* Throw away the ] at the end of the equivalence
			       class.  */
			    PATFETCH (c);

			    /* Set the bit for the character.  */
			    SET_LIST_BIT (str[0]);
			    range_start = ((const unsigned char *) str)[0];
			  }
# ifdef _LIBC
			else
			  {
			    /* Try to match the byte sequence in `str' against
			       those known to the collate implementation.
			       First find out whether the bytes in `str' are
			       actually from exactly one character.  */
			    int32_t table_size;
			    const int32_t *symb_table;
			    const unsigned char *extra;
			    int32_t idx;
			    int32_t elem;
			    int32_t second;
			    int32_t hash;

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
			    hash = elem_hash (str, c1);

			    idx = 0;
			    elem = hash % table_size;
			    second = hash % (table_size - 2);
			    while (symb_table[2 * elem] != 0)
			      {
				/* First compare the hashing value.  */
				if (symb_table[2 * elem] == hash
				    && c1 == extra[symb_table[2 * elem + 1]]
				    && memcmp (str,
					       &extra[symb_table[2 * elem + 1]
						     + 1],
					       c1) == 0)
				  {
				    /* Yep, this is the entry.  */
				    idx = symb_table[2 * elem + 1];
				    idx += 1 + extra[idx];
				    break;
				  }

				/* Next entry.  */
				elem += second;
			      }

			    if (symb_table[2 * elem] == 0)
			      /* This is no valid character.  */
			      FREE_STACK_RETURN (REG_ECOLLATE);

			    /* Throw away the ] at the end of the equivalence
			       class.  */
			    PATFETCH (c);

			    /* Now add the multibyte character(s) we found
			       to the accept list.

			       XXX Note that this is not entirely correct.
			       we would have to match multibyte sequences
			       but this is not possible with the current
			       implementation.  Also, we have to match
			       collating symbols, which expand to more than
			       one file, as a whole and not allow the
			       individual bytes.  */
			    c1 = extra[idx++];
			    if (c1 == 1)
			      range_start = extra[idx];
			    while (c1-- > 0)
			      {
				SET_LIST_BIT (extra[idx]);
				++idx;
			      }
			  }
