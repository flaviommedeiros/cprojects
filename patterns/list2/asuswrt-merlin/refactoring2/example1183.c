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
			  }
# ifdef _LIBC
			else
			  {
			    /* Try to match the byte sequence in `str' against
			       those known to the collate implementation.
			       First find out whether the bytes in `str' are
			       actually from exactly one character.  */
			    const int32_t *table;
			    const unsigned char *weights;
			    const unsigned char *extra;
			    const int32_t *indirect;
			    int32_t idx;
			    const unsigned char *cp = str;
			    int ch;

			    /* This #include defines a local function!  */
#  include <locale/weight.h>

			    table = (const int32_t *)
			      _NL_CURRENT (LC_COLLATE, _NL_COLLATE_TABLEMB);
			    weights = (const unsigned char *)
			      _NL_CURRENT (LC_COLLATE, _NL_COLLATE_WEIGHTMB);
			    extra = (const unsigned char *)
			      _NL_CURRENT (LC_COLLATE, _NL_COLLATE_EXTRAMB);
			    indirect = (const int32_t *)
			      _NL_CURRENT (LC_COLLATE, _NL_COLLATE_INDIRECTMB);

			    idx = findidx (&cp);
			    if (idx == 0 || cp < str + c1)
			      /* This is no valid character.  */
			      FREE_STACK_RETURN (REG_ECOLLATE);

			    /* Throw away the ] at the end of the equivalence
			       class.  */
			    PATFETCH (c);

			    /* Now we have to go throught the whole table
			       and find all characters which have the same
			       first level weight.

			       XXX Note that this is not entirely correct.
			       we would have to match multibyte sequences
			       but this is not possible with the current
			       implementation.  */
			    for (ch = 1; ch < 256; ++ch)
			      /* XXX This test would have to be changed if we
				 would allow matching multibyte sequences.  */
			      if (table[ch] > 0)
				{
				  int32_t idx2 = table[ch];
				  size_t len = weights[idx2];

				  /* Test whether the lenghts match.  */
				  if (weights[idx] == len)
				    {
				      /* They do.  New compare the bytes of
					 the weight.  */
				      size_t cnt = 0;

				      while (cnt < len
					     && (weights[idx + 1 + cnt]
						 == weights[idx2 + 1 + cnt]))
					++cnt;

				      if (cnt == len)
					/* They match.  Mark the character as
					   acceptable.  */
					SET_LIST_BIT (ch);
				    }
				}
			  }
