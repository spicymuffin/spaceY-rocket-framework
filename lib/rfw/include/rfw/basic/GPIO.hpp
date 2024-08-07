#ifndef __RFW_CLOCK_CLOCK_H
#define __RFW_CLOCK_CLOCK_H

#include <stdint.h>

#include "rfw/base/Update.h"

namespace RFW
{
	class GPIO : public virtual Base
	{
	public:
		virtual uint64_t get_value() = 0;
		virtual ~GPIO() = default;
	};
}

#endif // __RFW_CLOCK_CLOCK_H