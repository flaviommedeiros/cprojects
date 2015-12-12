#ifdef XML_DTD
if (entity->is_param) {
    int tok = XmlPrologTok(internalEncoding, textStart, textEnd, &next);
    result = doProlog(parser, internalEncoding, textStart, textEnd, tok, 
                      next, &next, XML_FALSE);
  }
  else 
#endif /* XML_DTD */
    result = doContent(parser, tagLevel, internalEncoding, textStart, 
                       textEnd, &next, XML_FALSE);
