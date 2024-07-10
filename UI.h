// DEFINITION MODULE UI;
/* Revision History:
Rev. 1 - 24/07/03 Original by Group 24
----------------------------------------------------------
This module defines the main menu functions for managing
various aspects related to product changes, releases,
change requests, requesters, and reports within the application.
Each function provides an interface to navigate through
different menus and actions, ensuring user interaction
and system management are well-structured and intuitive.
----------------------------------------------------------
*/

#ifndef MAINMENU_H
#define MAINMENU_H

#include "ScenarioControl.h"

/*
----------------------------------------------------------
// Exported functions
*/

// Main menu
void activateUI();

// Create menu
void create();

// Query menu
void query();

// Update menu
void update();

// Reports menu
void reports();
#endif