#ifndef WEDNESDAY_WTF_CVAR_FLAGS_HPP
#define WEDNESDAY_WTF_CVAR_FLAGS_HPP

namespace sdk
{
	enum cvar_ids : int {
		fcvar_unregistered            = ( 1 << 0 ),
		fcvar_developmentonly         = ( 1 << 1 ),
		fcvar_gamedll                 = ( 1 << 2 ),
		fcvar_clientdll               = ( 1 << 3 ),
		fcvar_hidden                  = ( 1 << 4 ),
		fcvar_protected               = ( 1 << 5 ),
		fcvar_sponly                  = ( 1 << 6 ),
		fcvar_archive                 = ( 1 << 7 ),
		fcvar_notify                  = ( 1 << 8 ),
		fcvar_userinfo                = ( 1 << 9 ),
		fcvar_printableonly           = ( 1 << 10 ),
		fcvar_unlogged                = ( 1 << 11 ),
		fcvar_never_as_string         = ( 1 << 12 ),
		fcvar_replicated              = ( 1 << 13 ),
		fcvar_cheat                   = ( 1 << 14 ),
		fcvar_ss                      = ( 1 << 15 ),
		fcvar_demo                    = ( 1 << 16 ),
		fcvar_dontrecord              = ( 1 << 17 ),
		fcvar_ss_added                = ( 1 << 18 ),
		fcvar_release                 = ( 1 << 19 ),
		fcvar_reload_materials        = ( 1 << 20 ),
		fcvar_reload_textures         = ( 1 << 21 ),
		fcvar_not_connected           = ( 1 << 22 ),
		fcvar_material_system_thread  = ( 1 << 23 ),
		fcvar_archive_xbox            = ( 1 << 24 ),
		fcvar_accessible_from_threads = ( 1 << 25 ),
		fcvar_server_can_execute      = ( 1 << 28 ),
		fcvar_server_cannot_query     = ( 1 << 29 ),
		fcvar_clientcmd_can_execute   = ( 1 << 30 ),
		fcvar_material_thread_mask    = ( fcvar_reload_materials | fcvar_reload_textures | fcvar_material_system_thread )
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_CVAR_FLAGS_HPP
