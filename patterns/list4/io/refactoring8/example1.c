IoMethodTable methodTable[] = {
		{"rawCertificate", IoSecureSocket_rawCertificate},
		//doc SecureSocket rawCertificate Returns rawCertificate.

		{"rawPeerCertificate", IoSecureSocket_rawPeerCertificate},
		//doc SecureSocket rawPeerCertificate Returns rawPeerCertificate.

		{"descriptorId", IoSecureSocket_descriptorId},
		//doc SecureSocket descriptorId Returns descriptorId.
		
		{"isConnected", IoSecureSocket_isConnected},
		//doc SecureSocket isConnected Returns true if socket is connected, false otherwise.
		
		{"isOpen", IoSecureSocket_isOpen},
		//doc SecureSocket isOpen Returns true if socket is open, false otherwise.
		
		{"asyncConnectBIO", IoSecureSocket_asyncConnectBIO},
		//doc SecureSocket asyncConnectBIO Performs asyncConnectBIO.

		{"asyncConnectSSL", IoSecureSocket_asyncConnectSSL},
		//doc SecureSocket asyncConnectSSL Performs asyncConnectSSL.

		{"rawValidate", IoSecureSocket_rawValidate},
		//doc SecureSocket rawValidate Performs rawValidate.
		
		{"wantsRead", IoSecureSocket_wantsRead},
		//doc SecureSocket wantsRead Returns wantsRead attribute.

		{"wantsWrite", IoSecureSocket_wantsWrite},
		//doc SecureSocket wantsWrite Returns IoSecureSocket_wantsWrite attribute.

		{"asyncAccept", IoSecureSocket_asyncAcceptSSL},
		//doc SecureSocket asyncAccept Accept a connection asynchronously.

		{"asyncStreamRead", IoSecureSocket_asyncStreamRead},
		//doc SecureSocket asyncStreamRead Read available data and return it.

		{"asyncWrite", IoSecureSocket_asyncWrite},
		//doc SecureSocket asyncWrite(aSeq) Writes aSeq to the socket. Returns self.
		
		{"shutdown", IoSecureSocket_shutdown},
		//doc SecureSocket shutdown close the socket connection. Returns self.

		{"setSocketReadBufferSize", IoSecureSocket_setSocketReadBufferSize},
		//doc SecureSocket setSocketReadBufferSize(numberOfBytes) Sets read buffer size. Returns self.
		
		{"setSocketWriteBufferSize", IoSecureSocket_setSocketWriteBufferSize},
		//doc SecureSocket setSocketWriteBufferSize(numberOfBytes)  Sets write buffer size. Returns self.
		
		{"getSocketReadLowWaterMark", IoSecureSocket_getSocketReadLowWaterMark},
		//doc SecureSocket getSocketReadLowWaterMark Returns ReadLowWaterMark attribute.
		
		{"getSocketWriteLowWaterMark", IoSecureSocket_getSocketWriteLowWaterMark},
		//doc SecureSocket getSocketWriteLowWaterMark Returns WriteLowWaterMark attribute.

		{"setSocketReadLowWaterMark", IoSecureSocket_setSocketReadLowWaterMark},
		//doc SecureSocket setSocketReadLowWaterMark(numberOfBytes) Sets read low water mark. Returns self.

		{"setSocketWriteLowWaterMark", IoSecureSocket_setSocketWriteLowWaterMark},
		//doc SecureSocket setSocketWriteLowWaterMark(numberOfBytes)  Sets write low water mark. Returns self.
		
		{"isDatagram", IoSecureSocket_isDatagram},
		//doc SecureSocket isDatagram Returns isDatagram attribute.
		#ifdef DTLS_IMPLEMENTED
		{"asyncUdpRead", IoSecureSocket_asyncUdpRead},
		//doc SecureSocket asyncUdpRead ?

		{"asyncUdpServerRead", IoSecureSocket_asyncUdpServerRead},
		//doc SecureSocket asyncUdpServerRead ?

		{"rbioReady", IoSecureSocket_rbioReady},
		//doc SecureSocket rbioReady Returns rbioReady attribute.

		#endif
		{NULL, NULL}
		};
