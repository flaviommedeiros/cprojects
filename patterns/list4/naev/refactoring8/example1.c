static struct option long_options[] = {
      { "datapath", required_argument, 0, 'd' },
      { "fullscreen", no_argument, 0, 'f' },
      { "fps", required_argument, 0, 'F' },
      { "vsync", no_argument, 0, 'V' },
      { "joystick", required_argument, 0, 'j' },
      { "Joystick", required_argument, 0, 'J' },
      { "width", required_argument, 0, 'W' },
      { "height", required_argument, 0, 'H' },
      { "mute", no_argument, 0, 'M' },
      { "sound", no_argument, 0, 'S' },
      { "mvol", required_argument, 0, 'm' },
      { "svol", required_argument, 0, 's' },
      { "generate", no_argument, 0, 'G' },
      { "nondata", no_argument, 0, 'N' },
#ifdef DEBUGGING
      { "devmode", no_argument, 0, 'D' },
      { "devcsv", no_argument, 0, 'C' },
#endif /* DEBUGGING */
      { "help", no_argument, 0, 'h' },
      { "version", no_argument, 0, 'v' },
      { NULL, 0, 0, 0 } };
