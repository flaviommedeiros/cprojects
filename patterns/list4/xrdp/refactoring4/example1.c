#ifdef ACCESS
if ((g_strncmp(name, "password", 255) == 0) || (g_strncmp(name, "pampassword", 255) == 0))
#else
                if (g_strncmp(name, "password", 255) == 0)
#endif
                {
                    b->password_char = '*';

                    if (username_set)
                    {
                        if (b->parent != 0)
                        {
                            b->parent->focused_control = b;
                        }
                    }
                }
