#ifdef SIXPACK_BENCHMARK_WIN32
if(benchmark)
    return benchmark_speed(compress_level, input_file);
  else
#endif
    return pack_file(compress_level, input_file, output_file);
