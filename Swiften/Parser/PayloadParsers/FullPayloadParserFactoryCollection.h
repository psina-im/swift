/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <boost/shared_ptr.hpp>
#include <vector>

#include <Swiften/Base/API.h>
#include <Swiften/Parser/PayloadParserFactoryCollection.h>
#include <Swiften/Parser/PayloadParserFactory.h>

namespace Swift {
	class SWIFTEN_API FullPayloadParserFactoryCollection : public PayloadParserFactoryCollection {
		public:
			FullPayloadParserFactoryCollection();
			~FullPayloadParserFactoryCollection();

		private:
			std::vector< boost::shared_ptr<PayloadParserFactory> > factories_;
			PayloadParserFactory* defaultFactory_;
	};
}
