if (residual == NULL

#ifdef _WIN32

        /* Avoid treating <drive>:<path> as a keytab type
         * specification */

        || name + 1 == residual
#endif
        ) {

        *ptype = "FILE";
        *ptype_len = strlen(*ptype);
        residual = name;
    } else {
        *ptype = name;
        *ptype_len = residual - name;
        residual++;
    }
