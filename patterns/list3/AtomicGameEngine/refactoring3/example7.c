switch ( field->location )
    {
    case T1_FIELD_LOCATION_FONT_INFO:
      dummy_object = &face->type1.font_info;
      objects      = &dummy_object;
      max_objects  = 0;

      if ( blend )
      {
        objects     = (void**)blend->font_infos;
        max_objects = blend->num_designs;
      }
      break;

    case T1_FIELD_LOCATION_FONT_EXTRA:
      dummy_object = &face->type1.font_extra;
      objects      = &dummy_object;
      max_objects  = 0;
      break;

    case T1_FIELD_LOCATION_PRIVATE:
      dummy_object = &face->type1.private_dict;
      objects      = &dummy_object;
      max_objects  = 0;

      if ( blend )
      {
        objects     = (void**)blend->privates;
        max_objects = blend->num_designs;
      }
      break;

    case T1_FIELD_LOCATION_BBOX:
      dummy_object = &face->type1.font_bbox;
      objects      = &dummy_object;
      max_objects  = 0;

      if ( blend )
      {
        objects     = (void**)blend->bboxes;
        max_objects = blend->num_designs;
      }
      break;

    case T1_FIELD_LOCATION_LOADER:
      dummy_object = loader;
      objects      = &dummy_object;
      max_objects  = 0;
      break;

    case T1_FIELD_LOCATION_FACE:
      dummy_object = face;
      objects      = &dummy_object;
      max_objects  = 0;
      break;

#ifndef T1_CONFIG_OPTION_NO_MM_SUPPORT
    case T1_FIELD_LOCATION_BLEND:
      dummy_object = face->blend;
      objects      = &dummy_object;
      max_objects  = 0;
      break;
#endif

    default:
      dummy_object = &face->type1;
      objects      = &dummy_object;
      max_objects  = 0;
    }
