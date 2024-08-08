#ifndef __RFW_BASE_UPDATE_H
#define __RFW_BASE_UPDATE_H

#include "Base.h"

namespace RFW
{
	class Update : public virtual Base
	{
	public:
		virtual void update() = 0;
		virtual ~Update() = default;
	};
}

#endif // __RFW_BASE_UPDATE_H