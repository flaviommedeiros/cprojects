switch (LOWORD(wParam)) {
		case IDM_QUIT:
#if 1/* ­§I¹ */
			SetTimer ( NULL, 0, 20000, forced_exit );
#endif
			w32g_message_set (W32G_SYN_QUIT);
			break;
		case IDM_START:
			w32g_message_set (W32G_SYN_START);
			break;
		case IDM_STOP:
			w32g_message_set (W32G_SYN_STOP);
			break;
		case IDM_SYSTEM_RESET:
			w32g_message_set (W32G_SYN_SYSTEM_RESET);
			break;
		case IDM_GM_SYSTEM_RESET:
			w32g_message_set (W32G_SYN_GM_SYSTEM_RESET);
			break;
		case IDM_GS_SYSTEM_RESET:
			w32g_message_set (W32G_SYN_GS_SYSTEM_RESET);
			break;
		case IDM_XG_SYSTEM_RESET:
			w32g_message_set (W32G_SYN_XG_SYSTEM_RESET);
			break;
		case	IDM_CHANGE_GM_SYSTEM:
			w32g_message_set (W32G_SYN_CHANGE_GM_SYSTEM);
			break;
		case	IDM_CHANGE_GS_SYSTEM:
			w32g_message_set (W32G_SYN_CHANGE_GS_SYSTEM);
			break;
		case IDM_CHANGE_XG_SYSTEM:
			w32g_message_set (W32G_SYN_CHANGE_XG_SYSTEM);
			break;
		case IDM_CHANGE_DEFAULT_SYSTEM:
			w32g_message_set (W32G_SYN_CHANGE_DEFAULT_SYSTEM);
			break;
		case IDM_PREFERENCE:
			PrefWndCreate ( w32g_syn.nid_hWnd );
			break;
		case IDM_VERSION:
			VersionWnd ( w32g_syn.nid_hWnd );
			break;
		case IDM_TIMIDITY:
			TiMidityWnd ( w32g_syn.nid_hWnd );
			break;
		case IDM_PROCESS_PRIORITY_LOWEST:
			processPriority = IDLE_PRIORITY_CLASS;
			if ( w32g_syn_status == run ) {
				SetPriorityClass(GetCurrentProcess(), processPriority);
			}
			break;
		case IDM_PROCESS_PRIORITY_BELOW_NORMAL:
			processPriority = BELOW_NORMAL_PRIORITY_CLASS;
			if ( w32g_syn_status == run ) {
				SetPriorityClass(GetCurrentProcess(), processPriority);
			}
			break;
		case IDM_PROCESS_PRIORITY_NORMAL:
			processPriority = NORMAL_PRIORITY_CLASS;
			if ( w32g_syn_status == run ) {
				SetPriorityClass(GetCurrentProcess(), processPriority);
			}
			break;
		case IDM_PROCESS_PRIORITY_ABOVE_NORMAL:
			processPriority = ABOVE_NORMAL_PRIORITY_CLASS;
			if ( w32g_syn_status == run ) {
				SetPriorityClass(GetCurrentProcess(), processPriority);
			}
			break;
		case IDM_PROCESS_PRIORITY_HIGHEST:
			processPriority = HIGH_PRIORITY_CLASS;
			if ( w32g_syn_status == run ) {
				SetPriorityClass(GetCurrentProcess(), processPriority);
			}
			break;
		case IDM_PROCESS_PRIORITY_REALTIME:
			processPriority = REALTIME_PRIORITY_CLASS;
			if ( w32g_syn_status == run ) {
				SetPriorityClass(GetCurrentProcess(), processPriority);
			}
			break;
		case IDM_SYN_THREAD_PRIORITY_LOWEST:
			syn_ThreadPriority = THREAD_PRIORITY_LOWEST;
			if ( w32g_syn_status == run ) {
				SetThreadPriority ( w32g_syn.syn_hThread, syn_ThreadPriority );
			}
			break;
		case IDM_SYN_THREAD_PRIORITY_BELOW_NORMAL:
			syn_ThreadPriority = THREAD_PRIORITY_BELOW_NORMAL;
			if ( w32g_syn_status == run ) {
				SetThreadPriority ( w32g_syn.syn_hThread, syn_ThreadPriority );
			}
			break;
		case IDM_SYN_THREAD_PRIORITY_NORMAL:
			syn_ThreadPriority = THREAD_PRIORITY_NORMAL;
			if ( w32g_syn_status == run ) {
				SetThreadPriority ( w32g_syn.syn_hThread, syn_ThreadPriority );
			}
			break;
		case IDM_SYN_THREAD_PRIORITY_ABOVE_NORMAL:
			syn_ThreadPriority = THREAD_PRIORITY_ABOVE_NORMAL;
			if ( w32g_syn_status == run ) {
				SetThreadPriority ( w32g_syn.syn_hThread, syn_ThreadPriority );
			}
			break;
		case IDM_SYN_THREAD_PRIORITY_HIGHEST:
			syn_ThreadPriority = THREAD_PRIORITY_HIGHEST;
			if ( w32g_syn_status == run ) {
				SetThreadPriority ( w32g_syn.syn_hThread, syn_ThreadPriority );
			}
			break;
		case IDM_SYN_THREAD_PRIORITY_TIMECRITICAL:
			syn_ThreadPriority = THREAD_PRIORITY_TIME_CRITICAL;
			if ( w32g_syn_status == run ) {
				SetThreadPriority ( w32g_syn.syn_hThread, syn_ThreadPriority );
			}
			break;
#ifdef HAVE_SYN_CONSOLE
		case IDM_CONSOLE_WND:
			if ( hConsoleWnd == NULL ) {
				InitConsoleWnd ( w32g_syn.nid_hWnd );
			}
			if ( IsWindowVisible ( hConsoleWnd ) )
				ShowWindow ( hConsoleWnd, SW_HIDE );
			else
				ShowWindow ( hConsoleWnd, SW_SHOW );
			break;
#endif
		default:
			break;
		}
