#ifdef RB_IPV6
if(family == AF_INET6) {
        default_bitlen = 128;
        if(prefix == NULL) {
            prefix = rb_malloc(sizeof(rb_prefix_t));
            dynamic_allocated++;
        }
        memcpy(&prefix->add.sin6, dest, 16);
    } else
#endif /* RB_IPV6 */
        if(family == AF_INET) {
            if(prefix == NULL) {
                prefix = rb_malloc(sizeof(rb_prefix_t));
                dynamic_allocated++;
            }
            memcpy(&prefix->add.sin, dest, 4);
        } else {
            return (NULL);
        }
