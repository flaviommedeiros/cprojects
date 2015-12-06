if ( have_scale &&
#ifdef TT_CONFIG_OPTION_COMPONENT_OFFSET_SCALED
           !( subglyph->flags & UNSCALED_COMPONENT_OFFSET ) )
#else
            ( subglyph->flags & SCALED_COMPONENT_OFFSET )
