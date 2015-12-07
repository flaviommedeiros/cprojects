#ifdef CONFIG_AP
if (wpa_s->ap_iface) {
			pos += ap_ctrl_iface_wpa_get_status(wpa_s, pos,
							    end - pos,
							    verbose);
		} else
#endif /* CONFIG_AP */
		pos += wpa_sm_get_status(wpa_s->wpa, pos, end - pos, verbose);
