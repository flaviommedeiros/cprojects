#ifdef STRICT_FORMAT_COMPATABILITY
if(FORMAT_VERSION < 2)
    {
        for(i = 0; i < strlen(magic); i++)
            if(getc_exit(this_shn->vars.fd) != magic[i]) {
                shn_error_fatal(this_shn,"Bad magic number");
                goto exit_thread;
            }

        /* get version number */
        version = getc_exit(this_shn->vars.fd);
    }
    else
#endif /* STRICT_FORMAT_COMPATABILITY */
    {
        int nscan = 0;

        version = MAX_VERSION + 1;
        while(version > MAX_VERSION)
        {
            int byte = ddb_getc(info->shnfile->vars.fd);
            if(byte == EOF) {
                shn_error_fatal(info->shnfile,"No magic number");
                trace ("shn_init: no magic number\n");
                return -1;
            }
            if(info->magic[nscan] != '\0' && byte == info->magic[nscan]) {
                nscan++;
            }
            else {
                if(info->magic[nscan] == '\0' && byte <= MAX_VERSION)
                    version = byte;
                else
                {
                    if(byte == info->magic[0])
                        nscan = 1;
                    else
                    {
                        nscan = 0;
                    }
                    version = MAX_VERSION + 1;
                }
            }
        }
    }
