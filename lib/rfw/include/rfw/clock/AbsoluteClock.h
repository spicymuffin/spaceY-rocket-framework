#ifndef __RFW_CLOCK_ABSOLUTE_CLOCK_H
#define __RFW_CLOCK_ABSOLUTE_CLOCK_H

#include <stdint.h>

#include "Clock.h"

namespace RFW
{
	class AbsoluteClock : public virtual Clock
	{
	public:
		virtual void set_time(uint64_t time) = 0;
		virtual ~AbsoluteClock() = default;
	};
}

#endif // __RFW_CLOCK_ABSOLUTE_CLOCK_H