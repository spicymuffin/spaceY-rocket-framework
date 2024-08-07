#ifndef __RFW_CLOCK_UPDATING_ABSOLUTE_CLOCK_H
#define __RFW_CLOCK_UPDATING_ABSOLUTE_CLOCK_H

#include "Clock.h"

namespace RFW
{
	class ExternalAbsoluteClock : public virtual Clock
	{
	public:
		virtual ~ExternalAbsoluteClock() = default;
	};
}

#endif // __RFW_CLOCK_UPDATING_ABSOLUTE_CLOCK_H