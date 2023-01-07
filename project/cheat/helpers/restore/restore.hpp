#pragma once

template< typename T >
class restore
{
private:
	T value{ };
	T* address{ };

public:
	restore( ) = default;
	restore( T* address ) : address( address ), value( *address ){ };

	void run( )
	{
		*address = value;
	}
};
