if((nameptr->state == STATE_UNUSED)
#if RESOLV_SUPPORTS_RECORD_EXPIRATION
      || (nameptr->state == STATE_DONE && clock_seconds() > nameptr->expiration)
#endif /* RESOLV_SUPPORTS_RECORD_EXPIRATION */
    ) {
      lseqi = i;
      lseq = 255;
    } else if(seqno - nameptr->seqno > lseq) {
      lseq = seqno - nameptr->seqno;
      lseqi = i;
    }
