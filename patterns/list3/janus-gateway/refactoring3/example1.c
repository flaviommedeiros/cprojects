switch(m->m_type) {
				case sdp_media_audio:
					g_snprintf(buffer, 512, "a=mid:%s\r\n", handle->audio_mid ? handle->audio_mid : "audio");
					break;
				case sdp_media_video:
					g_snprintf(buffer, 512, "a=mid:%s\r\n", handle->video_mid ? handle->video_mid : "video");
					break;
#ifdef HAVE_SCTP
				case sdp_media_application:
					/* FIXME sctpmap and webrtc-datachannel should be dynamic */
					g_snprintf(buffer, 512, "a=mid:%s\r\na=sctpmap:5000 webrtc-datachannel 16\r\n",
						handle->data_mid ? handle->data_mid : "data");
					break;
#endif
				default:
					break;
			}
