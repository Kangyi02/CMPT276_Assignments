// DEFINITION MODULE ScenarioControl;
/* Revision History:
Rev. 1 - 24/07/03 Original by Group 24
----------------------------------------------------------
This module defines the control functions for managing scenarios
related to product changes, releases, change requests, queries,
updates, reports, and shutdown operations. Each function provides
an interface to perform specific actions within the application,
ensuring clear separation of concerns and ease of maintenance.
----------------------------------------------------------
*/

#ifndef ScenarioControl_H
#define ScenarioControl_H

#include "Change.h"
#include "ChangeRequest.h"
#include "Requester.h"
#include "Product.h"
#include "Release.h"

/*
----------------------------------------------------------
//Exported constants/types/variables
*/

// Create control
void createProductControl();
void createReleaseControl();
void createChangeRequestControl();

// Query control
void queryChangeControl();

// Update control
void updateChangeControl();

// Reports control
void allChangesReportControl();
void allRequestersReportControl();

// ShutDown control
void shutDownControl();

#endif