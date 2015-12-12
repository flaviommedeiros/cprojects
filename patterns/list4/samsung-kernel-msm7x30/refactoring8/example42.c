static int pcxhr_handle_async_err(struct pcxhr_mgr *mgr, u32 err,
				  enum pcxhr_async_err_src err_src, int pipe,
				  int is_capture)
{
#ifdef CONFIG_SND_DEBUG_VERBOSE
	static char* err_src_name[] = {
		[PCXHR_ERR_PIPE]	= "Pipe",
		[PCXHR_ERR_STREAM]	= "Stream",
		[PCXHR_ERR_AUDIO]	= "Audio"
	};
#endif
	if (err & 0xfff)
		err &= 0xfff;
	else
		err = ((err >> 12) & 0xfff);
	if (!err)
		return 0;
	snd_printdd("CMD_ASYNC : Error %s %s Pipe %d err=%x\n",
		    err_src_name[err_src],
		    is_capture ? "Record" : "Play", pipe, err);
	if (err == 0xe01)
		mgr->async_err_stream_xrun++;
	else if (err == 0xe10)
		mgr->async_err_pipe_xrun++;
	else
		mgr->async_err_other_last = (int)err;
	return 1;
}
