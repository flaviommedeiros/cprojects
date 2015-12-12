static const int frame_extra_sizes[16] = {
  [1]	= -1, /* sizeof(((struct frame *)0)->un.fmt1), */
  [2]	= sizeof(((struct frame *)0)->un.fmt2),
  [3]	= sizeof(((struct frame *)0)->un.fmt3),
#ifdef CONFIG_COLDFIRE
  [4]	= 0,
#else
  [4]	= sizeof(((struct frame *)0)->un.fmt4),
#endif
  [5]	= -1, /* sizeof(((struct frame *)0)->un.fmt5), */
  [6]	= -1, /* sizeof(((struct frame *)0)->un.fmt6), */
  [7]	= sizeof(((struct frame *)0)->un.fmt7),
  [8]	= -1, /* sizeof(((struct frame *)0)->un.fmt8), */
  [9]	= sizeof(((struct frame *)0)->un.fmt9),
  [10]	= sizeof(((struct frame *)0)->un.fmta),
  [11]	= sizeof(((struct frame *)0)->un.fmtb),
  [12]	= -1, /* sizeof(((struct frame *)0)->un.fmtc), */
  [13]	= -1, /* sizeof(((struct frame *)0)->un.fmtd), */
  [14]	= -1, /* sizeof(((struct frame *)0)->un.fmte), */
  [15]	= -1, /* sizeof(((struct frame *)0)->un.fmtf), */
};
