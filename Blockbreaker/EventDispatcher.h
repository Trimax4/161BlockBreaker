#pragma once

class IEventHandler;

class EventDispatcher{

public:
	static EventDispatcher * Get();

private:
	EventDispatcher() : _deviceList(0) { ; }
	~EventDispatcher() { ; }

	static EventDispatcher * _instanceOf;

public:
	void RegisterHandler(IEventHandler * device);
	void SendEvent(int eventType, int arg1 = 0, int arg2 = 0);

private:
	IEventHandler * _deviceList;
};