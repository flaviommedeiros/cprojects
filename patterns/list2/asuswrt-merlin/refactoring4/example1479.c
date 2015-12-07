#if 0
if (gateway_needed)
    argv_printf_cat (&argv, "%s", gateway);
  else
    argv_printf_cat (&argv, "-iface %s", device);
