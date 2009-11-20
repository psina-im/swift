#include "Swiften/Serializer/AuthChallengeSerializer.h"

#include "Swiften/Elements/AuthChallenge.h"
#include "Swiften/StringCodecs/Base64.h"

namespace Swift {

AuthChallengeSerializer::AuthChallengeSerializer() {
}

String AuthChallengeSerializer::serialize(boost::shared_ptr<Element> element)  const {
	boost::shared_ptr<AuthChallenge> authRequest(boost::dynamic_pointer_cast<AuthChallenge>(element));
	String value = (authRequest->getValue().isEmpty() ? "=" : Base64::encode(authRequest->getValue()));
	return "<challenge xmlns=\"urn:ietf:params:xml:ns:xmpp-sasl\">" + value + "</challenge>";
}

}
