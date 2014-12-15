/**
* Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
* more contributor license agreements. See the NOTICE file distributed
* with this work for additional information regarding copyright ownership.
* Green Energy Corp licenses this file to you under the Apache License,
* Version 2.0 (the "License"); you may not use this file except in
* compliance with the License.  You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* This project was forked on 01/01/2013 by Automatak, LLC and modifications
* may have been made to this file. Automatak, LLC licenses these modifications
* to you under the terms of the License.
*/

#include "Group120.h"

#include <openpal/logging/LogMacros.h>
#include <openpal/serialization/Serialization.h>

#include <opendnp3/LogLevels.h>

using namespace openpal;

namespace opendnp3 {

Group120Var1::Group120Var1() : 
	challengeSeqNum(0),
	userNum(0),
	hmacType(HMACType::Unknown),
	reason(ChallengeReason::UNKNOWN)	
{
		
}

bool Group120Var1::Read(const openpal::ReadBufferView& data, Group120Var1& output, openpal::Logger* pLogger)
{
	if (data.Size() < MIN_SIZE)
	{
		SIMPLE_LOGGER_BLOCK(pLogger, flags::WARN, "Not enough data for g120v1 object");
		return false;
	}
	else
	{
		ReadBufferView copy(data);
		output.challengeSeqNum = UInt32::ReadBuffer(copy);		
		output.userNum = UInt16::ReadBuffer(copy);
		output.hmacType = HMACTypeFromType(UInt8::ReadBuffer(copy));
		output.reason = ChallengeReasonFromType(UInt8::ReadBuffer(copy));
		output.challengeData = copy;
		return true;
	}
}

}
