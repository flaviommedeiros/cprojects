if ((p->Base = (Byte *)alloc->Alloc(alloc, p->AlignOffset + size
        #ifndef PPMD_32BIT
        + UNIT_SIZE
        #endif
        )) == 0)
      return False;
