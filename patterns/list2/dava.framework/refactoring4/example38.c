#if (PY_VERSION_HEX < 0x02020000)
if (!PyArg_ParseTuple(args,(char *)"|O:own",&val))
#else
  if (!PyArg_UnpackTuple(args, (char *)"own", 0, 1, &val))
#endif
    {
      return NULL;
    }
  else
    {
      SwigPyObject *sobj = (SwigPyObject *)v;
      PyObject *obj = PyBool_FromLong(sobj->own);
      if (val) {
#ifdef METH_NOARGS
        if (PyObject_IsTrue(val)) {
          SwigPyObject_acquire(v);
        } else {
          SwigPyObject_disown(v);
        }
#else
        if (PyObject_IsTrue(val)) {
          SwigPyObject_acquire(v,args);
        } else {
          SwigPyObject_disown(v,args);
        }
#endif
      }
      return obj;
    }
