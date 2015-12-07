if (ret != 0 && ret != EINTR &&
#ifdef ETIME
			    ret != ETIME &&
#endif
			    ret != ETIMEDOUT) {
				(void)pthread_mutex_unlock(&mutexp->u.m.mutex);
				goto err;
			}
