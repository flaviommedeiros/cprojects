if (p == 0 &&
#ifndef HAVE_FTRUNCATE
		    !(i > vdp->meta_last_pgno &&
		    (F_ISSET(pip, VRFY_IS_ALLZEROES) || pip->type == P_HASH)) &&
#endif
		    !(dbp->type == DB_HASH && pip->type == P_INVALID)) {
			/*
			 * It is OK for unreferenced hash buckets to be
			 * marked invalid and unreferenced.
			 */
			EPRINT((env,
			    "Page %lu: unreferenced page", (u_long)i));
			isbad = 1;
		}
