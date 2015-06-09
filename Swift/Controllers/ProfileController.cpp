/*
 * Copyright (c) 2010-2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Swift/Controllers/ProfileController.h>

#include <boost/bind.hpp>

#include <Swiften/VCards/VCardManager.h>

#include <Swift/Controllers/Intl.h>
#include <Swift/Controllers/UIEvents/RequestProfileEditorUIEvent.h>
#include <Swift/Controllers/UIEvents/UIEventStream.h>
#include <Swift/Controllers/UIInterfaces/ProfileWindowFactory.h>

namespace Swift {

ProfileController::ProfileController(VCardManager* vcardManager, ProfileWindowFactory* profileWindowFactory, UIEventStream* uiEventStream) : vcardManager(vcardManager), profileWindowFactory(profileWindowFactory), uiEventStream(uiEventStream), available(true), profileWindow(NULL), gettingVCard(false) {
	uiEventStream->onUIEvent.connect(boost::bind(&ProfileController::handleUIEvent, this, _1));
}

ProfileController::~ProfileController() {
	if (profileWindow) {
		vcardManager->onOwnVCardChanged.disconnect(boost::bind(&ProfileController::handleOwnVCardChanged, this, _1));
		profileWindow->onVCardChangeRequest.disconnect(boost::bind(&ProfileController::handleVCardChangeRequest, this, _1));
		profileWindow->onWindowAboutToBeClosed.disconnect(boost::bind(&ProfileController::handleProfileWindowAboutToBeClosed, this, _1));
	}
	uiEventStream->onUIEvent.disconnect(boost::bind(&ProfileController::handleUIEvent, this, _1));
}

void ProfileController::handleUIEvent(UIEvent::ref event) {
	if (!boost::dynamic_pointer_cast<RequestProfileEditorUIEvent>(event)) {
		return;
	}

	if (!profileWindow) {
		profileWindow = profileWindowFactory->createProfileWindow();
		profileWindow->setEditable(true);
		profileWindow->onVCardChangeRequest.connect(boost::bind(&ProfileController::handleVCardChangeRequest, this, _1));
		profileWindow->onWindowAboutToBeClosed.connect(boost::bind(&ProfileController::handleProfileWindowAboutToBeClosed, this, _1));
		vcardManager->onOwnVCardChanged.connect(boost::bind(&ProfileController::handleOwnVCardChanged, this, _1));
	}
	gettingVCard = true;
	updateDialogStatus();
	vcardManager->requestOwnVCard();
	profileWindow->show();
}

void ProfileController::handleVCardChangeRequest(VCard::ref vcard) {
	assert(!pendingSetVCardRequest);
	profileWindow->setError("");
	pendingSetVCardRequest = vcardManager->createSetVCardRequest(vcard);
	pendingSetVCardRequest->onResponse.connect(boost::bind(&ProfileController::handleSetVCardResponse, this, _2));
	pendingSetVCardRequest->send();
	updateDialogStatus();
}

void ProfileController::handleSetVCardResponse(ErrorPayload::ref error) {
	pendingSetVCardRequest.reset();
	updateDialogStatus();
	if (error) {
		profileWindow->setVCard(vcardBeforeEdit);
		profileWindow->setError(QT_TRANSLATE_NOOP("", "There was an error publishing your profile data"));
	}
	else {
		profileWindow->setError("");
		profileWindow->hide();
	}
}

void ProfileController::handleOwnVCardChanged(VCard::ref vcard) {
	if (profileWindow) {
		profileWindow->setVCard(vcard);
		vcardBeforeEdit = vcard;
		gettingVCard = false;
		updateDialogStatus();
	}
}

void ProfileController::handleProfileWindowAboutToBeClosed(const JID&) {
	profileWindow = NULL;
}

void ProfileController::setAvailable(bool b) {
	available = b;
	if (!available) {
		pendingSetVCardRequest.reset();
	}
	updateDialogStatus();
}


void ProfileController::updateDialogStatus() {
	if (profileWindow) {
		profileWindow->setEnabled(available && !gettingVCard && !pendingSetVCardRequest);
		profileWindow->setProcessing(gettingVCard || pendingSetVCardRequest);
	}
}

}
