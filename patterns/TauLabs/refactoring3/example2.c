switch (Val->Typ->Base)
    {
        case TypeInt:             return (unsigned long)Val->Val->Integer;
        case TypeChar:            return (unsigned long)Val->Val->Character;
        case TypeShort:           return (unsigned long)Val->Val->ShortInteger;
        case TypeLong:            return (unsigned long)Val->Val->LongInteger;
        case TypeUnsignedInt:     return (unsigned long)Val->Val->UnsignedInteger;
        case TypeUnsignedShort:   return (unsigned long)Val->Val->UnsignedShortInteger;
        case TypeUnsignedLong:    return (unsigned long)Val->Val->UnsignedLongInteger;
        case TypeUnsignedChar:    return (unsigned long)Val->Val->UnsignedCharacter;
        case TypePointer:         return (unsigned long)Val->Val->Pointer;
#ifndef NO_FP
        case TypeFP:              return (unsigned long)Val->Val->FP;
#endif
        default:                  return 0;
    }
