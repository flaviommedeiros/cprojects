if (found != NULL 
#ifndef CONFIG_NF_CONNTRACK_SUPPORT
		     && (found_ct = tuplehash_to_ctrack(found)) != NULL
#else
		     && (found_ct = nf_ct_tuplehash_to_ctrack(found)) != NULL
#endif
		     && 0 == memcmp(&conn->tuple,&tuple,sizeof(tuple)) 
		     && found_ct->proto.tcp.state != TCP_CONNTRACK_TIME_WAIT) {
			/* Just to be sure we have it only once in the list.
			   We should'nt see tuples twice unless someone hooks this
			   into a table without "-p tcp --syn" */
			addit = 0;
		}
