#ifdef USE_ENCHANT
if (enchant_dict_check (speller_buffer->spellers[i], word, strlen (word)) == 0)
#else
            if (aspell_speller_check (speller_buffer->spellers[i], word, -1) == 1)
#endif /* USE_ENCHANT */
                return 1;
