if (root->len == -1) free(root->m); // malloced xml data
#ifndef EZXML_NOMMAP
        else if (root->len) munmap(root->m, root->len);
#endif
