#ifdef HAVE_XINPUT
if (!is_xinput_pad)
#endif
   {
      autoconfig_params_t params = {{0}};

      strlcpy(settings->input.device_names[g_joypad_cnt],
            dinput_joypad_name(g_joypad_cnt),
            sizeof(settings->input.device_names[g_joypad_cnt]));

      params.idx = g_joypad_cnt;
      strlcpy(params.name, dinput_joypad_name(g_joypad_cnt), sizeof(params.name));
      strlcpy(params.display_name, dinput_joypad_friendly_name(g_joypad_cnt), sizeof(params.driver));
      strlcpy(params.driver, dinput_joypad.ident, sizeof(params.driver));
      params.vid = dinput_joypad_vid(g_joypad_cnt);
      params.pid = dinput_joypad_pid(g_joypad_cnt);
      input_config_autoconfigure_joypad(&params);
      settings->input.pid[g_joypad_cnt] = params.pid;
      settings->input.vid[g_joypad_cnt] = params.vid;
   }
