// DEFINITION MODULE initStart;
/* Revision History:
Rev. 1 - 24/07/03 Original by Group 24
----------------------------------------------------------
This module initializes the necessary components for the application.
It includes the initialization of Change, ChangeRequest, Requester,
Product, and Release modules to ensure that the application starts
with all components ready for use. This abstraction hides the
complexities of initializing multiple components, providing a
straightforward interface for starting the application.
----------------------------------------------------------
*/

#ifndef INITSTART_H
#define INITSTART_H

#include "Change.h"
#include "ChangeRequest.h"
#include "Requester.h"
#include "Product.h"
#include "Release.h"

/*
----------------------------------------------------------
// Exported functions
*/

bool initStart();

#endif
