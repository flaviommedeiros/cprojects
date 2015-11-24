#if LUA_VERSION_NUM < 503
if ((LUA_TNUMBER != lua_type(L,-1)) || (n = lua_tonumber(L, -1)) <= 0 ||
            !IS_INT_EQUIVALENT(n))
#else
        if (!lua_isinteger(L,-1) || (n = lua_tointeger(L, -1)) <= 0)
#endif
        {
            lua_settop(L, stacktop);
            return 0;
        }
