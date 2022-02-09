#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
//interface for event handlers
#include <stdio.h>
#include <stdlib.h>

typedef int Handle; //to be imported from separate file handler.h

typedef void (*HandleEventFnc)(void* instance);

typedef Handle (*GetHandleFnc)(void* instance);

typedef struct {
    /*each concrete handler must correspond to a unique instance*/
    void* instance;
    HandleEventFnc handleEvent;
    GetHandleFnc getHandle;
    void*data;
}EventHandler;

#endif