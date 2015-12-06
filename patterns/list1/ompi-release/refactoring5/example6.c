#ifdef VT_ETIMESYNC
if( m_syncMethod == METHOD_ENHANCED )
      {
         const int64_t & offset = it->second->sync_offset;
         const double & drift = it->second->sync_drift;

         return (uint64_t)( offset + (uint64_t)( drift * (double)time ) );
      }
      else
#endif // VT_ETIMESYNC
      {
         const int64_t * ltime = it->second->ltime;
         const int64_t * offset = it->second->offset;
 
         const double a = ( (double)( (int64_t)( ltime[1] -  time ) ) /
                            (double)( (int64_t)( ltime[1]  - ltime[0] ) ) );
         return
            (uint64_t)( time + offset[1] - (int64_t)( a * (double)offset[1] ) +
                        (int64_t)( a * (double)offset[0] ) - m_minStartTime );
      
      }
