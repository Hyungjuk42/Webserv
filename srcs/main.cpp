#include <iostream>
#include <signal.h>
#include "ConfigHandler.hpp"
#include "AConfParser.hpp"
#include "HttpHandler.hpp"
#include "parseUtils.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include "WebServ.hpp"

int main(int argc, char *argv[], char *envp[])
{
	signal(SIGPIPE, SIG_IGN);
	try
	{
		if (argc > 2)
			throw std::runtime_error("Bad argc");
		if (argc == 2)
			ConfigHandler::MakeConfigHandler(argv[1]);
		else
			ConfigHandler::MakeConfigHandler("./conf/default.conf");
		std::vector<std::string> envList;
		for (char **env = envp; *env != 0; env++)
			envList.push_back(*env);
		WebServ webServ(ConfigHandler::GetConfigHandler().GetPorts(), envList);
	}
	catch(const std::exception& e)
	{
		perror(e.what());
	}
	return (0);
}
