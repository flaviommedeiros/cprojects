#ifdef TM_ZONE
if (t->TM_ZONE != NULL)
                    pt = _add(t->TM_ZONE, pt, ptlim,
                                                  modifier);
                else
#endif /* defined TM_ZONE */
                if (t->tm_isdst >= 0)
                    pt = _add(tzname[t->tm_isdst != 0],
                        pt, ptlim, modifier);
