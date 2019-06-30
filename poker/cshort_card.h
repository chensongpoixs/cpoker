/********************************************************************
created: 		2019-06-27

author:			chensong

purpose:		poker algorithms
*********************************************************************/


#ifndef _C_SHORT_CARD_H_
#define _C_SHORT_CARD_H_

#include "cshort_define.h"
namespace chen {
	
	/** 
	* 初始化牌的数据
	* @param deck: 牌的数据 in  out
	**/
	void init_deck(int32 *deck);

	/** 
	*  洗牌  
	*  @param deck: 牌的数据 in  out
	**/
	void shuffle_deck(int32 *deck);


	/**
	* 从七张牌找出最好五张最大牌
	* @param seven_cards: 七张牌   in
	* @param five_cards: 五张牌    in | out
	* return 返回值 牌的大小
	*/
	int32 find_seven_hand(int32 seven_cards[7], int32 *five_cards[5]);

	/** 
	* 获取五牌的值
	*  @param hand: 五张牌开始地址   in
	*  @return 返回值： 牌的大小
	**/
	int32 seach_five_cards(int32 * hand);

	/**
	* 获取五牌的值
	*  @param card1: 第一张牌   in
	*  @param card2: 第二张牌   in
	*  @param card3: 第三张牌   in
	*  @param card4: 第四张牌   in
	*  @param card5: 第五张牌   in
	*  @return 返回值： 牌的大小
	**/
	int32 seach_five_cards(int32 card1, int32 card2, int32 card3, int32 card4, int32 card5);

	/** 
	* 查找 数组的数据的下标
	*  @param key: 五张牌的唯一值  => "后面 8位相乘的值"  in 
	*  @return 返回值： 五张牌对应的大小的值
	**/
	int32 find_array(int32 key);

	/**
	*  返回牌型
	*  @param value: 五张牌的唯一值   in
	*  @return 返回值：牌型 看 ESHORTS_ENUM
	**/
	int32 card_type(int32 value);
} // !namespace chen


#endif // !#define _C_SHORT_CARD_H_