if (children == 3 || FIB6_SUBTREE(fn)
#ifdef CONFIG_IPV6_SUBTREES
		    /* Subtree root (i.e. fn) may have one child */
		    || (children && fn->fn_flags&RTN_ROOT)
#endif
		    ) {
			fn->leaf = fib6_find_prefix(fn);
#if RT6_DEBUG >= 2
			if (fn->leaf==NULL) {
				BUG_TRAP(fn->leaf);
				fn->leaf = &ip6_null_entry;
			}
#endif
			atomic_inc(&fn->leaf->rt6i_ref);
			return fn->parent;
		}