#ifndef __RFW_BASE_BASE_H
#define __RFW_BASE_BASE_H

namespace RFW
{
	class Base
	{
	public:
		// Load dependencies in this function
		virtual void init() = 0;
		virtual ~Base() = default;
	};
}

#endif // __RFW_BASE_BASE_H