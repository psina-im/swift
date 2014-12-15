/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <string>

#include <Swiften/Elements/Payload.h>

namespace Swift {
	class ChatState : public Payload {
		public:
			enum ChatStateType {Active, Composing, Paused, Inactive, Gone};
			ChatState(ChatStateType state = Active) {
				state_ = state;
			}

			ChatStateType getChatState() const { return state_; }
			void setChatState(ChatStateType state) {state_ = state;}

		private:
			ChatStateType state_;
	};
}
