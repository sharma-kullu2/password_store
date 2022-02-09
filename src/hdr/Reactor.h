#ifndef REACTOR_H
#define REACTOR_H

#include "EventHandler.h"

enum Events {
    EVT_WRITE_FILE,
    EVT_READ_FILE
};

typedef enum Events EventList;
void Register(EventHandler* handler, EventList event);
void Unregister(EventHandler* handler);
void DispatchEvent(EventList event);

#endif