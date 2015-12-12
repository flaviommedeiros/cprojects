#ifdef IN_LIBGLOCALE
if (strchr (alias, '_') == NULL)
#endif
		{
		  size_t alias_len;
		  size_t value_len;

		  if (nmap >= maxmap)
		    if (__builtin_expect (extend_alias_table (), 0))
		      goto out;

		  alias_len = strlen (alias) + 1;
		  value_len = strlen (value) + 1;

		  if (string_space_act + alias_len + value_len > string_space_max)
		    {
		      /* Increase size of memory pool.  */
		      size_t new_size = (string_space_max
					 + (alias_len + value_len > 1024
					    ? alias_len + value_len : 1024));
		      char *new_pool = (char *) realloc (string_space, new_size);
		      if (new_pool == NULL)
			goto out;

		      if (__builtin_expect (string_space != new_pool, 0))
			{
			  size_t i;

			  for (i = 0; i < nmap; i++)
			    {
			      map[i].alias += new_pool - string_space;
			      map[i].value += new_pool - string_space;
			    }
			}

		      string_space = new_pool;
		      string_space_max = new_size;
		    }

		  map[nmap].alias =
		    (const char *) memcpy (&string_space[string_space_act],
					   alias, alias_len);
		  string_space_act += alias_len;

		  map[nmap].value =
		    (const char *) memcpy (&string_space[string_space_act],
					   value, value_len);
		  string_space_act += value_len;

		  ++nmap;
		  ++added;
		}
