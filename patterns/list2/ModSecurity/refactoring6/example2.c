if(rule->actionset->id == NOT_SET_P
#if defined(WITH_LUA)
            && (type != RULE_TYPE_LUA)
#endif
          )
            return "ModSecurity: No action id present within the rule";
