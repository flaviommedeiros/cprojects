static dllfunc_t freetypefuncs[] =
{
	{ "FT_New_Size", ( void **)&q_FT_New_Size },
	{ "FT_Activate_Size", ( void **)&q_FT_Activate_Size },
	{ "FT_Set_Pixel_Sizes", ( void **)&q_FT_Set_Pixel_Sizes },
	{ "FT_Done_Size", ( void **)&q_FT_Done_Size },
	{ "FT_Get_Char_Index", ( void **)&q_FT_Get_Char_Index },
	{ "FT_Get_Kerning", ( void **)&q_FT_Get_Kerning },
	{ "FT_Load_Glyph", ( void **)&q_FT_Load_Glyph },
	{ "FT_New_Memory_Face", ( void **)&q_FT_New_Memory_Face },
	{ "FT_Done_Face", ( void **)&q_FT_Done_Face },
	{ "FT_Init_FreeType", ( void **)&q_FT_Init_FreeType },
	{ "FT_Done_FreeType", ( void **)&q_FT_Done_FreeType },
#ifndef FT_MULFIX_INLINED
	{ "FT_MulFix", ( void **)&q_FT_MulFix },
#endif
	{ NULL, NULL },
};
