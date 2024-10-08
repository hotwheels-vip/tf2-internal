#include "hooks.hpp"

#include "cl_move/cl_move.hpp"
#include "cl_send_move/cl_send_move.hpp"
#include "create_move/create_move.hpp"
#include "draw_model_execute/draw_model_execute.hpp"
#include "end_scene/end_scene.hpp"
#include "frame_stage_notify/frame_stage_notify.hpp"
#include "get_time/get_time.hpp"
#include "is_playing_back/is_playing_back.hpp"
#include "item_post_frame/item_post_frame.hpp"
#include "packet_start/packet_start.hpp"
#include "paint_traverse/paint_traverse.hpp"
#include "process_tick/process_tick.hpp"
#include "run_command/run_command.hpp"
#include "scene_end/scene_end.hpp"
#include "send_net_msg/send_net_msg.hpp"
#include "wndproc/wndproc.hpp"

bool hooks::run( )
{
	MH_Initialize( );

	g_end_scene->run( );
	g_wndproc->run( );
	g_paint_traverse->run( );
	g_create_move->run( );
	g_is_playing_back->run( );
	g_frame_stage_notify->run( );
	g_process_tick->run( );
	g_cl_move->run( );
	g_run_command->run( );
	g_send_net_msg->run( );
	g_item_post_frame->run( );
	g_get_time->run( );
	g_packet_start->run( );
	g_cl_send_move->run( );
	g_scene_end->run( );
	g_draw_model_execute->run( );

	// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
	MH_EnableHook( MH_ALL_HOOKS );

	return true;
}

bool hooks::end( )
{
	g_wndproc->end( );
	g_end_scene->end( );
	g_paint_traverse->end( );
	g_create_move->end( );
	g_is_playing_back->end( );
	g_frame_stage_notify->end( );
	g_process_tick->end( );
	g_cl_move->end( );
	g_run_command->end( );
	g_send_net_msg->end( );
	g_item_post_frame->end( );
	g_get_time->end( );
	g_packet_start->end( );
	g_cl_send_move->end( );
	g_scene_end->end( );
	g_draw_model_execute->end( );

	MH_Uninitialize( );

	return true;
}
