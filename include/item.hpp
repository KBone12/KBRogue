#ifndef _ITEM_HEADER_PP_KBROGUE_
#define _ITEM_HEADER_PP_KBROGUE_

#include <memory>
#include <string>
#include <vector>

namespace kb
{
	namespace rogue
	{
		class Mob;

		class Item
		{
			public:
				Item(char mark, const std::string& name);
				virtual ~Item() = default;

				virtual void use(std::vector<std::shared_ptr<Mob>> targets) = 0;

				int getAmount() const
				{
					return amount;
				}

				void setAmount(int amount)
				{
					if (amount >= 0)	this->amount = amount;
				}

				char getMark() const
				{
					return mark;
				}

				std::string getName() const
				{
					return name;
				}

			protected:
				char mark;
				std::string name;
				int amount;
		};
	}
}

bool operator==(const kb::rogue::Item& r, const kb::rogue::Item& l);
bool operator!=(const kb::rogue::Item& r, const kb::rogue::Item& l);

#endif /* _ITEM_HEADER_PP_KBROGUE_ */
