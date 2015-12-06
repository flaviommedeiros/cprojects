judyvalue JudyMask[9] = {
0, 0xff, 0xffff, 0xffffff, 0xffffffff,
#if JUDY_key_size > 4
0xffffffffffULL, 0xffffffffffffULL, 0xffffffffffffffULL, 0xffffffffffffffffULL
#endif
};
