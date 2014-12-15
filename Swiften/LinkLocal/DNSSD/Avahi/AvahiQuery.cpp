/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Swiften/LinkLocal/DNSSD/Avahi/AvahiQuery.h>
#include <Swiften/LinkLocal/DNSSD/Avahi/AvahiQuerier.h>

namespace Swift {

AvahiQuery::AvahiQuery(boost::shared_ptr<AvahiQuerier> q, EventLoop* eventLoop) : querier(q), eventLoop(eventLoop) {
}

AvahiQuery::~AvahiQuery() {
}

}

