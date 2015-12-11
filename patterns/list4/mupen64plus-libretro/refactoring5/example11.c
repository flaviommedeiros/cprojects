#ifdef RAM_OFFSET
if (c)
           {
              if (th >= 0) emit_readword_indexed(0, addr, th);
              emit_readword_indexed(4, addr, tl);
           }
