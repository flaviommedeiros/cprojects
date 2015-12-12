#ifdef USE_SUBEXP_CALL
if (IS_ENCLOSE_CALLED(node)) {
      len = SIZE_OP_MEMORY_START_PUSH + tlen
	  + SIZE_OP_CALL + SIZE_OP_JUMP + SIZE_OP_RETURN;
      if (BIT_STATUS_AT(reg->bt_mem_end, node->regnum))
	len += (IS_ENCLOSE_RECURSION(node)
		? SIZE_OP_MEMORY_END_PUSH_REC : SIZE_OP_MEMORY_END_PUSH);
      else
	len += (IS_ENCLOSE_RECURSION(node)
		? SIZE_OP_MEMORY_END_REC : SIZE_OP_MEMORY_END);
    }
    else
#endif
    {
      if (BIT_STATUS_AT(reg->bt_mem_start, node->regnum))
	len = SIZE_OP_MEMORY_START_PUSH;
      else
	len = SIZE_OP_MEMORY_START;

      len += tlen + (BIT_STATUS_AT(reg->bt_mem_end, node->regnum)
		     ? SIZE_OP_MEMORY_END_PUSH : SIZE_OP_MEMORY_END);
    }
