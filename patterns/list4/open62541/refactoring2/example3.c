#ifdef UA_EXTERNAL_NAMESPACES
if(!isExternal[i])
#endif
            Service_AddNodes_single(server, session, &request->nodesToAdd[i], &response->results[i]);
