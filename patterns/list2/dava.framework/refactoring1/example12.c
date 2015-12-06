if (ret != 0)
        xmlRelaxNGDumpValidError(ctxt);
#ifdef DEBUG
    else if (ctxt->errNr != 0) {
        ctxt->error(ctxt->userData,
                    "%d Extra error messages left on stack !\n",
                    ctxt->errNr);
        xmlRelaxNGDumpValidError(ctxt);
    }
#endif
