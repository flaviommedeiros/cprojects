if (!dtd->standalone
#ifdef XML_DTD
          && !paramEntityParsing
#endif /* XML_DTD */
          && notStandaloneHandler
          && !notStandaloneHandler(handlerArg))
        return XML_ERROR_NOT_STANDALONE;
