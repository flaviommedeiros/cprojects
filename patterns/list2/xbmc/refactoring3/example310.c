switch (stream.getStreamType())
  {
    case 0x01: // ISO/IEC 11172 Video
    case 0x02: // ISO/IEC 13818-2 Video
    case 0x80: // ATSC Video MPEG2 (ATSC DigiCipher QAM)
      DEBUGLOG("cStreamdevPatFilter PMT scanner adding PID %d (%s)\n", stream.getPid(), psStreamTypes[stream.getStreamType()]);
      *type = stMPEG2VIDEO;
      return stream.getPid();
    case 0x03: // ISO/IEC 11172 Audio
    case 0x04: // ISO/IEC 13818-3 Audio
      *type   = stMPEG2AUDIO;
      GetLanguage(stream, langs);
      DEBUGLOG("cStreamdevPatFilter PMT scanner adding PID %d (%s) (%s)\n", stream.getPid(), psStreamTypes[stream.getStreamType()], langs);
      return stream.getPid();
    case 0x0f: // ISO/IEC 13818-7 Audio with ADTS transport syntax
    case 0x11: // ISO/IEC 14496-3 Audio with LATM transport syntax
       *type = stAAC;
       GetLanguage(stream, langs);
       DEBUGLOG("cStreamdevPatFilter PMT scanner: adding PID %d (%s) %s (%s)\n", stream.getPid(), psStreamTypes[stream.getStreamType()], "AAC", langs);
      return stream.getPid();
#if 1
    case 0x07: // ISO/IEC 13512 MHEG
    case 0x08: // ISO/IEC 13818-1 Annex A  DSM CC
    case 0x0a: // ISO/IEC 13818-6 Multiprotocol encapsulation
    case 0x0b: // ISO/IEC 13818-6 DSM-CC U-N Messages
    case 0x0c: // ISO/IEC 13818-6 Stream Descriptors
    case 0x0d: // ISO/IEC 13818-6 Sections (any type, including private data)
    case 0x0e: // ISO/IEC 13818-1 auxiliary
#endif
    case 0x10: // ISO/IEC 14496-2 Visual (MPEG-4)
      DEBUGLOG("cStreamdevPatFilter PMT scanner: Not adding PID %d (%s) (skipped)\n", stream.getPid(), psStreamTypes[stream.getStreamType()]);
      break;
    case 0x1b: // ISO/IEC 14496-10 Video (MPEG-4 part 10/AVC, aka H.264)
      DEBUGLOG("cStreamdevPatFilter PMT scanner adding PID %d (%s)\n", stream.getPid(), psStreamTypes[stream.getStreamType()]);
      *type = stH264;
      return stream.getPid();
    case 0x05: // ISO/IEC 13818-1 private sections
    case 0x06: // ISO/IEC 13818-1 PES packets containing private data
      for (SI::Loop::Iterator it; (d = stream.streamDescriptors.getNext(it)); )
      {
        switch (d->getDescriptorTag())
        {
          case SI::AC3DescriptorTag:
            DEBUGLOG("cStreamdevPatFilter PMT scanner: adding PID %d (%s) %s (%s)\n", stream.getPid(), psStreamTypes[stream.getStreamType()], "AC3", langs);
            *type = stAC3;
            GetLanguage(stream, langs);
            delete d;
            return stream.getPid();
          case SI::EnhancedAC3DescriptorTag:
            DEBUGLOG("cStreamdevPatFilter PMT scanner: adding PID %d (%s) %s (%s)\n", stream.getPid(), psStreamTypes[stream.getStreamType()], "EAC3", langs);
            *type = stEAC3;
            GetLanguage(stream, langs);
            delete d;
            return stream.getPid();
          case SI::DTSDescriptorTag:
            DEBUGLOG("cStreamdevPatFilter PMT scanner: adding PID %d (%s) %s (%s)\n", stream.getPid(), psStreamTypes[stream.getStreamType()], "DTS", langs);
            *type = stDTS;
            GetLanguage(stream, langs);
            delete d;
            return stream.getPid();
          case SI::AACDescriptorTag:
            DEBUGLOG("cStreamdevPatFilter PMT scanner: adding PID %d (%s) %s (%s)\n", stream.getPid(), psStreamTypes[stream.getStreamType()], "AAC", langs);
            *type = stAAC;
            GetLanguage(stream, langs);
            delete d;
            return stream.getPid();
          case SI::TeletextDescriptorTag:
            DEBUGLOG("cStreamdevPatFilter PMT scanner: adding PID %d (%s) %s\n", stream.getPid(), psStreamTypes[stream.getStreamType()], "Teletext");
            *type = stTELETEXT;
            delete d;
            return stream.getPid();
          case SI::SubtitlingDescriptorTag:
          {
            *type               = stDVBSUB;
            *langs              = 0;
            *subtitlingType     = 0;
            *compositionPageId  = 0;
            *ancillaryPageId    = 0;
            SI::SubtitlingDescriptor *sd = (SI::SubtitlingDescriptor *)d;
            SI::SubtitlingDescriptor::Subtitling sub;
            char *s = langs;
            int n = 0;
            for (SI::Loop::Iterator it; sd->subtitlingLoop.getNext(sub, it); )
            {
              if (sub.languageCode[0])
              {
                *subtitlingType     = sub.getSubtitlingType();
                *compositionPageId  = sub.getCompositionPageId();
                *ancillaryPageId    = sub.getAncillaryPageId();
                if (n > 0)
                  *s++ = '+';
                strn0cpy(s, I18nNormalizeLanguageCode(sub.languageCode), MAXLANGCODE1);
                s += strlen(s);
                if (n++ > 1)
                  break;
              }
            }
            delete d;
            DEBUGLOG("cStreamdevPatFilter PMT scanner: adding PID %d (%s) %s\n", stream.getPid(), psStreamTypes[stream.getStreamType()], "DVBSUB");
            return stream.getPid();
          }
          default:
            DEBUGLOG("cStreamdevPatFilter PMT scanner: NOT adding PID %d (%s) %s (%i)\n", stream.getPid(), psStreamTypes[stream.getStreamType()], "UNKNOWN", d->getDescriptorTag());
            break;
        }
        delete d;
      }
      break;
    default:
      /* This following section handles all the cases where the audio track
       * info is stored in PMT user info with stream id >= 0x81
       * we check the registration format identifier to see if it
       * holds "AC-3"
       */
      if (stream.getStreamType() >= 0x81)
      {
        bool found = false;
        for (SI::Loop::Iterator it; (d = stream.streamDescriptors.getNext(it)); )
        {
          switch (d->getDescriptorTag())
          {
            case SI::RegistrationDescriptorTag:
            /* unfortunately libsi does not implement RegistrationDescriptor */
            if (d->getLength() >= 4)
            {
              found = true;
              SI::CharArray rawdata = d->getData();
              if (/*rawdata[0] == 5 && rawdata[1] >= 4 && */
                  rawdata[2] == 'A' && rawdata[3] == 'C' &&
                  rawdata[4] == '-' && rawdata[5] == '3')
              {
                DEBUGLOG("cStreamdevPatFilter PMT scanner: Adding pid %d (type 0x%x) RegDesc len %d (%c%c%c%c)\n",
                            stream.getPid(), stream.getStreamType(), d->getLength(), rawdata[2], rawdata[3], rawdata[4], rawdata[5]);
                *type = stAC3;
                delete d;
                return stream.getPid();
              }
            }
            break;
            default:
            break;
          }
          delete d;
        }
        if (!found)
        {
          DEBUGLOG("NOT adding PID %d (type 0x%x) RegDesc not found -> UNKNOWN\n", stream.getPid(), stream.getStreamType());
        }
      }
      DEBUGLOG("cStreamdevPatFilter PMT scanner: NOT adding PID %d (%s) %s\n", stream.getPid(), psStreamTypes[stream.getStreamType()<0x1c?stream.getStreamType():0], "UNKNOWN");
      break;
  }
