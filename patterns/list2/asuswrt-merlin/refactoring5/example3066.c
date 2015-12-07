#ifdef XML_DTD
if (entity->is_param) {
    int tok;
    processor = prologProcessor;
    tok = XmlPrologTok(encoding, s, end, &next);
    return doProlog(parser, encoding, s, end, tok, next, nextPtr, 
                    (XML_Bool)!ps_finalBuffer);
  }
  else
#endif /* XML_DTD */
  {
    processor = contentProcessor;
    /* see externalEntityContentProcessor vs contentProcessor */
    return doContent(parser, parentParser ? 1 : 0, encoding, s, end,
                     nextPtr, (XML_Bool)!ps_finalBuffer); 
  }
