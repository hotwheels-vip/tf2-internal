
#ifndef WEDNESDAY_WTF_DISPSURF_FLAG_HPP
#define WEDNESDAY_WTF_DISPSURF_FLAG_HPP
namespace sdk
{

	enum dispsurf_flag {
		dispsurf_flag_surface   = ( 1 << 0 ),
		dispsurf_flag_walkable  = ( 1 << 1 ),
		dispsurf_flag_buildable = ( 1 << 2 ),
		dispsurf_flag_surfprop1 = ( 1 << 3 ),
		dispsurf_flag_surfprop2 = ( 1 << 4 )
	};

} // namespace sdk
#endif // WEDNESDAY_WTF_DISPSURF_FLAG_HPP
