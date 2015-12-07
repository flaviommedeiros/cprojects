if ( IS_HINTED( loader->load_flags ) &&

#ifdef TT_USE_BYTECODE_INTERPRETER

             subglyph->flags & WE_HAVE_INSTR &&

#endif

             num_points > start_point )
          TT_Process_Composite_Glyph( loader, start_point, start_contour );
