switch (Op->Common.AmlOpcode)
        {
#ifndef ACPI_NO_METHOD_EXECUTION
        case AML_REGION_OP:
        case AML_DATA_REGION_OP:

            if (Op->Common.AmlOpcode == AML_REGION_OP)
            {
                RegionSpace = (ACPI_ADR_SPACE_TYPE)
                    ((Op->Common.Value.Arg)->Common.Value.Integer);
            }
            else
            {
                RegionSpace = ACPI_ADR_SPACE_DATA_TABLE;
            }

            /*
             * The OpRegion is not fully parsed at this time. The only valid
             * argument is the SpaceId. (We must save the address of the
             * AML of the address and length operands)
             *
             * If we have a valid region, initialize it. The namespace is
             * unlocked at this point.
             *
             * Need to unlock interpreter if it is locked (if we are running
             * a control method), in order to allow _REG methods to be run
             * during AcpiEvInitializeRegion.
             */
            if (WalkState->MethodNode)
            {
                /*
                 * Executing a method: initialize the region and unlock
                 * the interpreter
                 */
                Status = AcpiExCreateRegion (Op->Named.Data,
                    Op->Named.Length, RegionSpace, WalkState);
                if (ACPI_FAILURE (Status))
                {
                    return_ACPI_STATUS (Status);
                }

                AcpiExExitInterpreter ();
            }

            Status = AcpiEvInitializeRegion (
                AcpiNsGetAttachedObject (Node), FALSE);
            if (WalkState->MethodNode)
            {
                AcpiExEnterInterpreter ();
            }

            if (ACPI_FAILURE (Status))
            {
                /*
                 *  If AE_NOT_EXIST is returned, it is not fatal
                 *  because many regions get created before a handler
                 *  is installed for said region.
                 */
                if (AE_NOT_EXIST == Status)
                {
                    Status = AE_OK;
                }
            }
            break;

        case AML_NAME_OP:

            Status = AcpiDsCreateNode (WalkState, Node, Op);
            break;

        case AML_METHOD_OP:
            /*
             * MethodOp PkgLength NameString MethodFlags TermList
             *
             * Note: We must create the method node/object pair as soon as we
             * see the method declaration. This allows later pass1 parsing
             * of invocations of the method (need to know the number of
             * arguments.)
             */
            ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
                "LOADING-Method: State=%p Op=%p NamedObj=%p\n",
                WalkState, Op, Op->Named.Node));

            if (!AcpiNsGetAttachedObject (Op->Named.Node))
            {
                WalkState->Operands[0] = ACPI_CAST_PTR (void, Op->Named.Node);
                WalkState->NumOperands = 1;

                Status = AcpiDsCreateOperands (
                    WalkState, Op->Common.Value.Arg);
                if (ACPI_SUCCESS (Status))
                {
                    Status = AcpiExCreateMethod (
                        Op->Named.Data, Op->Named.Length, WalkState);
                }

                WalkState->Operands[0] = NULL;
                WalkState->NumOperands = 0;

                if (ACPI_FAILURE (Status))
                {
                    return_ACPI_STATUS (Status);
                }
            }
            break;

#endif /* ACPI_NO_METHOD_EXECUTION */

        default:

            /* All NAMED_COMPLEX opcodes must be handled above */
            break;
        }
