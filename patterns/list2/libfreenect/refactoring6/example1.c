if (
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
            __Pyx_sys_getdefaultencoding_not_ascii &&
#endif
            PyUnicode_Check(o)) {
#if PY_VERSION_HEX < 0x03030000
        char* defenc_c;
        PyObject* defenc = _PyUnicode_AsDefaultEncodedString(o, NULL);
        if (!defenc) return NULL;
        defenc_c = PyBytes_AS_STRING(defenc);
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        {
            char* end = defenc_c + PyBytes_GET_SIZE(defenc);
            char* c;
            for (c = defenc_c; c < end; c++) {
                if ((unsigned char) (*c) >= 128) {
                    PyUnicode_AsASCIIString(o);
                    return NULL;
                }
            }
        }
#endif /*__PYX_DEFAULT_STRING_ENCODING_IS_ASCII*/
        *length = PyBytes_GET_SIZE(defenc);
        return defenc_c;
#else /* PY_VERSION_HEX < 0x03030000 */
        if (PyUnicode_READY(o) == -1) return NULL;
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        if (PyUnicode_IS_ASCII(o)) {
            *length = PyUnicode_GET_LENGTH(o);
            return PyUnicode_AsUTF8(o);
        } else {
            PyUnicode_AsASCIIString(o);
            return NULL;
        }
#else /* __PYX_DEFAULT_STRING_ENCODING_IS_ASCII */
        return PyUnicode_AsUTF8AndSize(o, length);
#endif /* __PYX_DEFAULT_STRING_ENCODING_IS_ASCII */
#endif /* PY_VERSION_HEX < 0x03030000 */
    } else
#endif /* __PYX_DEFAULT_STRING_ENCODING_IS_ASCII  || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT */
#if !CYTHON_COMPILING_IN_PYPY
#if PY_VERSION_HEX >= 0x02060000
    if (PyByteArray_Check(o)) {
        *length = PyByteArray_GET_SIZE(o);
        return PyByteArray_AS_STRING(o);
    } else
#endif
#endif
    {
        char* result;
        int r = PyBytes_AsStringAndSize(o, &result, length);
        if (unlikely(r < 0)) {
            return NULL;
        } else {
            return result;
        }
    }
