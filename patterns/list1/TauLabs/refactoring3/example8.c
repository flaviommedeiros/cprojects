switch (Token)
            {
                case TokenStringConstant:       pc->LexValue.Typ = pc->CharPtrType; break;
                case TokenIdentifier:           pc->LexValue.Typ = NULL; break;
                case TokenIntegerConstant:      pc->LexValue.Typ = &pc->LongType; break;
                case TokenCharacterConstant:    pc->LexValue.Typ = &pc->CharType; break;
#ifndef NO_FP
                case TokenFPConstant:           pc->LexValue.Typ = &pc->FPType; break;
#endif
                default: break;
            }
