#include "token.hxx"
#include <cctype>
#include <cstdio>

namespace Token
{

Stream::Stream(const std::string &path) : f(path)
{
	f.get(c);
}

void Stream::Rewind()
{
	f.seekp(SEEK_SET);
	f.get(c);
}

const std::string &Stream::GetToken()
{
	return token;
}

void Stream::NextToken()
{
	token.resize(0);
	while (std::isspace(c))
	{
		f.get(c);
	}

	if (!f.eof())
	{
		do
		{
			token += c;
			f.get(c);
		} while (std::isalnum(c));
	}
}

bool Stream::NextIfMatch(const std::string &str)
{
	if (GetToken() == str)
	{
		NextToken();
		return true;
	}
	else
	{
		return false;
	}
}
}; // namespace Token