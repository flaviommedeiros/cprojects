switch(rgui->menu_type)
   {
#ifdef HAVE_SHADER_MANAGER
      case SHADER_CHOICE:
         strlcpy(extensions, EXT_SHADERS, sizeof(extensions));
         strlcpy(comment, "INFO - Select a shader.", sizeof(comment));
         break;
      case CGP_CHOICE:
         strlcpy(extensions, EXT_CGP_PRESETS, sizeof(extensions));
         strlcpy(comment, "INFO - Select a CGP file.", sizeof(comment));
         break;
#endif
      case INPUT_PRESET_CHOICE:
         strlcpy(extensions, EXT_INPUT_PRESETS, sizeof(extensions));
         strlcpy(comment, "INFO - Select an input preset.", sizeof(comment));
         break;
      case BORDER_CHOICE:
         strlcpy(extensions, EXT_IMAGES, sizeof(extensions));
         strlcpy(comment, "INFO - Select a border image file.", sizeof(comment));
         break;
      case LIBRETRO_CHOICE:
         strlcpy(extensions, EXT_EXECUTABLES, sizeof(extensions));
         strlcpy(comment, "INFO - Select a Libretro core.", sizeof(comment));
         break;
   }
