switch(id)
    {
      case MM_MIDI_MAPPER: return "MIDI Mapper";
      case MM_WAVE_MAPPER: return "Wave Mapper";
      case MM_SNDBLST_MIDIOUT: return "Sound Blaster MIDI output port";
      case MM_SNDBLST_MIDIIN: return "Sound Blaster MIDI input port";
      case MM_SNDBLST_SYNTH: return "Sound Blaster internal synthesizer";
      case MM_SNDBLST_WAVEOUT: return "Sound Blaster waveform output";
      case MM_SNDBLST_WAVEIN: return "Sound Blaster waveform input";
      case MM_ADLIB: return "Ad Lib-compatible synthesizer";
      case MM_MPU401_MIDIOUT: return "MPU401-compatible MIDI output port";
      case MM_MPU401_MIDIIN: return "MPU401-compatible MIDI input port";
      case MM_PC_JOYSTICK: return "Joystick adapter";

#ifdef MM_DIGITAL_BBA
      case MM_DIGITAL_BBA: return "DEC BaseBoard Audio for ALPHA-AXP";
#endif /* MM_DIGITAL_BBA */

#ifdef MM_DIGITAL_J300AUDIO
      case MM_DIGITAL_J300AUDIO: return "DEC J300 TC option card";
#endif /* MM_DIGITAL_J300AUDIO */

#ifdef MM_DIGITAL_MSB
      case MM_DIGITAL_MSB: return "DEC Microsoft Sound Board compatible card";
#endif /* MM_DIGITAL_MSB */

#ifdef MM_DIGITAL_IMAADPCM
      case MM_DIGITAL_IMAADPCM: return "DEC IMA ADPCM ACM driver";
#endif /* MM_DIGITAL_IMAADPCM */
    }
