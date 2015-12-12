if ( f->f_dir.len && ( f->f_base.len || f->f_suffix.len )
#if PATH_DELIM == '\\'
        && !( f->f_dir.len == 3 && f->f_dir.ptr[ 1 ] == ':' )
#endif
        && !( f->f_dir.len == 1 && is_path_delim( f->f_dir.ptr[ 0 ] ) ) )
        string_push_back( file, as_path_delim( f->f_dir.ptr[ f->f_dir.len ] ) );
