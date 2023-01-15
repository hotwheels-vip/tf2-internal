#pragma once

#include "vector.hpp"

namespace sdk
{
	class __declspec( align( 16 ) ) vector_aligned : public vector
	{
	public:
		vector_aligned( void ){ };

		vector_aligned( float x, float y, float z )
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		explicit vector_aligned( const vector& othr )
		{
			this->x = othr.x;
			this->y = othr.y;
			this->z = othr.z;
		}

		vector_aligned& operator=( const vector& othr )
		{
			this->x = othr.x;
			this->y = othr.y;
			this->z = othr.z;

			return *this;
		}

		float w;
	};

} // namespace sdk
