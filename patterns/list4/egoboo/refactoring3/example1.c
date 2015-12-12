switch (err) {
        case GL_NO_ERROR:
            error = "no error";
            break;
        case GL_INVALID_ENUM:
            error = "invalid enum";
            break;
        case GL_INVALID_VALUE:
            error = "invalid value";
            break;
        case GL_INVALID_OPERATION:
            error = "invalid operation";
            break;
        case GL_STACK_OVERFLOW:
            error = "stack overflow";
            break;
        case GL_STACK_UNDERFLOW:
            error = "stack underflow";
            break;
        case GL_OUT_OF_MEMORY:
            error = "out of memory";
            break;
#ifdef GL_INVALID_FRAMEBUFFER_OPERATION
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "invalid framebuffer operation";
            break;
#endif
        default:
            error = "(unknown error)";
            break;
    }
