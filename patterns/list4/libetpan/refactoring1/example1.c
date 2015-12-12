if (message->mstring != NULL)
    mmap_string_free(message->mstring);
#ifndef MMAP_UNAVAILABLE
  else if (message->data != NULL)
    munmap(message->data, message->len);
#endif
