VideoInterface_struct *VIDCoreList[] = {
&VIDDummy,
#ifdef HAVE_LIBGTKGLEXT
&VIDOGL,
#endif
&VIDSoft,
NULL
};
