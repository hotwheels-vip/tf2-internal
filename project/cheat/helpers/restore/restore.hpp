#pragma once

template< typename T >
class restore
{
private:
	T value{ };
	T* address{ };

public:
	restore( ) = default;
	explicit restore( T* address ) : value( *address ), address( address ){ };

	void run( )
	{
		*address = value;
	}
};
