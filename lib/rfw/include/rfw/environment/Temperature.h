#ifndef __RFW_ENVIRONMENT_TEMPERATURE_H
#define __RFW_ENVIRONMENT_TEMPERATURE_H

#include "rfw/base/Base.h"

namespace RFW
{
	class Temperature : public virtual Base
	{
	public:
		virtual double get_temperature() = 0;
		virtual ~Temperature() = default;
	};
}

#endif // __RFW_ENVIRONMENT_TEMPERATURE_H