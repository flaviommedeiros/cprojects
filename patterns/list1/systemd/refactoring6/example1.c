if (path_equal(m->path, "/")
#ifndef HAVE_SPLIT_USR
                    || path_equal(m->path, "/usr")
#endif
                )
                        continue;
