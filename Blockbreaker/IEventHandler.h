#pragma once

#include "EventDispatcher.h"

struct Event
{
	int Type;
	int arg1, arg2;
};


enum EventType
{
	// Keyboard button events
	E_KEYBOARD_LEFTPRESS, E_KEYBOARD_RIGHTPRESS,
	E_KEYBOARD_ENTERPRESS, E_KEYBOARD_UPPRESS,
	E_KEYBOARD_DOWNPRESS,

	// Start new game
	E_NEWGAME,

	// Game states
	E_PAUSEGAME, E_GAMEOVER, E_CONTINUE,
	E_INCREMENT_SCORE,

	// Exit the game
	E_QUIT
};

class IEventHandler
{
public:
	virtual void EventHandler(const Event &e) = 0;

	IEventHandler * GetNextHandler() { return _nextHandler; }
	void SetNextHandler(IEventHandler * next) { _nextHandler = next; }

	IEventHandler() : _nextHandler(0) 
	{
		EventDispatcher::Get()->RegisterHandler(this);
	}

protected:
	void SendEvent(int eventType, int arg1 = 0, int arg2 = 0)
	{
		EventDispatcher::Get()->SendEvent(eventType, arg1, arg2);
	}

private:
	IEventHandler * _nextHandler;

};