if (children == 3 || FIB6_SUBTREE(fn)
#ifdef CONFIG_IPV6_SUBTREES
		    /* Subtree root (i.e. fn) may have one child */
		    || (children && fn->fn_flags&RTN_ROOT)
#endif
		    ) {
			fn->leaf = fib6_find_prefix(net, fn);
#if RT6_DEBUG >= 2
			if (fn->leaf==NULL) {
				WARN_ON(!fn->leaf);
				fn->leaf = net->ipv6.ip6_null_entry;
			}
#endif
			atomic_inc(&fn->leaf->rt6i_ref);
			return fn->parent;
		}
