#if defined(__NTVIS__)
if( cnt<0 && WSAENOBUFS == WSAGetLastError()) 
#else
		if( cnt<0 && errno == ENOBUFS )  
#endif /* __NTVIS__ */
		{
			delay(18000);
			errno = 0;
			goto again;
		}
