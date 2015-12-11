#ifdef UA_EXTERNAL_NAMESPACES
if(!isExternal[i])
#endif
            Service_AddReferences_single(server, session, &request->referencesToAdd[i]);
