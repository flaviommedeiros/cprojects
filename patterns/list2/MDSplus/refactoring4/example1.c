#ifdef _WIN32
if (bind(udpSocket, (SOCKADDR *) & serverAddr, sizeof(serverAddr)) != 0)
#else
  if (bind(udpSocket, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in)) != 0)
#endif
  {
    perror("Cannot bind socket\n");
    return 0;
  }
