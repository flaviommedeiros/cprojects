void *os_exports[][3] = {
  {"","GetAttributeString", GetAttributeString},
#if !NewspeakVM
  {"","win32JoystickDebugInfo", win32JoystickDebugInfo},
  {"","win32JoystickDebugPrintRawValues", win32JoystickDebugPrintRawValues},
  {"","win32JoystickDebugPrintAlternativeValues", win32JoystickDebugPrintAlternativeValues},
#endif
  {"","win32DebugPrintSocketState", win32DebugPrintSocketState},
  {"","primitivePluginBrowserReady", primitivePluginBrowserReady},
  {"","primitivePluginRequestURLStream", primitivePluginRequestURLStream},
  {"","primitivePluginRequestURL", primitivePluginRequestURL},
  {"","primitivePluginPostURL", primitivePluginPostURL},
  {"","primitivePluginRequestFileHandle", primitivePluginRequestFileHandle},
  {"","primitivePluginDestroyRequest", primitivePluginDestroyRequest},
  {"","primitivePluginRequestState", primitivePluginRequestState},
  {"","printf", printf},
  {"","stWindow", &stWindow},
  {"","firstMessageHook", &firstMessageHook},
  {"","preMessageHook", &preMessageHook},
  {"","fUseOpenGL", &fUseOpenGL},
  {NULL,NULL, NULL}
};
