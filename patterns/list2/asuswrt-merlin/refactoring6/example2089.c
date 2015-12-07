if ((in != NULL) && (out != NULL) &&
#ifndef OPENSSL_SYS_MSDOS
        (stat(in, &ins) != -1) &&
        (stat(out, &outs) != -1) &&
        (ins.st_dev == outs.st_dev) && (ins.st_ino == outs.st_ino))
#else                           /* OPENSSL_SYS_MSDOS */
        (strcmp(in, out) == 0)
