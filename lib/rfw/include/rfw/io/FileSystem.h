#ifndef __RFW_IO_FILESYSTEM_H
#define __RFW_IO_FILESYSTEM_H

#include "rfw/base/Update.h"

namespace RFW
{
	class FileSystem : public virtual Update
	{
	public:
		// Filesystem Access may not encapsulated in a class
		virtual ~FileSystem() = default;
	};
}

#endif // __RFW_IO_FILESYSTEM_H