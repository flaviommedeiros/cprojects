const size_t size_map[] = { sizeof (int8),
    sizeof (int8), sizeof (int16), sizeof (int32), sizeof (int32)
#if defined (USE_INT64)
    , sizeof (t_int64), sizeof (t_int64), sizeof (t_int64), sizeof (t_int64)
#endif
};
