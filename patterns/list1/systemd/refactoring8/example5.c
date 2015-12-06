static struct HashmapBase *hashmap_base_new(const struct hash_ops *hash_ops, enum HashmapType type HASHMAP_DEBUG_PARAMS) {
        HashmapBase *h;
        const struct hashmap_type_info *hi = &hashmap_type_info[type];
        bool use_pool;

        use_pool = is_main_thread();

        h = use_pool ? mempool_alloc0_tile(hi->mempool) : malloc0(hi->head_size);

        if (!h)
                return NULL;

        h->type = type;
        h->from_pool = use_pool;
        h->hash_ops = hash_ops ? hash_ops : &trivial_hash_ops;

        if (type == HASHMAP_TYPE_ORDERED) {
                OrderedHashmap *lh = (OrderedHashmap*)h;
                lh->iterate_list_head = lh->iterate_list_tail = IDX_NIL;
        }

        reset_direct_storage(h);

        if (!shared_hash_key_initialized) {
                random_bytes(shared_hash_key, sizeof(shared_hash_key));
                shared_hash_key_initialized= true;
        }

#ifdef ENABLE_DEBUG_HASHMAP
        h->debug.func = func;
        h->debug.file = file;
        h->debug.line = line;
        assert_se(pthread_mutex_lock(&hashmap_debug_list_mutex) == 0);
        LIST_PREPEND(debug_list, hashmap_debug_list, &h->debug);
        assert_se(pthread_mutex_unlock(&hashmap_debug_list_mutex) == 0);
#endif

        return h;
}
