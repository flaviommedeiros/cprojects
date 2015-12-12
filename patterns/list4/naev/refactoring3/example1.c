switch (c) {
         case 'd':
            /* Does nothing, datapath is parsed earlier. */
            break;
         case 'f':
            conf.fullscreen = 1;
            break;
         case 'F':
            conf.fps_max = atoi(optarg);
            break;
         case 'V':
            conf.vsync = 1;
            break;
         case 'j':
            conf.joystick_ind = atoi(optarg);
            break;
         case 'J':
            conf.joystick_nam = strdup(optarg);
            break;
         case 'W':
            conf.width = atoi(optarg);
            conf.explicit_dim = 1;
            break;
         case 'H':
            conf.height = atoi(optarg);
            conf.explicit_dim = 1;
            break;
         case 'M':
            conf.nosound = 1;
            break;
         case 'S':
            conf.nosound = 0;
            break;
         case 'm':
            conf.music = atof(optarg);
            break;
         case 's':
            conf.sound = atof(optarg);
            break;
         case 'G':
            nebu_forceGenerate();
            break;
         case 'N':
            if (conf.ndata != NULL)
               free(conf.ndata);
            conf.ndata = NULL;
            break;
#ifdef DEBUGGING
         case 'D':
            conf.devmode = 1;
            LOG("Enabling developer mode.");
            break;

         case 'C':
            conf.devcsv = 1;
            LOG("Will generate CSV output.");
            break;
#endif /* DEBUGGING */

         case 'v':
            /* by now it has already displayed the version */
            exit(EXIT_SUCCESS);
         case 'h':
            print_usage(argv);
            exit(EXIT_SUCCESS);
      }
