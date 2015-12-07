#if defined(WITH_LUA)
if(type != RULE_TYPE_LUA)
#endif
        {
            rid = apr_hash_get(dcfg->rule_id_htab, rule->actionset->id, APR_HASH_KEY_STRING);
            if(rid != NULL) {
                return "ModSecurity: Found another rule with the same id";
            } else    {
                apr_hash_set(dcfg->rule_id_htab, apr_pstrdup(dcfg->mp, rule->actionset->id), APR_HASH_KEY_STRING, apr_pstrdup(dcfg->mp, "1"));
            }

            //tmp_rule = msre_ruleset_fetch_rule(dcfg->ruleset, rule->actionset->id, offset);
            //if(tmp_rule != NULL)
            //    return "ModSecurity: Found another rule with the same id";
        }
