#ifndef THREAD
if (_gu_db_stack->flags & FLUSH_ON_WRITE)
#endif
    {
#if defined(MSDOS) || defined(__WIN__)
	if (_gu_db_fp_ != stdout && _gu_db_fp_ != stderr) {
	    if (!(freopen(_gu_db_stack->name, "a", _gu_db_fp_))) {
		(void) fprintf(stderr, ERR_OPEN, _gu_db_process_,_gu_db_stack->name);
		fflush(stderr);
		_gu_db_fp_ = stdout;
		_gu_db_stack->out_file = _gu_db_fp_;
		_gu_db_stack->flags |= FLUSH_ON_WRITE;
	    }
	} else
#endif
	{
	    (void) fflush(_gu_db_fp_);
	    if (_gu_db_stack->delay)
		(void) Delay(_gu_db_stack->delay);
	}
    }
