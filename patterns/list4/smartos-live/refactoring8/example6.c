JSErrorFormatString JSFile_ErrorFormatString[JSFileErr_Limit] = {
#if JSFILE_HAS_DFLT_MSG_STRINGS
#define MSG_DEF(name, number, count, exception, format) \
    { format, count },
#else
#define MSG_DEF(name, number, count, exception, format) \
    { NULL, count },
#endif
#include "jsfile.msg"
#undef MSG_DEF
};
