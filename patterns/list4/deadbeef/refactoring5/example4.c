#ifdef STRICT_FORMAT_COMPATABILITY
if(FORMAT_VERSION < 2)
    {
        for(i = 0; i < strlen(magic); i++) {
            if(getc_exit(this_shn->vars.fd) != magic[i])
                return 0;
            this_shn->vars.bytes_read++;
        }

        /* get version number */
        version = getc_exit(this_shn->vars.fd);
        this_shn->vars.bytes_read++;
    }
    else
#endif /* STRICT_FORMAT_COMPATABILITY */
    {
        int nscan = 0;

        version = MAX_VERSION + 1;
        while(version > MAX_VERSION)
        {
            int byte = ddb_getc(this_shn->vars.fd);
            this_shn->vars.bytes_read++;
            if(byte == EOF)
                return 0;
            if(magic[nscan] != '\0' && byte == magic[nscan])
                nscan++;
            else
                if(magic[nscan] == '\0' && byte <= MAX_VERSION)
                    version = byte;
                else
                {
                    if(byte == magic[0])
                        nscan = 1;
                    else
                    {
                        nscan = 0;
                    }
                    version = MAX_VERSION + 1;
                }
        }
    }
