#ifndef __SSLSHADER_H__
#define __SSLSHADER_H__

#include <unordered_map>

namespace SE
{
	namespace core
	{
		namespace parser
		{
			namespace text
			{
				namespace ssl
				{
					class SSLShader
					{
					public:
						void											addIncludePath(const std::string& includePath);
						void											removeIncludePath(const std::string& includePath);

					public:
						std::string										sourceCode;

					private:
						std::unordered_map<std::string, std::string>	mIncludeMap;
					};
				}
			}
		}
	}
}

#endif // !__SSLSHADER_H__