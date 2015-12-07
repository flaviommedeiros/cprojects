if (_wbufq_non_empty(c)
#ifdef TCP_CONNECT_WAIT
			|| (c->flags&F_CONN_PENDING) 
#endif /* TCP_CONNECT_WAIT */
			){
			if (unlikely(_wbufq_add(c, buf, len)<0)){
				if (likely(!locked)) lock_release(&c->write_lock);
				n=-1;
				goto error;
			}
			if (likely(!locked)) lock_release(&c->write_lock);
			n=len;
			goto end;
		}
