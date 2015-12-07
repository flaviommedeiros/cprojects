if (PyLong_CheckExact(text) ||
#if PY_MAJOR_VERSION < 3
	    PyInt_CheckExact(text) ||
#endif
	    PyFloat_CheckExact(text) || PyBool_Check(text) ||
	    text == Py_None)
		return PyObject_CallFunctionObjArgs(markup, text, NULL);
