switch (Token)
    {
        case TokenIntType: *Typ = Unsigned ? &pc->UnsignedIntType : &pc->IntType; break;
        case TokenShortType: *Typ = Unsigned ? &pc->UnsignedShortType : &pc->ShortType; break;
        case TokenCharType: *Typ = Unsigned ? &pc->UnsignedCharType : &pc->CharType; break;
        case TokenLongType: *Typ = Unsigned ? &pc->UnsignedLongType : &pc->LongType; break;
#ifndef NO_FP
        case TokenFloatType: case TokenDoubleType: *Typ = &pc->FPType; break;
#endif
        case TokenVoidType: *Typ = &pc->VoidType; break;
        
        case TokenStructType: case TokenUnionType: 
            if (*Typ != NULL)
                ProgramFail(Parser, "bad type declaration");
                
            TypeParseStruct(Parser, Typ, Token == TokenStructType);
            break;

        case TokenEnumType:
            if (*Typ != NULL)
                ProgramFail(Parser, "bad type declaration");
                
            TypeParseEnum(Parser, Typ);
            break;
        
        case TokenIdentifier:
            /* we already know it's a typedef-defined type because we got here */
            VariableGet(pc, Parser, LexerValue->Val->Identifier, &VarValue);
            *Typ = VarValue->Val->Typ;
            break;

        default: ParserCopy(Parser, &Before); return FALSE;
    }
