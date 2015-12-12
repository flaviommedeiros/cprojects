#ifdef _WIN32
if (dwResult != WSAEADDRNOTAVAIL)
#else
			dwResult = errno;
