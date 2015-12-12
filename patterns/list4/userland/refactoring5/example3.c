#ifdef KHRN_GENERIC_MAP_RELOCATABLE
if (map->storage != MEM_INVALID_HANDLE) {
#endif
#ifdef KHRN_GENERIC_MAP_RELEASE_VALUE
#ifdef KHRN_GENERIC_MAP_RELOCATABLE
      KHRN_GENERIC_MAP(ENTRY_T) *base = (KHRN_GENERIC_MAP(ENTRY_T) *)mem_lock(map->storage);
#else
      KHRN_GENERIC_MAP(ENTRY_T) *base = map->storage;
#endif
      uint32_t i;
      for (i = 0; i != map->capacity; ++i) {
         if ((!KHRN_GENERIC_MAP_CMP_VALUE(base[i].value, KHRN_GENERIC_MAP_VALUE_DELETED)) && (!KHRN_GENERIC_MAP_CMP_VALUE(base[i].value, KHRN_GENERIC_MAP_VALUE_NONE))) {
            KHRN_GENERIC_MAP_RELEASE_VALUE(base[i].value);
         }
      }
#ifdef KHRN_GENERIC_MAP_RELOCATABLE
      mem_unlock(map->storage);
#endif
#endif
#ifdef KHRN_GENERIC_MAP_RELOCATABLE
      mem_release(map->storage);
      map->storage = MEM_INVALID_HANDLE;
   }
