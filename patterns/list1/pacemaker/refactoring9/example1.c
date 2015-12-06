int
scandir(const char *directory_name,
        struct dirent ***array_pointer, int (*select_function) (const struct dirent *),
#ifdef USE_SCANDIR_COMPARE_STRUCT_DIRENT
        /* This is what the linux man page says */
        int (*compare_function) (const struct dirent **, const struct dirent **)
#else
        /* This is what the linux header file says ... */
        int (*compare_function) (const void *, const void *)
#endif
    )
{
    DIR *directory;
    struct dirent **array;
    struct dirent *entry;
    struct dirent *copy;
    int allocated = INITIAL_ALLOCATION;
    int counter = 0;

    /* Get initial list space and open directory.  */

    if (directory = opendir(directory_name), directory == NULL)
        return -1;

    if (array = (struct dirent **)malloc(allocated * sizeof(struct dirent *)), array == NULL)
        return -1;

    /* Read entries in the directory.  */

    while (entry = readdir(directory), entry)
        if (select_function == NULL || (*select_function) (entry)) {
            /* User wants them all, or he wants this one.  Copy the entry.  */

            /*
             * On some OSes the declaration of "entry->d_name" is a minimal-length
             * placeholder.  Example: Solaris:
             *      /usr/include/sys/dirent.h:
             *              "char d_name[1];"
             *      man page "dirent(3)":
             *              The field d_name is the beginning of the character array
             *              giving the name of the directory entry. This name is
             *              null terminated and may have at most MAXNAMLEN chars.
             * So our malloc length may need to be increased accordingly.
             *      sizeof(entry->d_name): space (possibly minimal) in struct.
             *      strlen(entry->d_name): actual length of the entry. 
             *
             *                      John Kavadias <john_kavadias@hotmail.com>
             *                      David Lee <t.d.lee@durham.ac.uk>
             */
            int namelength = strlen(entry->d_name) + 1; /* length with NULL */
            int extra = 0;

            if (sizeof(entry->d_name) <= namelength) {
                /* allocated space <= required space */
                extra += namelength - sizeof(entry->d_name);
            }

            if (copy = (struct dirent *)malloc(sizeof(struct dirent) + extra), copy == NULL) {
                closedir(directory);
                free(array);
                return -1;
            }
            copy->d_ino = entry->d_ino;
            copy->d_reclen = entry->d_reclen;
            strcpy(copy->d_name, entry->d_name);

            /* Save the copy.  */

            if (counter + 1 == allocated) {
                allocated <<= 1;
                array = (struct dirent **)
                    realloc_safe((char *)array, allocated * sizeof(struct dirent *));
                if (array == NULL) {
                    closedir(directory);
                    free(array);
                    free(copy);
                    return -1;
                }
            }
            array[counter++] = copy;
        }

    /* Close things off.  */

    array[counter] = NULL;
    *array_pointer = array;
    closedir(directory);

    /* Sort?  */

    if (counter > 1 && compare_function)
        qsort((char *)array, counter, sizeof(struct dirent *)
              , (int (*)(const void *, const void *))(compare_function));

    return counter;
}
