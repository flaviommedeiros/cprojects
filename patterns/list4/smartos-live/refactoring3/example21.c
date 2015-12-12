switch (*flagp & GCF_TYPEMASK) {
      case GCX_OBJECT:
        if (RECURSION_TOO_DEEP())
            goto add_to_unscanned_bag;
        /* If obj->slots is null, obj must be a newborn. */
        obj = (JSObject *) thing;
        vp = obj->slots;
        if (!vp)
            break;

        /* Mark slots if they are small enough to be GC-allocated. */
        if ((vp[-1] + 1) * sizeof(jsval) <= GC_NBYTES_MAX)
            GC_MARK(cx, vp - 1, "slots");

        /* Set up local variables to loop over unmarked things. */
        end = vp + ((obj->map->ops->mark)
                    ? obj->map->ops->mark(cx, obj, NULL)
                    : JS_MIN(obj->map->freeslot, obj->map->nslots));
        thing = NULL;
        flagp = NULL;
#ifdef GC_MARK_DEBUG
        scope = OBJ_IS_NATIVE(obj) ? OBJ_SCOPE(obj) : NULL;
#endif
        for (; vp != end; ++vp) {
            v = *vp;
            if (!JSVAL_IS_GCTHING(v) || v == JSVAL_NULL)
                continue;
            next_thing = JSVAL_TO_GCTHING(v);
            if (next_thing == thing)
                continue;
            next_flagp = js_GetGCThingFlags(next_thing);
            if (*next_flagp & GCF_MARK)
                continue;
            JS_ASSERT(*next_flagp != GCF_FINAL);
            if (thing) {
#ifdef GC_MARK_DEBUG
                GC_MARK(cx, thing, name);
#else
                *flagp |= GCF_MARK;
                MarkGCThingChildren(cx, thing, flagp, JS_TRUE);
#endif
                if (*next_flagp & GCF_MARK) {
                    /*
                     * This happens when recursive MarkGCThingChildren marks
                     * the thing with flags referred by *next_flagp.
                     */
                    thing = NULL;
                    continue;
                }
            }
#ifdef GC_MARK_DEBUG
            GetObjSlotName(scope, obj, vp - obj->slots, name, sizeof name);
#endif
            thing = next_thing;
            flagp = next_flagp;
        }
        if (thing) {
            /*
             * thing came from the last unmarked GC-thing slot and we
             * can optimize tail recursion.
             *
             * Since we already know that there is enough C stack space,
             * we clear shouldCheckRecursion to avoid extra checking in
             * RECURSION_TOO_DEEP.
             */
            shouldCheckRecursion = JS_FALSE;
            goto on_tail_recursion;
        }
        break;

#ifdef DEBUG
      case GCX_STRING:
        str = (JSString *)thing;
        JS_ASSERT(!JSSTRING_IS_DEPENDENT(str));
        break;
#endif

      case GCX_MUTABLE_STRING:
        str = (JSString *)thing;
        if (!JSSTRING_IS_DEPENDENT(str))
            break;
        thing = JSSTRDEP_BASE(str);
        flagp = js_GetGCThingFlags(thing);
        if (*flagp & GCF_MARK)
            break;
#ifdef GC_MARK_DEBUG
        strcpy(name, "base");
#endif
        /* Fallthrough to code to deal with the tail recursion. */

      on_tail_recursion:
#ifdef GC_MARK_DEBUG
        /*
         * Do not eliminate C recursion when debugging to allow
         * js_MarkNamedGCThing to build a full dump of live GC
         * things.
         */
        GC_MARK(cx, thing, name);
        break;
#else
        /* Eliminate tail recursion for the last unmarked child. */
        JS_ASSERT(*flagp != GCF_FINAL);
        METER(++tailCallNesting);
        *flagp |= GCF_MARK;
        goto start;
#endif

#if JS_HAS_XML_SUPPORT
      case GCX_NAMESPACE:
        if (RECURSION_TOO_DEEP())
            goto add_to_unscanned_bag;
        js_MarkXMLNamespace(cx, (JSXMLNamespace *)thing);
        break;

      case GCX_QNAME:
        if (RECURSION_TOO_DEEP())
            goto add_to_unscanned_bag;
        js_MarkXMLQName(cx, (JSXMLQName *)thing);
        break;

      case GCX_XML:
        if (RECURSION_TOO_DEEP())
            goto add_to_unscanned_bag;
        js_MarkXML(cx, (JSXML *)thing);
        break;
#endif
      add_to_unscanned_bag:
        AddThingToUnscannedBag(cx->runtime, thing, flagp);
        break;
    }
