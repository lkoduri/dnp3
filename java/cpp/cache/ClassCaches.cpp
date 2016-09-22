/**
 * Copyright 2013 Automatak, LLC
 *
 * Licensed to Automatak, LLC (www.automatak.com) under one or more
 * contributor license agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership. Automatak, LLC
 * licenses this file to you under the Apache License Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */
 /**
 * Copyright 2013 Automatak, LLC
 *
 * Licensed to Automatak, LLC (www.automatak.com) under one or more
 * contributor license agreements. See the NOTICE file distributed with this
 * work for additional information regarding copyright ownership. Automatak, LLC
 * licenses this file to you under the Apache License Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

#include "ClassCaches.h"

#include "JNIHelpers.h"
#include "JNI.h"

#include <assert.h>

void LogHandlerCache::LogToHandler(jobject handler, const openpal::LogEntry& entry)
{
	const auto env = JNI::GetEnv();
	
	if (!initialized)
	{		
		this->logEntryClass = JNIHelpers::FindClass(env, "com/automatak/dnp3/LogEntry");		
		this->logEntryConstructor = JNIHelpers::GetMethodIDFromClass(env, this->logEntryClass, "<init>", "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		this->logMethod = JNIHelpers::GetMethodIDFromObject(env, handler, "log", "(Lcom/automatak/dnp3/LogEntry;)V");
		this->initialized = true;
	}	

	const jint level = entry.GetFilters().GetBitfield();
	const jstring id = env->NewStringUTF(entry.GetAlias());
	const jstring location = env->NewStringUTF(entry.GetLocation());
	const jstring msg = env->NewStringUTF(entry.GetMessage());
			
	auto jentry = env->NewObject(this->logEntryClass, this->logEntryConstructor, level, id, location, msg);
	
	assert(jentry != nullptr);
	
	env->CallVoidMethod(handler, logMethod, jentry);	
}