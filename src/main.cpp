#pragma warning (push)
#pragma warning (disable: 4005)
#pragma warning (disable: 5104)

#include "BabyDI.Configuration.h"

import graal.core;
import graal.packet;
import graal.programsettings;

//import "common.h";

import <iostream>;
import <algorithm>;
import <csignal>;

#include <boost/stacktrace.hpp>


void crash_handler(int signum)
{
	::signal(signum, SIG_DFL);
	boost::stacktrace::safe_dump_to("./backtrace.dump");
	::raise(SIGABRT);
}


int main(int argc, char* argv[])
{
	using namespace graal;

	::signal(SIGSEGV, &crash_handler);
	::signal(SIGABRT, &crash_handler);

	// Load all settings first.
	Log::Print(":: Loading settings.");
	auto s = new graal::settings::ProgramSettings();
	PROVIDE(graal::settings::ProgramSettings, s);
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

	packet::PacketData data;
	data << packet::WriteGraalByte<3>(123456) << packet::WriteGraalByte<2>(10101);

	// Initialize the Game.
	//auto game = BabyDI::Get<tdrp::Game>();
	//game->Initialize();

	// Pull out the injected window and start the event loop.
	//auto window = BabyDI::Get<tdrp::render::Window>();
	//window->EventLoop();

	return 0;
}

#pragma warning (pop)
