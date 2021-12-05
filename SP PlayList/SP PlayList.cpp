// SpeechPlaylist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "WndMainPlayList.h"
#include <stdio.h>
#include <Windows.h>

using namespace SPPlayList;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	WndMainPlayList ^obj=gcnew WndMainPlayList();
	Application::Run(obj);
	return 0;
	return 0;
}