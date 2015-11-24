if(recvreq->req_match_received &&
            recvreq->req_bytes_received >= recvreq->req_recv.req_bytes_packed &&
#if PML_BFO
                        (0 == recvreq->req_events) && lock_recv_request(recvreq)) {
#else /* PML_BFO */
            lock_recv_request(recvreq)) {
#endif /* PML_BFO */
        recv_request_pml_complete(recvreq);
        return true;
    }
