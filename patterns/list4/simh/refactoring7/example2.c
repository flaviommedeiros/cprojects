return ((TST_INT (PTR)? IOS_PTR: 0)
#if defined (IOS_PTRERR)
    | (ptr_err? IOS_PTRERR: 0)
#endif
    );
