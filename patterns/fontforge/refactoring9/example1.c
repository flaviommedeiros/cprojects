char * ufo_name_number(
#ifdef FF_UTHASH_GLIF_NAMES
struct glif_name_index * glif_name_hash,
#else
void * glif_name_hash,
#endif
int index, const char * input, const char * prefix, const char * suffix, int flags) {
        // This does not append the prefix or the suffix.
        // The specification deals with name collisions by appending a 15-digit decimal number to the name.
        // But the name length cannot exceed 255 characters, so it is necessary to crop the base name if it is too long.
        // Name exclusions are case insensitive, so we uppercase.
        // flags & 16 forces appending a number.
        char * name_numbered = upper_case(input);
        char * full_name_base = same_case(input); // This is in case we do not need a number added.
        if (strlen(input) > (255 - strlen(prefix) - strlen(suffix))) {
          // If the numbered name base is too long, we crop it, even if we are not numbering.
          full_name_base[(255 - strlen(suffix))] = '\0';
          full_name_base = realloc(full_name_base, ((255 - strlen(prefix) - strlen(suffix)) + 1));
        }
        char * name_base = same_case(input); // This is in case we need a number added.
        long int name_number = 0;
#ifdef FF_UTHASH_GLIF_NAMES
        if (glif_name_hash != NULL) {
          if (strlen(input) > (255 - 15 - strlen(prefix) - strlen(suffix))) {
            // If the numbered name base is too long, we crop it.
            name_base[(255 - 15 - strlen(suffix))] = '\0';
            name_base = realloc(name_base, ((255 - 15 - strlen(prefix) - strlen(suffix)) + 1));
          }
          int number_once = ((flags & 16) ? 1 : 0);
          // Check the resulting name against a hash table of names.
          if (glif_name_search_glif_name(glif_name_hash, name_numbered) != NULL || number_once) {
            // If the name is taken, we must make space for a 15-digit number.
            char * name_base_upper = upper_case(name_base);
            while (glif_name_search_glif_name(glif_name_hash, name_numbered) != NULL || number_once) {
              name_number++; // Remangle the name until we have no more matches.
              free(name_numbered); name_numbered = NULL;
              asprintf(&name_numbered, "%s%015ld", name_base_upper, name_number);
              number_once = 0;
            }
            free(name_base_upper); name_base_upper = NULL;
          }
          // Insert the result into the hash table.
          glif_name_track_new(glif_name_hash, index, name_numbered);
        }
#endif
        // Now we want the correct capitalization.
        free(name_numbered); name_numbered = NULL;
        if (name_number > 0) {
          asprintf(&name_numbered, "%s%015ld", name_base, name_number);
        } else {
          asprintf(&name_numbered, "%s", full_name_base);
        }
        free(name_base); name_base = NULL;
        free(full_name_base); full_name_base = NULL;
        return name_numbered;
}
