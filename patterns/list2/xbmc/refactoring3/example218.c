switch (wParam) {
#ifdef WINAMP
		case MAKEWPARAM(IDC_PLAYING, BN_CLICKED):
			playing_info = (IsDlgButtonChecked(hDlg, IDC_PLAYING) == BST_CHECKED);
			if (playing_info)
				updateInfoDialog(current_filename, current_song);
			return TRUE;
#endif
		case MAKEWPARAM(IDC_AUTHOR, EN_CHANGE):
			SendDlgItemMessage(hDlg, IDC_AUTHOR, WM_GETTEXT, sizeof(edited_module_info.author), (LPARAM) edited_module_info.author);
			updateSaveButton();
			return TRUE;
		case MAKEWPARAM(IDC_NAME, EN_CHANGE):
			SendDlgItemMessage(hDlg, IDC_NAME, WM_GETTEXT, sizeof(edited_module_info.name), (LPARAM) edited_module_info.name);
			updateSaveButton();
			return TRUE;
		case MAKEWPARAM(IDC_DATE, EN_CHANGE):
			SendDlgItemMessage(hDlg, IDC_DATE, WM_GETTEXT, sizeof(edited_module_info.date), (LPARAM) edited_module_info.date);
			updateSaveButton();
			return TRUE;
		case MAKEWPARAM(IDC_TIME, EN_CHANGE):
			SendDlgItemMessage(hDlg, IDC_TIME, WM_GETTEXT, sizeof(str), (LPARAM) str);
			edited_module_info.durations[edited_song] = ASAP_ParseDuration(str);
			updateSaveButton();
			return TRUE;
		case MAKEWPARAM(IDC_LOOP, BN_CLICKED):
			edited_module_info.loops[edited_song] = (IsDlgButtonChecked(hDlg, IDC_LOOP) == BST_CHECKED);
			updateSaveButton();
			return TRUE;
		case MAKEWPARAM(IDC_SONGNO, CBN_SELCHANGE):
			edited_song = SendDlgItemMessage(hDlg, IDC_SONGNO, CB_GETCURSEL, 0, 0);
			showSongTime();
			return TRUE;
		case MAKEWPARAM(IDC_SAVE, BN_CLICKED):
			saveInfo();
			return TRUE;
		case MAKEWPARAM(IDC_CONVERT, BN_CLICKED):
			convert();
			return TRUE;
		case MAKEWPARAM(IDCANCEL, BN_CLICKED):
			if (infoChanged()) {
				BOOL ok;
				switch (MessageBox(hDlg, can_save ? "Save changes?" : "Convert to SAP?", "ASAP", MB_YESNOCANCEL | MB_ICONQUESTION)) {
				case IDYES:
					ok = can_save ? saveInfo() : convert();
					if (!ok)
						return TRUE;
					break;
				case IDCANCEL:
					return TRUE;
				default:
					break;
				}
			}
			DestroyWindow(hDlg);
			infoDialog = NULL;
			return TRUE;
		}
