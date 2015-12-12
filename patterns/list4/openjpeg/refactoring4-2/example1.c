#ifdef SERVER
while(FCGI_Accept() >= 0)
#else

  char query_string[128];
