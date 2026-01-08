#pragma once

#include <fstream>
#include <string>
namespace Token
{

struct Stream
{
	Stream(const std::string &path);

	const std::string &GetToken();

	void NextToken();

	bool NextIfMatch(const std::string &str);

	void Rewind();

  private:
	std::fstream f;
	char c;
	std::string token;
};

}; // namespace Token