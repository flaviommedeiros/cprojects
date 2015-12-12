#ifdef MAP_FAILED
if (mem == MAP_FAILED)
#else
    if (!mem)
#endif
    {
        swWarn("mmap() failed. Error: %s[%d]", strerror(errno), errno);
        return NULL;
    }
    else
    {
        object->size = size;
        object->mem = mem;
        return mem;
    }
