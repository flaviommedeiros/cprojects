static const struct mix_ent mix_devs[SOUND_MIXER_NRDEVICES] = {
	{ 2, 6, 1,  7 }, /* SOUND_MIXER_VOLUME   */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_BASS     */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_TREBLE   */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_SYNTH    */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_PCM      */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_SPEAKER  */
	{ 0, 4, 6, 31 }, /* SOUND_MIXER_LINE     */
	{ 2, 6, 4,  3 }, /* SOUND_MIXER_MIC      */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_CD       */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_IMIX     */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_ALTPCM   */
#if 0
	{ 3, 7, 0, 10 }, /* SOUND_MIXER_RECLEV   */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_IGAIN    */
#else
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_RECLEV   */
	{ 3, 7, 0,  7 }, /* SOUND_MIXER_IGAIN    */
#endif
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_OGAIN    */
	{ 0, 4, 1, 31 }, /* SOUND_MIXER_LINE1    */
	{ 1, 5, 6, 31 }, /* SOUND_MIXER_LINE2    */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_LINE3    */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_DIGITAL1 */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_DIGITAL2 */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_DIGITAL3 */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_PHONEIN  */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_PHONEOUT */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_VIDEO    */
	{ 0, 0, 0,  0 }, /* SOUND_MIXER_RADIO    */
	{ 0, 0, 0,  0 }  /* SOUND_MIXER_MONITOR  */
};
