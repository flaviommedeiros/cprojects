if ( function_->type == FUNCTION_BUILTIN )
    {
        BUILTIN_FUNCTION const * const f = (BUILTIN_FUNCTION *)function_;
        if ( function_->formal_arguments )
            argument_list_check( function_->formal_arguments,
                function_->num_formal_arguments, function_, frame );
        return f->func( frame, f->flags );
    }

#ifdef HAVE_PYTHON
    else if ( function_->type == FUNCTION_PYTHON )
    {
        PYTHON_FUNCTION * f = (PYTHON_FUNCTION *)function_;
        return call_python_function( f, frame );
    }
#endif
