if((-1 != data->req.size) &&
       (data->req.size != *ftp->bytecountp) &&
#ifdef CURL_DO_LINEEND_CONV
       /* Most FTP servers don't adjust their file SIZE response for CRLFs, so
        * we'll check to see if the discrepancy can be explained by the number
        * of CRLFs we've changed to LFs.
        */
       ((data->req.size + data->state.crlf_conversions) !=
        *ftp->bytecountp) &&
#endif /* CURL_DO_LINEEND_CONV */
       (data->req.maxdownload != *ftp->bytecountp)) {
      failf(data, "Received only partial file: %" FORMAT_OFF_T " bytes",
            *ftp->bytecountp);
      result = CURLE_PARTIAL_FILE;
    }
    else if(!ftpc->dont_check &&
            !*ftp->bytecountp &&
            (data->req.size>0)) {
      failf(data, "No data was received!");
      result = CURLE_FTP_COULDNT_RETR_FILE;
    }
