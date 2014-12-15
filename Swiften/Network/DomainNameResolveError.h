/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/Error.h>

namespace Swift {
	class DomainNameResolveError : public Error {
		public:
			DomainNameResolveError() {}
	};
}
