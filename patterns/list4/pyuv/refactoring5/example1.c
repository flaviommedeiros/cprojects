#ifndef PYUV_WINDOWS
if (Py_FileSystemDefaultEncoding)
        return PyUnicode_AsEncodedString(unicode, Py_FileSystemDefaultEncoding, "surrogateescape");
    else
#endif
        return PyUnicode_EncodeUTF8(PyUnicode_AS_UNICODE(unicode), PyUnicode_GET_SIZE(unicode), "surrogateescape");
