#ifdef XML_DTD
if (!isParamEntity && _dtd)
#else
  if (_dtd)
#endif /* XML_DTD */
    dtdDestroy(_dtd, (XML_Bool)!parentParser, &parser->m_mem);
