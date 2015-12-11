#ifdef USE_LCD_FSMC
if (gfx->data.type == JSGRAPHICSTYPE_FSMC) {
      lcdSetCallbacks_FSMC(gfx);
    } else
#endif
    if (gfx->data.type == JSGRAPHICSTYPE_ARRAYBUFFER) {
      lcdSetCallbacks_ArrayBuffer(gfx);
    } else if (gfx->data.type == JSGRAPHICSTYPE_JS) {
      lcdSetCallbacks_JS(gfx);
    } else {
      jsExceptionHere(JSET_INTERNALERROR, "Unknown graphics type\n");
      assert(0);
    }
