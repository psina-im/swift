/*
 * Copyright (c) 2010-2014 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Elements/ToplevelElement.h>

namespace Swift {
	class CompressRequest : public ToplevelElement
	{
		public:
			CompressRequest(const std::string& method = "") : method_(method) {}

			const std::string& getMethod() const {
				return method_;
			}

			void setMethod(const std::string& method) { 
				method_ = method;
			}

		private:
			std::string method_;
	};
}
