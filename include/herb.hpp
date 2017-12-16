#ifndef _HERB_HEADER_PP_KBROGUE_
#define _HERB_HEADER_PP_KBROGUE_

#include "item.hpp"

namespace kb
{
	namespace rogue
	{
		class Herb : public Item
		{
			public:
				Herb(int recoveryAmount);
				virtual ~Herb() = default;

				virtual void use(std::vector<std::shared_ptr<Mob>> targets) override;

			private:
				int recoveryAmount;
		};
	}
}

#endif /* _HERB_HEADER_PP_KBROGUE_ */
