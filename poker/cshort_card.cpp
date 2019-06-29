/***********************************************************************************************
created: 		2019-06-27

author:			chensong

purpose:		short card
************************************************************************************************/

#include "cshort_card.h"
#include "clog.h"
#include "cshort_define.h"
#include "crandom.h"
namespace chen {
	void init_deck(int32 * deck)
	{
		//int i, j, n = 0, suit 0;
		int32 n = 0;
		for (int32 i = 0; i < ESTART; ++i)
		{
			for (int32 j = 0; j < EEND; ++j, ++n)
			{
				deck[n] = CPRIMES[j] | (j << ECOLOR_OFFSET) | ECOLOR[i] | (1 << (EHEX + j));
			}
		}
	}

	void shuffle_deck(int32 * deck)
	{
		if (!deck)
		{
			return;
		}

		int32 index = 0;
		uint32 seed = c_rand.rand();
		for (int32 i = 0; i < ESHORT_SIZE - 1; ++i)
		{
			//保证每次第i位的值不会涉及到第i位以前
			index = i + seed % (ESHORT_SIZE - i);
			int32 temp = deck[i];
			deck[i] = deck[index];
			deck[index] = temp;
		}
	}
	int32 find_seven_hand(int32 seven_cards[7], int32 *five_cards[5])
	{
		int32 q , best = 9999, subhand[5];

		for (int32 i = 0; i < 21; ++i)
		{
			for (int32 j = 0; j < 5; ++j)
			{
				subhand[j] = seven_cards[CPERM7[i][j]];
			}
			q = seach_five_cards(subhand);
			if (q < best)
			{
				memcpy(*five_cards, subhand, sizeof(subhand));
				best = q;
			}
		}
		return(best);
	}
	int32 seach_five_cards(int32 * hand)
	{
		int32 c1, c2, c3, c4, c5;

		c1 = *hand++;
		c2 = *hand++;
		c3 = *hand++;
		c4 = *hand++;
		c5 = *hand;

		return(seach_five_cards(c1, c2, c3, c4, c5));
	}
	int32 seach_five_cards(int32 card1, int32 card2, int32 card3, int32 card4, int32 card5)
	{
		int32 q = 0;
		int32 s = 0;

		q = (card1 | card2 | card3 | card4 | card5) >> EHEX;

		//check for Flushes and StraightFlushes
		//检查同花和同花顺
		if (card1 & card2 & card3 & card4 & card5 & 0xF000)
		{
			return(csame_flower[q]);
		}

		// check for Straights and HighCard hands
		//检查顺子和高牌
		s = cstraight_height[q];
		if (s)
		{
			return (s);
		}

		/* let's do it the hard way
		*/
		q = (card1 & 0xFF) * (card2 & 0xFF) * (card3 & 0xFF) * (card4 & 0xFF) * (card5 & 0xFF);
		q = find_array(q);

		return(cshort_values[q]);
	}
	int32 find_array(int32 key)
	{
		int32 low = 0, high = ESHORT_KEY_VALUE, mid;

		while (low <= high)
		{
			mid = (high + low) >> 1;      // divide by two
			if (key < cshort_keys[mid])
			{
				high = mid - 1;
			}
			else if (key > cshort_keys[mid])
			{
				low = mid + 1;
			}
			else
			{
				return(mid);
			}
		}
		ERROR_EX_LOG(" no match found: key = %d", key);
		return(-1);
	}
	int32 card_type(int32 value)
	{
		if (value > 1284)
		{
			return(EHIGH_CARD);
		}
		if (value > 780)
		{
			return(EONE_PAIR);
		}
		if (value > 528) 
		{
			return(ETWO_PAIR);
		}
		if (value > 522)
		{
			return(ESTRAIGHT);
		}
		if (value > 270)
		{
			return(ETHREE_OF_A_KIND);
		}
		if (value > 198)
		{
			return(EFULL_HOUSE);
		}
		if (value > 78)
		{
			return(EFLUSH);
		}
		if (value > 6)
		{
			return(EFOUR_OF_A_KIND);
		}
		if (value > 1)
		{
			return(ESTRAIGHT_FLUSH);
		}
		return (EROYAL_FLUSH);
	}
} // !namespace chen

