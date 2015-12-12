#ifdef _WIN32
if(!UnmapViewOfFile((LPINT)storage->data))
#else
            if (munmap(storage->data, storage->size*sizeof(real)))
#endif
              THError("could not unmap the shared memory file");
