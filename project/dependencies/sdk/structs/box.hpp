#ifndef WEDNESDAY_WTF_BOX_HPP
#define WEDNESDAY_WTF_BOX_HPP

namespace sdk
{
	struct box {
		int x, y, w, h;

		box( ) = default;
		box( int xywh ) : x( xywh ), y( xywh ), w( xywh ), h( xywh ){ };
		box( int x, int y ) : x( x ), y( y ), w( x ), h( y ){ };
		box( int x, int y, int w, int h ) : x( x ), y( y ), w( w ), h( h ){ };

		vector width( )
		{
			return { static_cast< float >( w - x ), static_cast< float >( h - y ) };
		}
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_BOX_HPP
