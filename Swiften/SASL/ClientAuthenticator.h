/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <boost/optional.hpp>

#include "Swiften/Base/String.h"
#include "Swiften/Base/ByteArray.h"

namespace Swift {
	class ClientAuthenticator {
		public:
			ClientAuthenticator(const String& name);
			virtual ~ClientAuthenticator();

			const String& getName() const {
				return name;
			}

			void setCredentials(const String& authcid, const String& password, const String& authzid = String()) {
				this->authcid = authcid;
				this->password = password;
				this->authzid = authzid;
			}

			virtual boost::optional<ByteArray> getResponse() const = 0;
			virtual bool setChallenge(const boost::optional<ByteArray>&) = 0;

			const String& getAuthenticationID() const {
				return authcid;
			}

			const String& getAuthorizationID() const {
				return authzid;
			}

			const String& getPassword() const {
				return password;
			}
		
		private:
			String name;
			String authcid;
			String password;
			String authzid;
	};
}
