#ifndef _ITEM_HEADER_PP_KBROGUE_
#define _ITEM_HEADER_PP_KBROGUE_

namespace kb
{
	namespace rogue
	{
		class Item
		{
			public:
				Item(char mark);
				virtual ~Item() = default;

				virtual void use() = 0;

			protected:
				char mark;
		};
	}
}

#endif /* _ITEM_HEADER_PP_KBROGUE_ */
