switch(style & (UNITY_DISPLAY_STYLE_T)(~UNITY_DISPLAY_RANGE_AUTO))
    {
        case UNITY_DISPLAY_STYLE_HEX8:
        case UNITY_DISPLAY_STYLE_INT8:
        case UNITY_DISPLAY_STYLE_UINT8:
            while (elements--)
            {
                if (*(UNITY_PTR_ATTRIBUTE const _US8*)ptr_exp != *(UNITY_PTR_ATTRIBUTE const _US8*)ptr_act)
                {
                    UnityTestResultsFailBegin(lineNumber);
                    UnityPrint(UnityStrElement);
                    UnityPrintNumberByStyle((num_elements - elements - 1), UNITY_DISPLAY_STYLE_UINT);
                    UnityPrint(UnityStrExpected);
                    UnityPrintNumberByStyle(*(UNITY_PTR_ATTRIBUTE const _US8*)ptr_exp, style);
                    UnityPrint(UnityStrWas);
                    UnityPrintNumberByStyle(*(UNITY_PTR_ATTRIBUTE const _US8*)ptr_act, style);
                    UnityAddMsgIfSpecified(msg);
                    UNITY_FAIL_AND_BAIL;
                }
                ptr_exp = (UNITY_INTERNAL_PTR)((_UP)ptr_exp + 1);
                ptr_act = (UNITY_INTERNAL_PTR)((_UP)ptr_act + 1);
            }
            break;
        case UNITY_DISPLAY_STYLE_HEX16:
        case UNITY_DISPLAY_STYLE_INT16:
        case UNITY_DISPLAY_STYLE_UINT16:
            while (elements--)
            {
                if (*(UNITY_PTR_ATTRIBUTE const _US16*)ptr_exp != *(UNITY_PTR_ATTRIBUTE const _US16*)ptr_act)
                {
                    UnityTestResultsFailBegin(lineNumber);
                    UnityPrint(UnityStrElement);
                    UnityPrintNumberByStyle((num_elements - elements - 1), UNITY_DISPLAY_STYLE_UINT);
                    UnityPrint(UnityStrExpected);
                    UnityPrintNumberByStyle(*(UNITY_PTR_ATTRIBUTE const _US16*)ptr_exp, style);
                    UnityPrint(UnityStrWas);
                    UnityPrintNumberByStyle(*(UNITY_PTR_ATTRIBUTE const _US16*)ptr_act, style);
                    UnityAddMsgIfSpecified(msg);
                    UNITY_FAIL_AND_BAIL;
                }
                ptr_exp = (UNITY_INTERNAL_PTR)((_UP)ptr_exp + 2);
                ptr_act = (UNITY_INTERNAL_PTR)((_UP)ptr_act + 2);
            }
            break;
#ifdef UNITY_SUPPORT_64
        case UNITY_DISPLAY_STYLE_HEX64:
        case UNITY_DISPLAY_STYLE_INT64:
        case UNITY_DISPLAY_STYLE_UINT64:
            while (elements--)
            {
                if (*(UNITY_PTR_ATTRIBUTE const _US64*)ptr_exp != *(UNITY_PTR_ATTRIBUTE const _US64*)ptr_act)
                {
                    UnityTestResultsFailBegin(lineNumber);
                    UnityPrint(UnityStrElement);
                    UnityPrintNumberByStyle((num_elements - elements - 1), UNITY_DISPLAY_STYLE_UINT);
                    UnityPrint(UnityStrExpected);
                    UnityPrintNumberByStyle(*(UNITY_PTR_ATTRIBUTE const _US64*)ptr_exp, style);
                    UnityPrint(UnityStrWas);
                    UnityPrintNumberByStyle(*(UNITY_PTR_ATTRIBUTE const _US64*)ptr_act, style);
                    UnityAddMsgIfSpecified(msg);
                    UNITY_FAIL_AND_BAIL;
                }
                ptr_exp = (UNITY_INTERNAL_PTR)((_UP)ptr_exp + 8);
                ptr_act = (UNITY_INTERNAL_PTR)((_UP)ptr_act + 8);
            }
            break;
#endif
        default:
            while (elements--)
            {
                if (*(UNITY_PTR_ATTRIBUTE const _US32*)ptr_exp != *(UNITY_PTR_ATTRIBUTE const _US32*)ptr_act)
                {
                    UnityTestResultsFailBegin(lineNumber);
                    UnityPrint(UnityStrElement);
                    UnityPrintNumberByStyle((num_elements - elements - 1), UNITY_DISPLAY_STYLE_UINT);
                    UnityPrint(UnityStrExpected);
                    UnityPrintNumberByStyle(*(UNITY_PTR_ATTRIBUTE const _US32*)ptr_exp, style);
                    UnityPrint(UnityStrWas);
                    UnityPrintNumberByStyle(*(UNITY_PTR_ATTRIBUTE const _US32*)ptr_act, style);
                    UnityAddMsgIfSpecified(msg);
                    UNITY_FAIL_AND_BAIL;
                }
                ptr_exp = (UNITY_INTERNAL_PTR)((_UP)ptr_exp + 4);
                ptr_act = (UNITY_INTERNAL_PTR)((_UP)ptr_act + 4);
            }
            break;
    }
