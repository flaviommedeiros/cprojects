const clicmd_t cmdTable[] = {
    { "aux", "feature_name auxflag or blank for list", cliAux },
    { "cmix", "design custom mixer", cliCMix },
    { "defaults", "reset to defaults and reboot", cliDefaults },
    { "dump", "print configurable settings in a pastable form", cliDump },
    { "exit", "", cliExit },
    { "feature", "list or -val or val", cliFeature },
#ifdef GPS
    { "gpspassthrough", "passthrough gps to serial", cliGpsPassthrough },
#endif
    { "help", "", cliHelp },
    { "map", "mapping of rc channel order", cliMap },
    { "mixer", "mixer name or list", cliMixer },
    { "motor", "get/set motor output value", cliMotor },
    { "profile", "index (0 to 2)", cliProfile },
    { "save", "save and reboot", cliSave },
    { "servo", "edit servo configuration", cliServo },
    { "set", "name=value or blank or * for list", cliSet },
    { "smix", "design custom servo mixer", cliServoMix },
    { "status", "show system status", cliStatus },
    { "version", "", cliVersion },
};
