if(!(data->set.opt_no_body) && (k->size != -1) &&
       (k->bytecount != k->size) &&
#ifdef CURL_DO_LINEEND_CONV
       /* Most FTP servers don't adjust their file SIZE response for CRLFs,
          so we'll check to see if the discrepancy can be explained
          by the number of CRLFs we've changed to LFs.
       */
       (k->bytecount != (k->size + data->state.crlf_conversions)) &&
#endif /* CURL_DO_LINEEND_CONV */
       !data->req.newurl) {
      failf(data, "transfer closed with %" FORMAT_OFF_T
            " bytes remaining to read",
            k->size - k->bytecount);
      return CURLE_PARTIAL_FILE;
    }
    else if(!(data->set.opt_no_body) &&
            k->chunk &&
            (conn->chunk.state != CHUNK_STOP)) {
      /*
       * In chunked mode, return an error if the connection is closed prior to
       * the empty (terminiating) chunk is read.
       *
       * The condition above used to check for
       * conn->proto.http->chunk.datasize != 0 which is true after reading
       * *any* chunk, not just the empty chunk.
       *
       */
      failf(data, "transfer closed with outstanding read data remaining");
      return CURLE_PARTIAL_FILE;
    }
