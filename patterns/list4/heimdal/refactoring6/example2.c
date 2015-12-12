if (residual == NULL ||
	ISPATHSEP(name[0])
#ifdef _WIN32
        /* Avoid treating <drive>:<path> as a keytab type
         * specification */
        || name + 1 == residual
#endif
        ) {

        *type = "FILE";
        *type_len = strlen(*type);
        residual = name;
    } else {
        *type = name;
        *type_len = residual - name;
        residual++;
    }
