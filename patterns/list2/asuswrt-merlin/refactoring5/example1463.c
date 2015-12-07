#if 1
if (nt->lwn > 0) {
        num = nt->lwn;
        nt->lwn = 0;
    } else {
        if (RAND_pseudo_bytes(&n, 1) < 0)
            return -1;
        num = (n & 7);
    }
