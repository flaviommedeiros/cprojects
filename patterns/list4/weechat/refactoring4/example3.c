#ifdef LUA_VERSION_NUM
if (luaL_dostring (lua_current_interpreter, weechat_lua_code) != 0)
#else
    if (lua_dostring (lua_current_interpreter, weechat_lua_code) != 0)
#endif /* LUA_VERSION_NUM */
    {
        weechat_printf (NULL,
                        weechat_gettext ("%s%s: unable to redirect stdout "
                                         "and stderr"),
                        weechat_prefix ("error"), LUA_PLUGIN_NAME);
    }
