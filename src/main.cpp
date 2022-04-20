#pragma warning (push)
#pragma warning (disable: 4005)
#pragma warning (disable: 5104)

#include "common.h"
#include "BabyDI.Configuration.h"

#include <csignal>
#include <boost/stacktrace.hpp>

import graal.core;
import graal.packet;
import graal.programsettings;
import graal.server;

//import std.core;
//import "BabyDI.hpp";


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

	// Provide settings first before we construct anything else.
	auto settings = new graal::settings::ProgramSettings();
	PROVIDE(graal::settings::ProgramSettings, settings);

	// Load all settings.
	Log::PrintLine(":: Loading settings.");
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

	// Load server.
	PROVIDE(graal::server::Server, new graal::server::Server());
	auto server = BabyDI::Get<graal::server::Server>();
	server->LoadConfiguration();

	// Wait until the server ends.


	return 0;
}

#pragma warning (pop)
