IoMethodTable methodTable[] = {
		{"setKeyFile", IoSecureServer_setKeyFile},
		//doc SecureServer setKeyFile(path) Sets the key file. Returns self.
		
		{"setCertFile", IoSecureServer_setCertFile},
		//doc SecureServer setCertFile(path) Sets the certificate file. Returns self.
		
		{"setCAFile", IoSecureServer_setCAFile},
		//doc SecureServer setCAFile(path) Sets the CA file. Returns self.
		
		{"setCRLFile", IoSecureServer_setCRLFile},
		//doc SecureServer setCRLFile(path) Sets the CRL file. Returns self.
		
		{"useTLS", IoSecureServer_useTLS},
		//doc SecureServer useTLS Returns useTLS value.

		{"useDTLS", IoSecureServer_useDTLS},
		//doc SecureServer useDTLS Returns useDTLS value.

		{"setRequiresClientCertificate", IoSecureServer_setRequiresClientCertificate},
		//doc SecureServer setRequiresClientCertificate(aBool) Sets the requires client certificate attribute. Returns self.
		
		{"tlsWrap", IoSecureServer_tlsWrap},
		//doc SecureServer tlsWrap Returns tlsWrap value.
		
		#ifdef DTLS_IMPLEMENTED
		{"dtlsWrap", IoSecureServer_dtlsWrap},
		//doc SecureServer dtlsWrap Returns dtlsWrap value.
		
		{"udpRecvIP", IoSecureServer_udpRecvIP},
		//doc SecureServer udpRecvIP Returns udpRecvIP value.
		
		{"dispatchUdp", IoSecureServer_dispatchUDP},
		//doc SecureServer dispatchUdp Returns dispatchUdp value.
		
		#endif
		{NULL, NULL}
		};
