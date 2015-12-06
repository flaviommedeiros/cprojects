switch (obj->type) {
	    case XPATH_NODESET:
	    case XPATH_XSLT_TREE:
		if (obj->nodesetval != NULL) {
		    if (obj->boolval) {
			/*
			* It looks like the @boolval is used for
			* evaluation if this an XSLT Result Tree Fragment.
			* TODO: Check if this assumption is correct.
			*/
			obj->type = XPATH_XSLT_TREE; /* just for debugging */
			xmlXPathFreeValueTree(obj->nodesetval);
			obj->nodesetval = NULL;
		    } else if ((obj->nodesetval->nodeMax <= 40) &&
			(XP_CACHE_WANTS(cache->nodesetObjs,
					cache->maxNodeset)))
		    {
			XP_CACHE_ADD(cache->nodesetObjs, obj);
			goto obj_cached;
		    } else {
			xmlXPathFreeNodeSet(obj->nodesetval);
			obj->nodesetval = NULL;
		    }
		}
		break;
	    case XPATH_STRING:
		if (obj->stringval != NULL)
		    xmlFree(obj->stringval);

		if (XP_CACHE_WANTS(cache->stringObjs, cache->maxString)) {
		    XP_CACHE_ADD(cache->stringObjs, obj);
		    goto obj_cached;
		}
		break;
	    case XPATH_BOOLEAN:
		if (XP_CACHE_WANTS(cache->booleanObjs, cache->maxBoolean)) {
		    XP_CACHE_ADD(cache->booleanObjs, obj);
		    goto obj_cached;
		}
		break;
	    case XPATH_NUMBER:
		if (XP_CACHE_WANTS(cache->numberObjs, cache->maxNumber)) {
		    XP_CACHE_ADD(cache->numberObjs, obj);
		    goto obj_cached;
		}
		break;
#ifdef LIBXML_XPTR_ENABLED
	    case XPATH_LOCATIONSET:
		if (obj->user != NULL) {
		    xmlXPtrFreeLocationSet(obj->user);
		}
		goto free_obj;
#endif
	    default:
		goto free_obj;
	}
