#ifdef UA_EXTERNAL_NAMESPACES
if(!isExternal[i])
#endif
    		Service_TranslateBrowsePathsToNodeIds_single(server, session, &request->browsePaths[i],
                                                         &response->results[i]);
