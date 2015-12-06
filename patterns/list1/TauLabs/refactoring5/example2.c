#ifndef NO_FP
if (TopValue->Typ == &Parser->pc->FPType)
    {
        /* floating point prefix arithmetic */
        double ResultFP = 0.0;
        
        switch (Op)
        {
            case TokenIncrement:    ResultFP = ExpressionAssignFP(Parser, TopValue, TopValue->Val->FP+1); break;
            case TokenDecrement:    ResultFP = ExpressionAssignFP(Parser, TopValue, TopValue->Val->FP-1); break;
            default:                ProgramFail(Parser, "invalid operation"); break;
        }
        
        ExpressionPushFP(Parser, StackTop, ResultFP);
    }
    else 
#endif
    if (IS_NUMERIC_COERCIBLE(TopValue))
    {
        long ResultInt = 0;
        long TopInt = ExpressionCoerceInteger(TopValue);
        switch (Op)
        {
            case TokenIncrement:            ResultInt = ExpressionAssignInt(Parser, TopValue, TopInt+1, TRUE); break;
            case TokenDecrement:            ResultInt = ExpressionAssignInt(Parser, TopValue, TopInt-1, TRUE); break;
            case TokenRightSquareBracket:   ProgramFail(Parser, "not supported"); break;  /* XXX */
            case TokenCloseBracket:         ProgramFail(Parser, "not supported"); break;  /* XXX */
            default:                        ProgramFail(Parser, "invalid operation"); break;
        }
    
        ExpressionPushInt(Parser, StackTop, ResultInt);
    }
    else if (TopValue->Typ->Base == TypePointer)
    {
        /* pointer postfix arithmetic */
        int Size = TypeSize(TopValue->Typ->FromType, 0, TRUE);
        struct Value *StackValue;
        void *OrigPointer = TopValue->Val->Pointer;
        
        if (TopValue->Val->Pointer == NULL)
            ProgramFail(Parser, "invalid use of a NULL pointer");
            
        if (!TopValue->IsLValue) 
            ProgramFail(Parser, "can't assign to this"); 
        
        switch (Op)
        {
            case TokenIncrement:    TopValue->Val->Pointer = (void *)((char *)TopValue->Val->Pointer + Size); break;
            case TokenDecrement:    TopValue->Val->Pointer = (void *)((char *)TopValue->Val->Pointer - Size); break;
            default:                ProgramFail(Parser, "invalid operation"); break;
        }
        
        StackValue = ExpressionStackPushValueByType(Parser, StackTop, TopValue->Typ);
        StackValue->Val->Pointer = OrigPointer;
    }
    else
        ProgramFail(Parser, "invalid operation");
