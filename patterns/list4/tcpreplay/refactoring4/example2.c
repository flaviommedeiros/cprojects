#if !defined (apollo)
if ((start + 1) != i)
#else
        if ((start + 1) != i && (start != 0 || i != 2))
#endif /* apollo */
        {
            strcpy( result + start + 1, result + i );
            i = start + 1;
        }
