# if USE_SNPRINTF
if (sizeof (DCHAR_T) != sizeof (TCHAR_T))
# endif
                          {
                            const TCHAR_T *tmpsrc;
                            DCHAR_T *tmpdst;
                            size_t n;

# if USE_SNPRINTF
                            if (result == resultbuf)
                              {
                                tmpsrc = (TCHAR_T *) (result + length);
                                /* ENSURE_ALLOCATION will not move tmpsrc
                                   (because it's part of resultbuf).  */
                                ENSURE_ALLOCATION (xsum (length, count));
                              }
                            else
                              {
                                /* ENSURE_ALLOCATION will move the array
                                   (because it uses realloc().  */
                                ENSURE_ALLOCATION (xsum (length, count));
                                tmpsrc = (TCHAR_T *) (result + length);
                              }
# else
                            tmpsrc = tmp;
                            ENSURE_ALLOCATION (xsum (length, count));
# endif
                            tmpdst = result + length;
                            /* Copy backwards, because of overlapping.  */
                            tmpsrc += count;
                            tmpdst += count;
                            for (n = count; n > 0; n--)
                              *--tmpdst = (unsigned char) *--tmpsrc;
                          }
