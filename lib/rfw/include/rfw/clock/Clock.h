#ifndef __RFW_CLOCK_CLOCK_H
#define __RFW_CLOCK_CLOCK_H

#include <stdint.h>

#include "rfw/base/Base.h"

namespace RFW
{
	class Clock : public virtual Base
	{
	public:
		virtual uint64_t get_time_ms() = 0;
		virtual uint64_t get_time_us() = 0;
		virtual ~Clock() = default;
	};
}

#endif // __RFW_CLOCK_CLOCK_H