if(Curl_inet_pton(AF_INET, conn->host.name, &addr)
#ifdef ENABLE_IPV6
       || Curl_inet_pton(AF_INET6, conn->host.name, &addr6)
#endif
      ) {
      schannel_cred.dwFlags |= SCH_CRED_NO_SERVERNAME_CHECK;
      infof(data, "schannel: using IP address, SNI is being disabled by "
                  "disabling the servername check against the "
                  "subject names in server certificates.\n");
    }
