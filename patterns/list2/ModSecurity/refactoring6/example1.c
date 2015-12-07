if (
#if defined(WITH_LUA)
            type != RULE_TYPE_LUA &&
#endif
            (dcfg->tmp_chain_starter == NULL))
                if(rule->actionset == NULL)
                    return "ModSecurity: Rules must have at least id action";
