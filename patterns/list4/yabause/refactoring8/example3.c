SoundInterface_struct *SNDCoreList[] = {
&SNDDummy,
&SNDAudioTrack,
#ifdef HAVE_OPENSL
&SNDOpenSL,
#endif
NULL
};
