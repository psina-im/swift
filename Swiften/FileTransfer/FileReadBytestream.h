/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/FileTransfer/ReadBytestream.h>

namespace Swift {
	class SWIFTEN_API FileReadBytestream : public ReadBytestream {
		public:
			FileReadBytestream(const boost::filesystem::path& file);
			~FileReadBytestream();

			virtual boost::shared_ptr< std::vector<unsigned char> > read(size_t size);
			virtual bool isFinished() const;

		private:
			boost::filesystem::path file;
			boost::filesystem::ifstream* stream;
	};
}
