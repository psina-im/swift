/*
 * Copyright (c) 2010-2014 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <set>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/JID/JID.h>
#include <Swiften/Elements/VCard.h>
#include <Swiften/Elements/ErrorPayload.h>
#include <Swiften/VCards/SetVCardRequest.h>
#include <Swiften/Base/boost_bsignals.h>

namespace Swift {
	class JID;
	class VCardStorage;
	class IQRouter;

	class SWIFTEN_API VCardManager : public boost::bsignals::trackable {
		public:
			VCardManager(const JID& ownJID, IQRouter* iqRouter, VCardStorage* vcardStorage);
			~VCardManager();

			VCard::ref getVCard(const JID& jid) const;
			VCard::ref getVCardAndRequestWhenNeeded(const JID& jid, const boost::posix_time::time_duration& allowedAge = boost::posix_time::time_duration(boost::date_time::pos_infin));
			void requestVCard(const JID& jid);
			void requestOwnVCard();

			std::string getPhotoHash(const JID& jid) const;


			SetVCardRequest::ref createSetVCardRequest(VCard::ref);

		public:
			/**
			 * The JID will always be bare.
			 */
			boost::signal<void (const JID&, VCard::ref)> onVCardChanged;

			/**
			 * Emitted when our own vcard changes.
			 *
			 * onVCardChanged will also be emitted.
			 */
			boost::signal<void (VCard::ref)> onOwnVCardChanged;

		private:
			void handleVCardReceived(const JID& from, VCard::ref, ErrorPayload::ref);
			void handleSetVCardResponse(VCard::ref, ErrorPayload::ref);
			void setVCard(const JID& jid, VCard::ref vcard);

		private:
			JID ownJID;
			IQRouter* iqRouter;
			VCardStorage* storage;
			std::set<JID> requestedVCards;
	};
}
