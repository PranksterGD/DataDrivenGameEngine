#include "pch.h"

using namespace FieaGameEngine;
using namespace std;

RTTI_DEFINITIONS(Reaction)

const string Reaction::sReactionsTag = "Reactions";

Reaction::Reaction(const std::string& name):
	ActionList(name)
{

}