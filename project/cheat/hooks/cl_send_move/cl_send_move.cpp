#include "cl_send_move.hpp"

void cl_send_move::detour( )
{
	return g_cl_send_move->_hook.call( );
}
