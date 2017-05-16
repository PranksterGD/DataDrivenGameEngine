#pragma once

//Windows libraries
#include <SDKDDKVer.h>

//Standard libraries
#include <cstdint>
#include <exception>
#include <windows.h>
#include <utility>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <chrono>
#include <future>
#include <thread>
#include <mutex>

//Local Headers

//Containers
#include "SList.h"
#include "Vector.h"
#include "DefaultHash.h"
#include "Hashmap.h"
#include "RTTI.h"
#include "Datum.h"
#include "Scope.h"
#include "Attributed.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "Action.h"

//Parsers
#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"
#include "XmlParseHelperTable.h"
#include "XmlParseHelperInteger.h"
#include "XmlParseHelperFloat.h"
#include "XmlParseHelperString.h"
#include "XmlParseHelperVector.h"
#include "XmlParseHelperMatrix.h"
#include "XmlParseHelperWorld.h"
#include "XmlParseHelperSector.h"
#include "XmlParseHelperEntity.h"
#include "XmlParseHelperAction.h"
#include "XmlParseHelperActionListIf.h"
#include "XmlParseHelperReaction.h"

//Game Components
#include "WorldState.h"
#include "Factory.h"
#include "GameClock.h"
#include "GameTime.h"

//Actions
#include "ActionList.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionListIf.h"
#include "ActionEvent.h"

//Reactions
#include "Reaction.h"
#include "ReactionAttributed.h"

//Events
#include "EventPublisher.h"
#include "EventSubscriber.h"
#include "Event.h"
#include "EventQueue.h"
#include "EventMessageAttributed.h"

