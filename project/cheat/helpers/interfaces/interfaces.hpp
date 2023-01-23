#pragma once

#include "../memory/memory.hpp"

#include <d3dx9.h>
#include <hash/hash.hpp>
#include <sdk/include.hpp>

class interfaces
{
public:
	struct interface_ {
	public:
		void* ( *get )( ){ };
		const char* name{ };
		interface_* next{ };
	};

	sdk::i_client_mode* client_mode{ };
	sdk::i_engine_client* engine_client{ };
	sdk::i_base_client_dll* client{ };
	sdk::i_client_entity_list* entity_list{ };
	sdk::i_debug_overlay* debug_overlay{ };
	sdk::i_input* input{ };
	sdk::i_con_var* cvar{ };
	sdk::i_model_info* model_info{ };
	sdk::i_net_channel* net_channel{ };
	sdk::c_prediction* prediction{ };
	sdk::i_game_movement* game_movement{ };
	sdk::i_move_helper* move_helper{ };
	sdk::i_panel* panel{ };
	IDirect3DDevice9* device{ };
	sdk::i_global_vars_base* globals{ };
	sdk::i_render_view* render_view{ };
	sdk::i_engine_trace* engine_trace{ };
	sdk::i_client_leaf_system* leaf_system{ };
	sdk::i_model_render* model_render{ };
	sdk::i_material_system* material_system{ };
	sdk::i_localize* localize{ };
	sdk::i_base_client_state* client_state{ };

	bool run( );
	bool end( );
	static void* get_interface( const char* module, std::uint32_t hash );
	static std::uintptr_t jump_address( std::uintptr_t address );
};

inline interfaces* g_interfaces = new interfaces( );
