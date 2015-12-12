#if LUA_VERSION_NUM>=503
if (lua_dump(L, thread_dump, &b, 1) == 0)
#else
    if (lua_dump(L, thread_dump, &b) == 0)
#endif
    {
      luaL_pushresult(&b);
      buff = lua_tolstring(L, -1, l);
    } else
      luaL_error(L, "Error: unable to dump given function");
