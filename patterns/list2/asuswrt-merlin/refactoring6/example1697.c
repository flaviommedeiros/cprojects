if ((flags & NETSNMP_DIR_RECURSE) 
#if defined(HAVE_STRUCT_DIRENT_D_TYPE) && defined(DT_DIR)
            && (file->d_type == DT_DIR)
#elif defined(S_ISDIR)
            && (stat(file->d_name, &statbuf) != 0) && (S_ISDIR(statbuf.st_mode))
#endif
            ) {
            /** xxx add the dir as well? not for now.. maybe another flag? */
            netsnmp_directory_container_read(container, path, flags);
        }
        else if (flags & NETSNMP_DIR_NSFILE) {
            if (_insert_nsfile( container, file->d_name,
                                filter ? &statbuf : NULL, flags ) < 0)
                break;
        }
        else {
            char *dup = strdup(path);
            if (NULL == dup) {
                snmp_log(LOG_ERR,
                         "strdup failed while building directory container\n");
                break;
            }
            rc = CONTAINER_INSERT(container, dup);
            if (-1 == rc ) {
                DEBUGMSGTL(("directory:container", "  err adding %s\n", path));
                free(dup);
            }
        }
