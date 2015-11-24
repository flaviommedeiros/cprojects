int opal_dss_print_int64(char **output, char *prefix,
#ifdef HAVE_INT64_T
                          int64_t *src,
#else
                          void *src,
#endif  /* HAVE_INT64_T */
                         opal_data_type_t type)
{
    char *prefx;

    /* deal with NULL prefix */
    if (NULL == prefix) asprintf(&prefx, " ");
    else prefx = prefix;

    /* if src is NULL, just print data type and return */
    if (NULL == src) {
        asprintf(output, "%sData type: OPAL_INT64\tValue: NULL pointer", prefx);
        return OPAL_SUCCESS;
    }

#ifdef HAVE_INT64_T
    asprintf(output, "%sData type: OPAL_INT64\tValue: %ld", prefx, (long) *src);
#else
    asprintf(output, "%sData type: OPAL_INT64\tValue: unsupported", prefx);
#endif  /* HAVE_INT64_T */

    return OPAL_SUCCESS;
}
