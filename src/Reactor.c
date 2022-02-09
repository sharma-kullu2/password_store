#include "hdr/Reactor.h"


#define MAX_NO_OF_EVENTS 32

/* Bind an event handler to the struct used to interface poll(). */
typedef struct
{
   int isUsed;
   EventHandler handler;
   EventList event;
} HandlerRegistration;

static HandlerRegistration registeredHandlers[MAX_NO_OF_EVENTS];

static int addToRegistry(EventHandler* handler,EventList event);

static int removeFromRegistry(EventHandler* handler);

/****************************************************************
* Implementation of the Reactor interface used for registrations.
*****************************************************************/

void Register(EventHandler* handler,EventList event)
{
   //assert(NULL != handler);

   if(!addToRegistry(handler,event)) {
      /* NOTE: In production code, this error should be delegated to the client instead. */
      //error("No more registrations possible");
   }
}

void Unregister(EventHandler* handler)
{
   //assert(NULL != handler);
   
   if(!removeFromRegistry(handler)) {
      /* NOTE: In production code, this error should be delegated to the client instead. */
      //error("Event handler not registered");
   }
}

void DispatchEvent(EventList event)
{
    for(int i=0;i<MAX_NO_OF_EVENTS;i++){
        if (event==i){
            EventHandler* handler=&registeredHandlers[i].handler;
            printf("handler->handleEvent at address %p\n",handler);
            handler->handleEvent(handler->instance);
            
        }
    }
}

/************************************************************
* Definition of the local utility functions.
************************************************************/
/**
* Add a copy of the given handler to the first free position in registeredHandlers.
*/
static int addToRegistry(EventHandler* handler,EventList Event)
{
   /* Identify the first free position. */
   int isRegistered = 0;
   int i = 0;
   
   for(i = 0; (i < MAX_NO_OF_EVENTS) && (0 == isRegistered); ++i) {
      
      if(0 == registeredHandlers[i].isUsed) {
         /* A free position found. */
         HandlerRegistration* freeEntry = &registeredHandlers[i];
         
         /* Create a binding between the handle provided by the client and the events of interest. */
         freeEntry->handler = *handler;
         freeEntry->event=Event;         
         isRegistered = freeEntry->isUsed = 1;
         (void) printf("Reactor: Added handle with Event = %d\n", freeEntry->event);
      }
   }

   return isRegistered;
}

/**
* Identify the event handler in the registeredHandlers and remove it.
*/
static int removeFromRegistry(EventHandler* handler)
{
   /* Identify the event handler in the registeredHandlers and remove it. */
   int i = 0;
   int nodeRemoved = 0;
   
   for(i = 0; (i < MAX_NO_OF_EVENTS) && (0 == nodeRemoved); ++i) {
      
      if(registeredHandlers[i].isUsed && (registeredHandlers[i].handler.instance == handler->instance)) {
         /* The given event handler is found -> mark it as unused and terminate the loop. */
         registeredHandlers[i].isUsed = 0;
		 nodeRemoved = 1;
		 (void) printf("Reactor: Removed event handler with ID = %d\n", registeredHandlers[i].event);
      }
   }
   return nodeRemoved;
}
