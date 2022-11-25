#ifndef SKELETONS_Cpitch_QANGLE_HPP
#define SKELETONS_Cpitch_QANGLE_HPP

#include <cmath>
#include <iostream>

namespace sdk
{
	struct qangle {
	public:
		float pitch{ }, yaw{ }, roll{ };

		qangle( ) = default;
		qangle( float pitch, float yaw, float roll ) : pitch( pitch ), yaw( yaw ), roll( roll ){ };

		float length( ) const
		{
			return sqrtf( pitch * pitch + yaw * yaw + roll * roll );
		}

		float length_2d( ) const
		{
			return sqrtf( pitch * pitch + yaw * yaw );
		}

		qangle normalize( )
		{
			pitch = std::isfinite( pitch ) ? std::remainder( pitch, 360.f ) : 0.f;
			yaw   = std::isfinite( yaw ) ? std::remainder( yaw, 360.f ) : 0.f;
			roll  = 0.f;
			return *this;
		}

		qangle operator+( const float other ) const
		{
			return qangle( pitch + other, yaw + other, roll + other );
		}

		qangle operator-( const float other ) const
		{
			return qangle( pitch - other, yaw - other, roll - other );
		}

		qangle operator*( const float other ) const
		{
			return qangle( pitch * other, yaw * other, roll * other );
		}

		qangle operator/( const float other ) const
		{
			return qangle( pitch / other, yaw / other, roll / other );
		}

		qangle operator+( const qangle other ) const
		{
			return qangle( pitch + other.pitch, yaw + other.yaw, roll + other.roll );
		}

		qangle operator-( const qangle other ) const
		{
			return qangle( pitch - other.pitch, yaw - other.yaw, roll - other.roll );
		}

		qangle operator+=( const float other )
		{
			pitch += other;
			yaw += other;
			roll += other;
			return *this;
		}

		qangle operator-=( const float other )
		{
			pitch -= other;
			yaw -= other;
			roll -= other;
			return *this;
		}

		qangle operator*=( const float other )
		{
			pitch *= other;
			yaw *= other;
			roll *= other;
			return *this;
		}

		qangle operator/=( const float other )
		{
			pitch /= other;
			yaw /= other;
			roll /= other;
			return *this;
		}

		qangle operator+=( const qangle other )
		{
			pitch += other.pitch;
			yaw += other.yaw;
			roll += other.roll;
			return *this;
		}

		qangle operator-=( const qangle other )
		{
			pitch -= other.pitch;
			yaw -= other.yaw;
			roll -= other.roll;
			return *this;
		}
	};
} // namespace sdk

#endif // WEDNESDAY_WTF_QANGLE_HPP
