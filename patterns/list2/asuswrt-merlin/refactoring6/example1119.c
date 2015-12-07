if (((total % 256) == 0) &&
#ifdef XP_OPTIMIZED_NON_ELEM_COMPARISON
		    (xmlXPathCmpNodesExt(*first, cur) >= 0))
#else
		    (xmlXPathCmpNodes(*first, cur) >= 0)
