#ifndef _KB_ROGUE_HEADER_PP_
#define _KB_ROGUE_HEADER_PP_

#include <memory>

#include "spdlog/spdlog.h"

namespace kb
{
	namespace rogue
	{
		class MapManager;

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

			private:
				std::shared_ptr<spdlog::logger> logger;
				std::shared_ptr<MapManager> mapManager;
		};
	}
}

#endif /* _KB_ROGUE_HEADER_PP_ */
