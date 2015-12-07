#ifndef NOPRIVPORTS
if (conn_authen == 0)
#endif
        {
        strcpy(conn_credent[s].username, preq->rq_user);
        strcpy(conn_credent[s].hostname, preq->rq_host);

        /* time stamp just for the record */

        conn_credent[s].timestamp = time(NULL);

        pthread_mutex_lock(svr_conn[s].cn_mutex);
        svr_conn[s].cn_authen = PBS_NET_CONN_AUTHENTICATED;
        pthread_mutex_unlock(svr_conn[s].cn_mutex);
        }
