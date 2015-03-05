#include "EventDispatcher.h"
#include "IEventHandler.h"

EventDispatcher * EventDispatcher::_instanceOf = 0;

EventDispatcher * EventDispatcher::Get() 
{
	if (_instanceOf)
		return _instanceOf;
	return _instanceOf = new EventDispatcher();
}

void EventDispatcher::RegisterHandler(IEventHandler * device)
{
	device->SetNextHandler(_deviceList);
	_deviceList = device;
}

void EventDispatcher::SendEvent(int eventType, int arg1, int arg2)
{
	Event e;
	e.Type = eventType;
	e.arg1 = arg1;
	e.arg2 = arg2;
	IEventHandler * currentDevice = _deviceList;
	for (; currentDevice; currentDevice = currentDevice->GetNextHandler())
	{
		currentDevice->EventHandler(e);
	}
}