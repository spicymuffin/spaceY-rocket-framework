#ifndef __RFW_ENVIRONMENT_PRESSURE_H
#define __RFW_ENVIRONMENT_PRESSURE_H

#include "rfw/base/Base.h"

namespace RFW
{
	class Pressure : public Base
	{
	public:
		virtual double get_pressure() = 0;
		virtual ~Pressure() = default;
	};
}

#endif // __RFW_ENVIRONMENT_PRESSURE_H