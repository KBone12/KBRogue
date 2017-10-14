#ifndef _KB_ROGUE_HEADER_PP_
#define _KB_ROGUE_HEADER_PP_

#include <memory>

#include "spdlog/spdlog.h"

namespace kb
{
	namespace rogue
	{
		class Map;

		class KBRogue
		{
			public:
				/**
				 * Throws a spdlog::spdlog_ex when spdlog can't initialize
				 */
				KBRogue();

				void initialize();
				void start();
				void finalize();

				std::shared_ptr<Map> getCurrentMap() const
				{
					return currentMap;
				}

			private:
				std::shared_ptr<spdlog::logger> logger;
				std::vector<std::shared_ptr<Map>> maps;
				std::shared_ptr<Map> currentMap;
		};
	}
}

#endif /* _KB_ROGUE_HEADER_PP_ */
