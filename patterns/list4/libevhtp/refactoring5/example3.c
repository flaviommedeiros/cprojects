#ifdef USE_SUBEXP_CALL
if (IS_ENCLOSE_CALLED(node)) {
      if (BIT_STATUS_AT(reg->bt_mem_end, node->regnum))
	r = add_opcode(reg, (IS_ENCLOSE_RECURSION(node)
			     ? OP_MEMORY_END_PUSH_REC : OP_MEMORY_END_PUSH));
      else
	r = add_opcode(reg, (IS_ENCLOSE_RECURSION(node)
			     ? OP_MEMORY_END_REC : OP_MEMORY_END));

      if (r) return r;
      r = add_mem_num(reg, node->regnum);
      if (r) return r;
      r = add_opcode(reg, OP_RETURN);
    }
    else
#endif
    {
      if (BIT_STATUS_AT(reg->bt_mem_end, node->regnum))
	r = add_opcode(reg, OP_MEMORY_END_PUSH);
      else
	r = add_opcode(reg, OP_MEMORY_END);
      if (r) return r;
      r = add_mem_num(reg, node->regnum);
    }
