#pragma once
#include <winsock2.h>
#include <sstream>
#include <stdexcept>

namespace Network {

	class SocketMessage	{
	public:
		SocketMessage();
		~SocketMessage();

		template <typename T> void add(T v) {
			string s = to_string(v);
			for (int i = 0; i < s.size(); i++) {
				buff[writeCursor] = s[i];
				writeCursor++;
			}
			buff[writeCursor++] = '|';
		}

		template <typename T> T get() throw (std::logic_error) {
			if (ss == NULL) {
				throw logic_error("The message is not received.");
			}

			string line;
			getline(ss, line, '|');
			return (T)line;
		}

		friend class Socket;

	private:
		char* buff;
		int size;
		int writeCursor;
		std::stringstream *ss;

		static int MSG_MAXSIZE;

		SocketMessage(char* buffer, int size);
		int serialize(char **buffer);
	};

	/*template <>	void SocketMessage::add<string>(string v) {
		for (unsigned int i = 0; i < v.size(); i++) {
			buff[writeCursor] = v[i];
			writeCursor++;
		}
		buff[writeCursor++] = '|';
	}*/

}