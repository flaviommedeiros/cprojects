#ifdef RB_IPV6
if((prefix = ascii2prefix(AF_INET6, string)) != NULL) {
            node = rb_patricia_lookup(tree, prefix);
        } else
#endif
            return NULL;
