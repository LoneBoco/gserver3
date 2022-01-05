#include "BabyDI.Configuration.h"

import graal.core;

//import "common.h";

import <iostream>;
import <algorithm>;


int main(int argc, char* argv[])
{
	// Load all settings first.
	PROVIDE(graal::settings::ProgramSettings, new graal::settings::ProgramSettings());
	auto settings = BabyDI::Get<graal::settings::ProgramSettings>();
	settings->LoadFromFile("settings.ini");
	settings->LoadFromCommandLine(argc, argv);

	// Configure our various managers.
	try
	{
		ConfigureBabyDI();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	// Initialize the Game.
	//auto game = BabyDI::Get<tdrp::Game>();
	//game->Initialize();

	// Pull out the injected window and start the event loop.
	//auto window = BabyDI::Get<tdrp::render::Window>();
	//window->EventLoop();

	return 0;
}
