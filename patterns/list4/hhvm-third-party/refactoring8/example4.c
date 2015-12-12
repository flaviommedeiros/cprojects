static int SLJIT_CALL do_callout(struct jit_arguments* arguments, PUBL(callout_block) *callout_block, pcre_uchar **jit_ovector)
{
const pcre_uchar *begin = arguments->begin;
int *offset_vector = arguments->offsets;
int offset_count = arguments->offset_count;
int i;

if (PUBL(callout) == NULL)
  return 0;

callout_block->version = 2;
callout_block->callout_data = arguments->callout_data;

/* Offsets in subject. */
callout_block->subject_length = arguments->end - arguments->begin;
callout_block->start_match = (pcre_uchar*)callout_block->subject - arguments->begin;
callout_block->current_position = (pcre_uchar*)callout_block->offset_vector - arguments->begin;
#if defined COMPILE_PCRE8
callout_block->subject = (PCRE_SPTR)begin;
#elif defined COMPILE_PCRE16
callout_block->subject = (PCRE_SPTR16)begin;
#elif defined COMPILE_PCRE32
callout_block->subject = (PCRE_SPTR32)begin;
#endif

/* Convert and copy the JIT offset vector to the offset_vector array. */
callout_block->capture_top = 0;
callout_block->offset_vector = offset_vector;
for (i = 2; i < offset_count; i += 2)
  {
  offset_vector[i] = jit_ovector[i] - begin;
  offset_vector[i + 1] = jit_ovector[i + 1] - begin;
  if (jit_ovector[i] >= begin)
    callout_block->capture_top = i;
  }

callout_block->capture_top = (callout_block->capture_top >> 1) + 1;
if (offset_count > 0)
  offset_vector[0] = -1;
if (offset_count > 1)
  offset_vector[1] = -1;
return (*PUBL(callout))(callout_block);
}
