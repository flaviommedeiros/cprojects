switch (mode & 255) {
  case ca_command:
    index = complete_command_list (index, command_pos, command_len, &R);
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_user:
    index = tgl_complete_user_list (TLS, index, command_pos, command_len, &R);    
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_peer:
    index = tgl_complete_peer_list (TLS, index, command_pos, command_len, &R);
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_file_name:
  case ca_file_name_end:
    if (c) { rl_line_buffer[rl_point] = c; }
    R = rl_filename_completion_function (command_pos, state);
    return R;
  case ca_chat:
    index = tgl_complete_chat_list (TLS, index, command_pos, command_len, &R);
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_secret_chat:
    index = tgl_complete_encr_chat_list (TLS, index, command_pos, command_len, &R);
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_modifier:
    index = complete_string_list (modifiers, index, command_pos, command_len, &R);
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
  case ca_msg_string_end:
    if (autocomplete_peer) {
      if (tgl_get_peer_type (autocomplete_peer->id) == TGL_PEER_USER) {
        index = complete_user_command (autocomplete_peer, index, command_pos, command_len, &R);
      }
      if (tgl_get_peer_type (autocomplete_peer->id) == TGL_PEER_CHAT) {
        index = complete_chat_command (autocomplete_peer, index, command_pos, command_len, &R);
      }
    }
    if (autocomplete_id) {
      struct tgl_message *M = tgl_message_get (TLS, autocomplete_id);
      if (M) {
        if (command_len > 0 && *command_pos == '/') {
          tgl_peer_t *P = tgl_peer_get (TLS, M->from_id);
          if (P) {
            index = complete_user_command (autocomplete_peer, index, command_pos, command_len, &R);
          }
        } else {
          index = complete_spec_message_answer (M, index, command_pos, command_len, &R);
        }
      }
    }
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
#ifndef DISABLE_EXTF
  case ca_extf:
    index = tglf_extf_autocomplete (TLS, text, len, index, &R, rl_line_buffer, rl_point);
    if (c) { rl_line_buffer[rl_point] = c; }
    return R;
#endif
  default:
    if (c) { rl_line_buffer[rl_point] = c; }
    return 0;
  }
