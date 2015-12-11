static
  const T1_FieldRec  t1_keywords[] =
  {

#include "t1tokens.h"

    /* now add the special functions... */
    T1_FIELD_CALLBACK( "FontMatrix",           parse_font_matrix,
                       T1_FIELD_DICT_FONTDICT )
    T1_FIELD_CALLBACK( "Encoding",             parse_encoding,
                       T1_FIELD_DICT_FONTDICT )
    T1_FIELD_CALLBACK( "Subrs",                parse_subrs,
                       T1_FIELD_DICT_PRIVATE )
    T1_FIELD_CALLBACK( "CharStrings",          parse_charstrings,
                       T1_FIELD_DICT_PRIVATE )
    T1_FIELD_CALLBACK( "Private",              parse_private,
                       T1_FIELD_DICT_FONTDICT )

#ifndef T1_CONFIG_OPTION_NO_MM_SUPPORT
    T1_FIELD_CALLBACK( "BlendDesignPositions", parse_blend_design_positions,
                       T1_FIELD_DICT_FONTDICT )
    T1_FIELD_CALLBACK( "BlendDesignMap",       parse_blend_design_map,
                       T1_FIELD_DICT_FONTDICT )
    T1_FIELD_CALLBACK( "BlendAxisTypes",       parse_blend_axis_types,
                       T1_FIELD_DICT_FONTDICT )
    T1_FIELD_CALLBACK( "WeightVector",         parse_weight_vector,
                       T1_FIELD_DICT_FONTDICT )
    T1_FIELD_CALLBACK( "BuildCharArray",       parse_buildchar,
                       T1_FIELD_DICT_PRIVATE )
#endif

    { 0, T1_FIELD_LOCATION_CID_INFO, T1_FIELD_TYPE_NONE, 0, 0, 0, 0, 0, 0 }
  };
