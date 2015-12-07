if ((crecp->flags & F_FORWARD) && 
#ifdef HAVE_DNSSEC
		  (((crecp->flags & (F_DNSKEY | F_DS)) == (prot & (F_DNSKEY | F_DS))) || (prot & F_NSIGMATCH)) &&
#endif
		  (crecp->flags & prot) &&
		  hostname_isequal(cache_get_name(crecp), name))
		{
		  if (crecp->flags & (F_HOSTS | F_DHCP | F_CONFIG))
		    {
		      *chainp = crecp;
		      chainp = &crecp->next;
		    }
		  else
		    {
		      cache_unlink(crecp);
		      cache_link(crecp);
		    }
	      	      
		  /* Move all but the first entry up the hash chain
		     this implements round-robin. 
		     Make sure that re-ordering doesn't break the hash-chain
		     order invariants. 
		  */
		  if (insert && (crecp->flags & (F_REVERSE | F_IMMORTAL)) == ins_flags)
		    {
		      *up = crecp->hash_next;
		      crecp->hash_next = *insert;
		      *insert = crecp;
		      insert = &crecp->hash_next;
		    }
		  else
		    {
		      if (!insert && !no_rr)
			{
			  insert = up;
			  ins_flags = crecp->flags & (F_REVERSE | F_IMMORTAL);
			}
		      up = &crecp->hash_next; 
		    }
		}
	      else
		/* case : not expired, incorrect entry. */
		up = &crecp->hash_next;
