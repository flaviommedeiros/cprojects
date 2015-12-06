switch (Val->Typ->Base)
    {
        case TypeInt:             return (long)Val->Val->Integer;
        case TypeChar:            return (long)Val->Val->Character;
        case TypeShort:           return (long)Val->Val->ShortInteger;
        case TypeLong:            return (long)Val->Val->LongInteger;
        case TypeUnsignedInt:     return (long)Val->Val->UnsignedInteger;
        case TypeUnsignedShort:   return (long)Val->Val->UnsignedShortInteger;
        case TypeUnsignedLong:    return (long)Val->Val->UnsignedLongInteger;
        case TypeUnsignedChar:    return (long)Val->Val->UnsignedCharacter;
        case TypePointer:         return (long)Val->Val->Pointer;
#ifndef NO_FP
        case TypeFP:              return (long)Val->Val->FP;
#endif
        default:                  return 0;
    }
