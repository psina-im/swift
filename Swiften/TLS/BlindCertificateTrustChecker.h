/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/TLS/CertificateTrustChecker.h>

namespace Swift {
	/**
	 * A certificate trust checker that trusts any ceritficate.
	 *
	 * This can be used to ignore any TLS certificate errors occurring 
	 * during connection.
	 *
	 * \see Client::setAlwaysTrustCertificates()
	 */
	class BlindCertificateTrustChecker : public CertificateTrustChecker {
		public:
			virtual bool isCertificateTrusted(const std::vector<Certificate::ref>&) {
				return true;
			}
	};
}
