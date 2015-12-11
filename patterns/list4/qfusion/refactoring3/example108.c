switch(result)
    {
        case SL_RESULT_SUCCESS: return "Success";
        case SL_RESULT_PRECONDITIONS_VIOLATED: return "Preconditions violated";
        case SL_RESULT_PARAMETER_INVALID: return "Parameter invalid";
        case SL_RESULT_MEMORY_FAILURE: return "Memory failure";
        case SL_RESULT_RESOURCE_ERROR: return "Resource error";
        case SL_RESULT_RESOURCE_LOST: return "Resource lost";
        case SL_RESULT_IO_ERROR: return "I/O error";
        case SL_RESULT_BUFFER_INSUFFICIENT: return "Buffer insufficient";
        case SL_RESULT_CONTENT_CORRUPTED: return "Content corrupted";
        case SL_RESULT_CONTENT_UNSUPPORTED: return "Content unsupported";
        case SL_RESULT_CONTENT_NOT_FOUND: return "Content not found";
        case SL_RESULT_PERMISSION_DENIED: return "Permission denied";
        case SL_RESULT_FEATURE_UNSUPPORTED: return "Feature unsupported";
        case SL_RESULT_INTERNAL_ERROR: return "Internal error";
        case SL_RESULT_UNKNOWN_ERROR: return "Unknown error";
        case SL_RESULT_OPERATION_ABORTED: return "Operation aborted";
        case SL_RESULT_CONTROL_LOST: return "Control lost";
#ifndef __ANDROID__
        case SL_RESULT_READONLY: return "ReadOnly";
        case SL_RESULT_ENGINEOPTION_UNSUPPORTED: return "Engine option unsupported";
        case SL_RESULT_SOURCE_SINK_INCOMPATIBLE: return "Source/Sink incompatible";
#endif // __ANDROID__
    }
