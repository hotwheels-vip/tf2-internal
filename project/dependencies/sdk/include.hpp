#pragma once

#include "helpers/math.hpp"

#include "enums/buttons.hpp"

#include "interfaces/game_movement.hpp"
#include "interfaces/i_base_client_dll.hpp"
#include "interfaces/i_base_client_state.hpp"
#include "interfaces/i_client_entity_list.hpp"
#include "interfaces/i_client_leaf_system.hpp"
#include "interfaces/i_client_mode.hpp"
#include "interfaces/i_cvar.hpp"
#include "interfaces/i_debug_overlay.hpp"
#include "interfaces/i_engine_client.hpp"
#include "interfaces/i_engine_trace.hpp"
#include "interfaces/i_global_vars_base.hpp"
#include "interfaces/i_input.hpp"
#include "interfaces/i_localize.hpp"
#include "interfaces/i_material_system.hpp"
#include "interfaces/i_model_info.hpp"
#include "interfaces/i_model_render.hpp"
#include "interfaces/i_net_channel.hpp"
#include "interfaces/i_panel.hpp"
#include "interfaces/i_prediction.hpp"
#include "interfaces/i_render_view.hpp"

#include "structs/c_tf_knife.hpp"
#include "structs/c_tf_medigun.hpp"
#include "structs/c_tf_minigun.hpp"
#include "structs/c_tf_pipebomb_launcher.hpp"
#include "structs/c_tf_player.hpp"
#include "structs/c_tf_sniper_rifle.hpp"
#include "structs/c_user_cmd.hpp"
#include "structs/client_class.hpp"
#include "structs/dt_recv.hpp"
#include "structs/i_collideable.hpp"
#include "structs/key_values.hpp"
#include "structs/player_info.hpp"

#include "structs/box.hpp"
#include "structs/color.hpp"
#include "structs/matrix.hpp"
#include "structs/qangle.hpp"
#include "structs/vector.hpp"

#include "enums/client_frame_stage.hpp"
#include "enums/flags.hpp"
#include "enums/hitboxes.hpp"
#include "enums/tf_cond.hpp"
#include "enums/trace_defs.hpp"
#include "enums/weapon_type.hpp"
