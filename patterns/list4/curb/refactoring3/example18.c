switch (code) {
    case CURLE_OK:                      /* 0 */
      exclz = eCurlErrOK;
      break;
    case CURLE_UNSUPPORTED_PROTOCOL:    /* 1 */
      exclz = eCurlErrUnsupportedProtocol;
      break;
    case CURLE_FAILED_INIT:             /* 2 */
      exclz = eCurlErrFailedInit;
      break;
    case CURLE_URL_MALFORMAT:           /* 3 */
      exclz = eCurlErrMalformedURL;
      break;
#ifdef HAVE_CURLE_NOT_BUILT_IN
    case CURLE_NOT_BUILT_IN:            /* 4 - [was obsoleted in August 2007 for 7.17.0, reused in April 2011 for 7.21.5] */
      exclz = eCurlErrNotBuiltIn;
      break;
#else
    case CURLE_URL_MALFORMAT_USER:      /* 4 (NOT USED) */
      exclz = eCurlErrMalformedURLUser;
      break;
#endif
    case CURLE_COULDNT_RESOLVE_PROXY:   /* 5 */
      exclz = eCurlErrProxyResolution;
      break;
    case CURLE_COULDNT_RESOLVE_HOST:    /* 6 */
      exclz = eCurlErrHostResolution;
      break;
    case CURLE_COULDNT_CONNECT:         /* 7 */
      exclz = eCurlErrConnectFailed;
      break;
    case CURLE_FTP_WEIRD_SERVER_REPLY:  /* 8 */
      exclz = eCurlErrFTPWeirdReply;
      break;
    case CURLE_FTP_ACCESS_DENIED:       /* 9 denied due to lack of access. */
      exclz = eCurlErrFTPAccessDenied;
      break;
    case CURLE_FTP_USER_PASSWORD_INCORRECT: /* 10 */
      exclz = eCurlErrFTPBadPassword;
      break;
    case CURLE_FTP_WEIRD_PASS_REPLY:    /* 11 */
      exclz = eCurlErrFTPWeirdPassReply;
      break;
    case CURLE_FTP_WEIRD_USER_REPLY:    /* 12 */
      exclz = eCurlErrFTPWeirdUserReply;
      break;
    case CURLE_FTP_WEIRD_PASV_REPLY:    /* 13 */
      exclz = eCurlErrFTPWeirdPasvReply;
      break;
    case CURLE_FTP_WEIRD_227_FORMAT:    /* 14 */
      exclz = eCurlErrFTPWeird227Format;
      break;
    case CURLE_FTP_CANT_GET_HOST:       /* 15 */
      exclz = eCurlErrFTPCantGetHost;
      break;
    case CURLE_FTP_CANT_RECONNECT:      /* 16 */
      exclz = eCurlErrFTPCantReconnect;
      break;
    case CURLE_FTP_COULDNT_SET_BINARY:  /* 17 */
      exclz = eCurlErrFTPCouldntSetBinary;
      break;
    case CURLE_PARTIAL_FILE:            /* 18 */
      exclz = eCurlErrPartialFile;
      break;
    case CURLE_FTP_COULDNT_RETR_FILE:   /* 19 */
      exclz = eCurlErrFTPCouldntRetrFile;
      break;
    case CURLE_FTP_WRITE_ERROR:         /* 20 */
      exclz = eCurlErrFTPWrite;
      break;
    case CURLE_FTP_QUOTE_ERROR:         /* 21 */
      exclz = eCurlErrFTPQuote;
      break;
    case CURLE_HTTP_RETURNED_ERROR:     /* 22 */
      exclz = eCurlErrHTTPFailed;
      break;
    case CURLE_WRITE_ERROR:             /* 23 */
      exclz = eCurlErrWriteError;
      break;
    case CURLE_MALFORMAT_USER:          /* 24 - NOT USED */
      exclz = eCurlErrMalformedUser;
      break;
    case CURLE_FTP_COULDNT_STOR_FILE:   /* 25 - failed FTP upload */
      exclz = eCurlErrFTPCouldntStorFile;
      break;
    case CURLE_READ_ERROR:              /* 26 - could open/read from file */
      exclz = eCurlErrReadError;
      break;
    case CURLE_OUT_OF_MEMORY:           /* 27 */
      exclz = eCurlErrOutOfMemory;
      break;
    case CURLE_OPERATION_TIMEOUTED:     /* 28 - the timeout time was reached */
      exclz = eCurlErrTimeout;
      break;
    case CURLE_FTP_COULDNT_SET_ASCII:   /* 29 - TYPE A failed */
      exclz = eCurlErrFTPCouldntSetASCII;
      break;
    case CURLE_FTP_PORT_FAILED:         /* 30 - FTP PORT operation failed */
      exclz = eCurlErrFTPPortFailed;
      break;
    case CURLE_FTP_COULDNT_USE_REST:    /* 31 - the REST command failed */
      exclz = eCurlErrFTPCouldntUseRest;
      break;
    case CURLE_FTP_COULDNT_GET_SIZE:    /* 32 - the SIZE command failed */
      exclz = eCurlErrFTPCouldntGetSize;
      break;
    case CURLE_HTTP_RANGE_ERROR:        /* 33 - RANGE "command" didn't work */
      exclz = eCurlErrHTTPRange;
      break;
    case CURLE_HTTP_POST_ERROR:         /* 34 */
      exclz = eCurlErrHTTPPost;
      break;
    case CURLE_SSL_CONNECT_ERROR:       /* 35 - wrong when connecting with SSL */
      exclz = eCurlErrSSLConnectError;
      break;
    case CURLE_BAD_DOWNLOAD_RESUME:     /* 36 - couldn't resume download */
      exclz = eCurlErrBadResume;
      break;
    case CURLE_FILE_COULDNT_READ_FILE:  /* 37 */
      exclz = eCurlErrFileCouldntRead;
      break;
    case CURLE_LDAP_CANNOT_BIND:        /* 38 */
      exclz = eCurlErrLDAPCouldntBind;
      break;
    case CURLE_LDAP_SEARCH_FAILED:      /* 39 */
      exclz = eCurlErrLDAPSearchFailed;
      break;
    case CURLE_LIBRARY_NOT_FOUND:       /* 40 */
      exclz = eCurlErrLibraryNotFound;
      break;
    case CURLE_FUNCTION_NOT_FOUND:      /* 41 */
      exclz = eCurlErrFunctionNotFound;
      break;
    case CURLE_ABORTED_BY_CALLBACK:     /* 42 */
      exclz = eCurlErrAbortedByCallback;
      break;
    case CURLE_BAD_FUNCTION_ARGUMENT:   /* 43 */
      exclz = eCurlErrBadFunctionArgument;
      break;
    case CURLE_BAD_CALLING_ORDER:       /* 44 - NOT USED */
      exclz = eCurlErrBadCallingOrder;
      break;
    case CURLE_INTERFACE_FAILED:        /* 45 - CURLOPT_INTERFACE failed */
      exclz = eCurlErrInterfaceFailed;
      break;
    case CURLE_BAD_PASSWORD_ENTERED:    /* 46 - NOT USED */
      exclz = eCurlErrBadPasswordEntered;
      break;
    case CURLE_TOO_MANY_REDIRECTS:      /* 47 - catch endless re-direct loops */
      exclz = eCurlErrTooManyRedirects;
      break;
    case CURLE_UNKNOWN_TELNET_OPTION:   /* 48 - User specified an unknown option */
      exclz = eCurlErrTelnetUnknownOption;
      break;
    case CURLE_TELNET_OPTION_SYNTAX:    /* 49 - Malformed telnet option */
      exclz = eCurlErrTelnetBadOptionSyntax;
      break;
#ifdef HAVE_CURLE_OBSOLETE
    case CURLE_OBSOLETE:                /* 50 - NOT USED */
      exclz = eCurlErrObsolete;
      break;
#endif
    case CURLE_SSL_PEER_CERTIFICATE:    /* 51 - peer's certificate wasn't ok */
      exclz = eCurlErrSSLPeerCertificate;
      break;
    case CURLE_GOT_NOTHING:             /* 52 - when this is a specific error */
      exclz = eCurlErrGotNothing;
      break;
    case CURLE_SSL_ENGINE_NOTFOUND:     /* 53 - SSL crypto engine not found */
      exclz = eCurlErrSSLEngineNotFound;
      break;
    case CURLE_SSL_ENGINE_SETFAILED:    /* 54 - can not set SSL crypto engine as default */
      exclz = eCurlErrSSLEngineSetFailed;
      break;
    case CURLE_SEND_ERROR:              /* 55 - failed sending network data */
      exclz = eCurlErrSendError;
      break;
    case CURLE_RECV_ERROR:              /* 56 - failure in receiving network data */
      exclz = eCurlErrRecvError;
      break;
    case CURLE_SHARE_IN_USE:            /* 57 - share is in use */
      exclz = eCurlErrShareInUse;
      break;
    case CURLE_SSL_CERTPROBLEM:         /* 58 - problem with the local certificate */
      exclz = eCurlErrSSLCertificate;
      break;
    case CURLE_SSL_CIPHER:              /* 59 - couldn't use specified cipher */
      exclz = eCurlErrSSLCipher;
      break;
    case CURLE_SSL_CACERT:              /* 60 - problem with the CA cert (path?) */
      exclz = eCurlErrSSLCACertificate;
      break;
    case CURLE_BAD_CONTENT_ENCODING:    /* 61 - Unrecognized transfer encoding */
      exclz = eCurlErrBadContentEncoding;
      break;
    case CURLE_LDAP_INVALID_URL:        /* 62 - Invalid LDAP URL */
      exclz = eCurlErrLDAPInvalidURL;
      break;
    case CURLE_FILESIZE_EXCEEDED:       /* 63 - Maximum file size exceeded */
      exclz = eCurlErrFileSizeExceeded;
      break;
    case CURLE_FTP_SSL_FAILED:          /* 64 - Requested FTP SSL level failed */
      exclz = eCurlErrFTPSSLFailed;
      break;
#ifdef HAVE_CURLE_SEND_FAIL_REWIND
    case CURLE_SEND_FAIL_REWIND:        /* 65 - Sending the data requires a rewind that failed */
      exclz = eCurlErrSendFailedRewind;
      break;
#endif
#ifdef HAVE_CURLE_SSL_ENGINE_INITFAILED
    case CURLE_SSL_ENGINE_INITFAILED:   /* 66 - failed to initialise ENGINE */
      exclz = eCurlErrSSLEngineInitFailed;
      break;
#endif
#ifdef HAVE_CURLE_LOGIN_DENIED
    case CURLE_LOGIN_DENIED:            /* 67 - user, password or similar was not accepted and we failed to login */
      exclz = eCurlErrLoginDenied;
      break;
#endif

      // recent additions, may not be present in all supported versions
#ifdef HAVE_CURLE_TFTP_NOTFOUND
    case CURLE_TFTP_NOTFOUND:           /* 68 - file not found on server */
      exclz = eCurlErrTFTPNotFound;
      break;
#endif
#ifdef HAVE_CURLE_TFTP_PERM
    case CURLE_TFTP_PERM:               /* 69 - permission problem on server */
      exclz = eCurlErrTFTPPermission;
      break;
#endif
#ifdef HAVE_CURLE_TFTP_DISKFULL
    case CURLE_TFTP_DISKFULL:           /* 70 - out of disk space on server */
      exclz = eCurlErrTFTPDiskFull;
      break;
#endif
#ifdef HAVE_CURLE_TFTP_ILLEGAL
    case CURLE_TFTP_ILLEGAL:            /* 71 - Illegal TFTP operation */
      exclz = eCurlErrTFTPIllegalOperation;
      break;
#endif
#ifdef HAVE_CURLE_TFTP_UNKNOWNID
    case CURLE_TFTP_UNKNOWNID:          /* 72 - Unknown transfer ID */
      exclz = eCurlErrTFTPUnknownID;
      break;
#endif
#ifdef HAVE_CURLE_TFTP_EXISTS
    case CURLE_TFTP_EXISTS:             /* 73 - File already exists */
      exclz = eCurlErrTFTPFileExists;
      break;
#endif
#ifdef HAVE_CURLE_TFTP_NOSUCHUSER
    case CURLE_TFTP_NOSUCHUSER:         /* 74 - No such user */
      exclz = eCurlErrTFTPNotFound;
      break;
#endif
#ifdef HAVE_CURLE_CONV_FAILED
    case CURLE_CONV_FAILED:             /* 75 - conversion failed */
      exclz = eCurlErrConvFailed;
      break;
#endif
#ifdef HAVE_CURLE_CONV_REQD
    case CURLE_CONV_REQD:               /* 76 - caller must register conversion
                                                callbacks using curl_easy_setopt options
                                                CURLOPT_CONV_FROM_NETWORK_FUNCTION,
                                                CURLOPT_CONV_TO_NETWORK_FUNCTION, and
                                                CURLOPT_CONV_FROM_UTF8_FUNCTION */
      exclz = eCurlErrConvReqd;
      break;
#endif
#ifdef HAVE_CURLE_SSL_CACERT_BADFILE
    case CURLE_SSL_CACERT_BADFILE:      /* 77 - could not load CACERT file, missing
                                                or wrong format */
      exclz = eCurlErrSSLCacertBadfile;
      break;
#endif
#ifdef  HAVE_CURLE_REMOTE_FILE_NOT_FOUND
    case CURLE_REMOTE_FILE_NOT_FOUND:   /* 78 - remote file not found */
      exclz = eCurlErrRemoteFileNotFound;
      break;
#endif
#ifdef  HAVE_CURLE_SSH
    case CURLE_SSH:                     /* 79 - error from the SSH layer, somewhat
                                    generic so the error message will be of
                                    interest when this has happened */
      exclz = eCurlErrSSH;
      break;
#endif
#ifdef  HAVE_CURLE_SSL_SHUTDOWN_FAILED
    case CURLE_SSL_SHUTDOWN_FAILED:     /* 80 - Failed to shut down the SSL
                                    connection */
      exclz = eCurlErrSSLShutdownFailed;
      break;
#endif
#ifdef  HAVE_CURLE_AGAIN
    case CURLE_AGAIN:                   /* 81 - socket is not ready for send/recv,
                                    wait till it's ready and try again (Added
                                    in 7.18.2) */
      exclz = eCurlErrAgain;
      break;
#endif
#ifdef  HAVE_CURLE_SSL_CRL_BADFILE
    case CURLE_SSL_CRL_BADFILE:         /* 82 - could not load CRL file, missing or
                                    wrong format (Added in 7.19.0) */
      exclz = eCurlErrSSLCRLBadfile;
      break;
#endif
#ifdef  HAVE_CURLE_SSL_ISSUER_ERROR
    case CURLE_SSL_ISSUER_ERROR:        /* 83 - Issuer check failed.  (Added in
                                    7.19.0) */
      exclz = eCurlErrSSLIssuerError;
      break;
#endif
    default:
      exclz = eCurlErrError;
      exmsg = "Unknown error result from libcurl";
  }
