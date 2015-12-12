if (
#ifndef CATCACHE_FORCE_RELEASE
				ct->dead &&
#endif
				ct->refcount == 0 &&
				(ct->c_list == NULL || ct->c_list->refcount == 0))
				CatCacheRemoveCTup(cache, ct);
