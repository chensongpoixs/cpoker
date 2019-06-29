/************************************************
created: 		2019-06-25

author:			chensong

purpose:		poker algorithms
*************************************************/
#include "clog.h"
#include "cpoker_algorithms.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
namespace chen {
	
	static int index = 0;
	static int show_index = 0;
	std::vector<int>  m_same_flower; // 同花顺
	std::vector<int>  m_same; //同花

	std::vector<int> m_flower; //顺子
	std::vector<int> m_height; //高牌
	std::vector<int> m_four; //四条
	std::vector<int> m_gourd; // 葫芦
	std::vector<int> m_three_article; //三条
	std::vector<int> m_two_pair; //两条
	std::vector<int> m_first_pair; //一对

	std::vector<cpoker_data> m_data; // 所有的牌的数据排序后的顺序

	std::vector<cpoker_data> m_same_data; //同花和同花顺的数据
	std::vector<cpoker_data> m_height_data; //高牌和顺子的数据
	std::vector<cpoker_data> m_part_data; // 后面的数据----> 




	std::set<int > m_data_map;


	std::vector<int> m_temp_data; // 测试使用
	std::map<int, std::string> m_key_map; //同花顺和顺子 map
	std::map<int, std::string> m_four_key_map; // 四条 map
	std::map<int, std::string> m_ground_key_map; // 葫芦 map
	std::map<int, std::string> m_three_key_map; // 三条 map
	std::map<int, std::string> m_two_key_map; // 两对 map
	std::map<int, std::string> m_first_key_map; //一对 map

	static const int START = 4; // 德州扑克 是0 短牌是 4
	static const int END = 13;

	//static const int MIDDLE = 11;
	static const int cards = 5;

	static int m_same_index = 0; // 同花顺和顺子中特殊位置A的下标的保存



	void same_flower()
	{
		//同花和同花顺有多少种可能
	
		int five_start;
		for (int i = END - 1; i >= START; --i)
		{

			five_start = i - START + 1;
			// 判断是否可以排序
			if (five_start < cards)
			{
				continue;
			}
			// 2 
			for (int index2 = i; index2 >= START; --index2)
			{
				if (index2 != i)
				{
					// 3. 
					for (int index3 = index2; index3 >= START; --index3)
					{
						if (index3 != i && index3 != index2)
						{
							// 4. 
							for (int index4 = index3; index4 >= START; --index4)
							{
								if (index4 != i && index4 != index3 && index4 != index2)
								{
									// 5.
									for (int index5 = index4; index5 >= START; --index5)
									{
										if (index5 != i && index5 != index2 && index5 != index3 && index5 != index4)
										{
											num_show(i, index2, index3, index4, index5);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}






	void num_show(int v1, int v2, int v3, int v4, int v5)
	{

		//for (int i = v5; i < 15; ++i)
		//for (int i = v5 ; i >= START; --i)
		{
			++index;
			++index;
			int hex = (0x01 << (v1 & 0xFF)) | (0x01 << (v2 & 0xFF)) | (0x01 << (v3 & 0xFF)) | (0x01 << (v4 & 0xFF)) | (0x01 << (v5 & 0xFF));

			//printf("hex ==> [%d][]\n", hex);

			if (!m_data_map.insert(hex).second)
			{
				ERROR_EX_LOG("error hex = %d", hex);
			}

			switch (hex)
			{
			//case 0x1F: // 2, 3, 4, 5, 6  // 31
			//case 0x3E: // 3, 4, 5, 6, 7 //62
			//case 0x7C: // 4, 5, 6, 7, 8 // 124
			//case 0xF8: // 5, 6, 7, 8, 9 // 248
			case 0x1F0: // 6, 7, 8, 9, 10 // 496
			case 0x3E0: // 7, 8, 9, 10, J // 992
			case 0x7C0: // 8, 9, 10, J, Q // 1984
			case 0xF80: // 9, 10, J, Q , K// 3968
			{
				m_same_flower.insert(m_same_flower.begin() + m_same_index, hex);
				m_flower.insert(m_flower.begin() + m_same_index, hex);
				++m_same_index;
				break;
			}
				//case 0x21E: // A, 6, 7, 8, 9 // 542
			//case 0x1E01: // 10, J, Q, K, A // 7681
			//{
			//	//顺子
			//	//printf("index = %d,[straight] card[1] = %d, card[2] = %d, card[3] = %d, card[4] = %d, card[5] = %d\n", index, v1, v2, v3, v4, i);
			//	//m_same_flower.push_back(hex);
			//	//m_same_flower[5] = hex;
			//	// 放到同花顺的尾巴
			//	m_same_flower.insert(m_same_flower.begin(), hex);
			//	//颜色不一样的
			//	m_flower.insert(m_flower.begin(), hex);
			//	break;
			//}
			//case 0x100F: // A, 2, 3, 4, 5 // 4111 德州扑克
			case 0x10F0: // A, 6, 7, 8, 9 // 4336   短牌
			{
				m_same_flower.push_back(hex);
				m_flower.push_back(hex);
				break;
			}
			case 0x1F00: //  10, J, Q, K , A// 7936

						 //case  0x3E: // 6, 7, 8, 9, 10   // 62
						 //case 0x7C: //  7, 8, 9, 10, J  // 124
						 //case 0xF8: //  8, 9, 10, J, Q  // 248
						 //case 0x1F0: // 9, 10, J, Q, K // 496
						 //case 0x3E0: // 10, J, Q, K, A // 992
			{
				// 先插入 皇家同花顺 再插入 A, 2, 3, 4, 5
				m_same_flower.push_back(hex);
				m_flower.push_back(hex);
				++m_same_index;
				// 保证插入同花顺最小的前面

				//m_same_flower.insert(m_same_flower.size() >  0 ?   (m_same_flower.size() -1 + m_same_flower.begin()) : m_same_flower.begin() , hex);
				//	m_flower.insert(m_flower.size() >  0 ? (m_flower.size() - 1 + m_flower.begin()) : m_flower.begin(), hex);
				break;
			}


			default:
				// 高牌
				//if (0 == v1 || 0 == v2 || 0 == v3 || 0 == v4 || 0 == v5)   // A
				//{
				//	m_temp_data.push_back(hex);
				//	m_same.insert(m_same.begin() + m_same_index, hex);
				//	m_height.insert(m_height.begin() + m_same_index, hex);
				//	++m_same_index;
				//}
				//else
				{
					m_same.push_back(hex);
					m_height.push_back(hex);
				}
				break;
			}
			//printf("hex ==> %d\n", hex);
			std::string _cards = show_data(v1, v2, v3, v4, v5);
			if (!m_key_map.insert(std::make_pair(hex, _cards)).second)
			{
				ERROR_EX_LOG(" insert  hex = %d, cards = %s", hex, _cards.c_str());
			}
			//SYSTEM_LOG("index = %d, hex = [%d], card[1] = %d, card[2] = %d, card[3] = %d, card[4] = %d, card[5] = %d\n", index, hex, v1, v2, v3, v4, v5);
		}
	}

	void show_four()
	{
		//int start = 6;  // 6 
		//int end = 15;   // A
		int four_index = 0;
		for (int i = END - 1; i >= START; --i)
		{
			for (int j = END - 1; j >= START; --j)
			{
				if (j != i)
				{
					++index;// 14 8
					int hex = cperms[i ] * cperms[i ] * cperms[i ] * cperms[i ] * cperms[j];
					// 倒着插入 
					m_four.push_back(hex);
					
					std::string _cards = show_data(i, i, i, i, j);
					if (!m_four_key_map.insert(std::make_pair(hex, _cards)).second)
					{
						ERROR_EX_LOG(" insert hour hex = %d, cards = %s", hex, _cards.c_str());
					}
				}
			}
		}
	}

	void show_straight_hight()
	{

		int start = 6;  // 6 
		int end = 15;   // A


		int five_start;

		for (int i = start; i < end; ++i)
		{
			five_start = end - i;
			if (five_start < 4)
			{
				continue;;
			}
			for (int j = 0; j < five_start; ++j)
			{

				straight_hight_show(i, i + j + 1, i + j + 2, i + j + 3, i + j + 4);
			}
		}
	}

	void straight_hight_show(int v1, int v2, int v3, int v4, int v5)
	{


		for (int i = v5; i < 15; ++i)
		{
			++index;
			int hex = (0x01 << (v1 - 5)) | (0x01 << (v2 - 5)) | (0x01 << (v3 - 5)) | (0x01 << (v4 - 5)) | (0x01 << (i - 5));
			printf("hex ==> %d\n", hex);
			switch (hex)
			{
			case  0x3E: // 6, 7, 8, 9, 10
			case 0x7C: //  7, 8, 9, 10, J
			case 0xF8: //  8, 9, 10, J, Q
			case 0x1F0: // 9, 10, J, Q, K
			case 0x3E0: // 10, J, Q, K, A
			{
				//顺子
				printf("index = %d,[straight] card[1] = %d, card[2] = %d, card[3] = %d, card[4] = %d, card[5] = %d\n", index, v1, v2, v3, v4, i);

				break;
			}
			default:
				// 高牌
				printf("index = %d,[heiht] card[1] = %d, card[2] = %d, card[3] = %d, card[4] = %d, card[5] = %d\n", index, v1, v2, v3, v4, i);
				break;
			}
		}
	}

	void show_gourd()
	{
		//int start = 6;  // 6 
		//int end = 15;   // A
		int gourd_index = 0; // A
		for (int i = END - 1; i >= START; --i)
		{
			for (int j = END - 1; j >= START; --j)
			{
				if (j != i)
				{
					++index;
					// 真实的值 
					int hex = (cperms[i] & 0xFF) * (cperms[i ] & 0xFF) * (cperms[i ] & 0xFF) * (cperms[j ] & 0xFF) * (cperms[j] & 0xFF);
					//cperms[i - start];
					m_gourd.push_back(hex);

					std::string _cards = show_data(i, i, i, j, j);
					if (!m_ground_key_map.insert(std::make_pair(hex, _cards)).second)
					{
						ERROR_EX_LOG(" insert hour hex = %d, cards = %s", hex, _cards.c_str());
					}
				}
			}
		}
	}

	void show_three_article()
	{
		int three_index = 0;
		// 下标 3 和 4 时 为 'A' 移动前面
		int three_index3_4_A = 0;   
		for (int i = END - 1; i >= START; --i)
		{
			for (int j = END - 1; j >= START; --j)
			{
				if (j != i)
				{
					for (int k = j; k >= START; --k)
					{
						if (k != j && k != i)
						{
							++index;
							//three_article_show(i, i, i, j, k);
							int hex = (cperms[i] & 0xFF) * (cperms[i] & 0xFF) * (cperms[i] & 0xFF) * (cperms[j] & 0xFF) * (cperms[k] & 0xFF);
							m_three_article.push_back(hex);
							std::string _cards = show_data(i, i, i, j, k);
							if (!m_three_key_map.insert(std::make_pair(hex, _cards)).second)
							{
								ERROR_EX_LOG(" insert hour hex = %d, cards = %s", hex, _cards.c_str());
							}
						}
					}
				}
			}
		}
	}

	void three_article_show(int v1, int v2, int v3, int v4, int v5)
	{
		++index;
		// v4 -> v3
		//****** v4 -> v5 是开始位置的标记
		// 真实的值 
		//cperms[i - start];
		int hex = (cperms[v1] & 0xFF) * (cperms[v2] & 0xFF) * (cperms[v3 ] & 0xFF) * (cperms[v4 ] & 0xFF) * (cperms[v5] & 0xFF);
		
		std::string _cards = show_data(v1, v2, v3, v4, v5);
		if (!m_ground_key_map.insert(std::make_pair(hex, _cards)).second)
		{
			ERROR_EX_LOG(" insert hour hex = %d, cards = %s", hex, _cards.c_str());
		}
		/*if (v4 == 0)
		{
			m_three_article.push_back(hex);
		}*/

		if (v4 == 0)
		{
			m_three_article.insert(m_gourd.begin() + m_gourd.size() - v3, hex);
		}
		else
		{
			m_three_article.push_back(hex);
		}
		
		m_three_article.push_back(hex);

	}

	void two_pair_show(int v1, int v2, int v3, int v4, int v5)
	{
		++index;
		// 真实的值 
		//cperms[i - start];
		int hex = (cperms[v1 - 6] & 0xFF) * (cperms[v2 - 6] & 0xFF) * (cperms[v3 - 6] & 0xFF) * (cperms[v4 - 6] & 0xFF) * (cperms[v5 - 6] & 0xFF);
		m_two_pair.push_back(hex);
		printf("index = %d, card[1] = %d, card[2] = %d, card[3] = %d, card[4] = %d, card[5] = %d\n", index, v1, v2, v3, v4, v5);

	}

	void show_two_pair()
	{
		//int start = 6;  // 6 
		//int end = 15;   // A
		int _two_index = 0;
		for (int i = END - 1; i >= START; --i)
		{
			// 从 第一个一对 的下标开始计算
			for (int j = i; j >= START; --j)
			{
				if (j != i)
				{
					for (int k = END - 1; k >= START; --k)
					{
						if (k != j && k != i)
						{
							//two_pair_show(i, i, j, j, k);
							++index;
							// 真实的值 
							//cperms[i - start];
							int hex = (cperms[i] & 0xFF) * (cperms[i] & 0xFF) * (cperms[j] & 0xFF) * (cperms[j] & 0xFF) * (cperms[k] & 0xFF);
							
							m_two_pair.push_back(hex);
							std::string _cards = show_data(i, i, j, j, k);
							if (!m_two_key_map.insert(std::make_pair(hex, _cards)).second)
							{
								ERROR_EX_LOG(" two key map insert hour hex = %d, cards = %s", hex, _cards.c_str());
							}
						}
					}
				}
			}
		}
	}

	void first_pair_show(int v1, int v2, int v3, int v4, int v5)
	{
		++index;
		// 真实的值 
		//cperms[i - start];
		int hex = (cperms[v1 - 6] & 0xFF) * (cperms[v2 - 6] & 0xFF) * (cperms[v3 - 6] & 0xFF) * (cperms[v4 - 6] & 0xFF) * (cperms[v5 - 6] & 0xFF);
		m_first_pair.push_back(hex);
		printf("index = %d, card[1] = %d, card[2] = %d, card[3] = %d, card[4] = %d, card[5] = %d\n", index, v1, v2, v3, v4, v5);

	}

	void show_first_pair()
	{

		// 根据 对

		//int start = 6;  // 6 
		//int end = 15;   // A
		int _first_index_1 = 0;
		int _first_index = 0;
		// 当前数组的下标起位置
		int  _cur_array = 0;
		int _cur_array_index = 0;
		for (int i = END - 1; i >= START; --i)
		{
			for (int j = END - 1; j >= START; --j)
			{
				if (j != i)
				{
					// 从 第一个一对 的下标开始计算
					for (int k = j; k >= START; --k)
					{
						if (k != j && k != i)
						{
							for (int q = k; q >= START; --q)
							{
								if (q != k && q != j && q != i)
								{	
									int hex = (cperms[i] & 0xFF) * (cperms[i] & 0xFF) * (cperms[k] & 0xFF) * (cperms[j] & 0xFF) * (cperms[q] & 0xFF);
									
									m_first_pair.push_back(hex);
									
									std::string _cards = show_data(i, i, k, j, q);
									if (!m_first_key_map.insert(std::make_pair(hex, _cards)).second)
									{
										ERROR_EX_LOG(" first key map insert hour hex = %d, cards = %s", hex, _cards.c_str());
									}
								}
							}
						}
					}
				}
			}
		}
	}

	void logic_show()
	{
		// 短牌: 皇家同花顺>同花顺>四条>同花>葫芦>三条>顺子>两对>一对>高牌；
		std::fstream in;
		in.open("chenli.log", std::ios::out | std::ios::trunc);
		if (!in.is_open())
		{
			return;
		}
		std::string str_buf;//
						
		/// 同花顺和同花的
		std::fstream same_in;
		
		same_in.open("same_flower.log", std::ios::out | std::ios::trunc);
		if (!same_in.is_open())
		{
			ERROR_EX_LOG(" open file not failed same_flower");
			return;
		}


		//  短牌排序
		std::fstream same_in_data;

		same_in_data.open("sort_all_data.log", std::ios::out | std::ios::trunc);
		if (!same_in_data.is_open())
		{
			ERROR_EX_LOG(" open file not failed same_flower");
			return;
		}

		SYSTEM_LOG("--------------same_flower-------------\n");
		str_buf = "----------------same_flower-------------------------";
		in.write(str_buf.c_str(), str_buf.length());
		in.write("\n", 1);
		// 1. 同花顺
		for (std::vector<int>::const_iterator iter = m_same_flower.begin(); iter != m_same_flower.end(); ++iter)
		{
			++show_index;
			
			std::map<int, std::string>::const_iterator value_iter = m_key_map.find(*iter);
			if (value_iter != m_key_map.end())
			{
				
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				m_same_data.push_back(_data);
				str_buf.clear();
				str_buf.append("index = [").append(std::to_string(index)).append("], show_index = [").append(std::to_string(show_index)).append("]");
				str_buf.append(", hex = [").append(std::to_string(*iter)).append("]");
				str_buf.append(", cards = [").append(value_iter->second).append("]");
				in.write(str_buf.c_str(), str_buf.length());
				in.write("\n", 1);
				str_buf.clear();
				str_buf.append(std::to_string(show_index)).append("\t ").append(std::to_string(*iter)).append("\t ").append(value_iter->second);
				same_in.write(str_buf.c_str(), str_buf.length());
				same_in.write("\n", 1);

				/*if (static_cast<int>(flushes[*iter ]) != show_index)
				{
					ERROR_EX_LOG("show_index = %d,  persm = %d, %d, %s", show_index,  cperms[*iter - 1], cperms[*iter ], str_buf.c_str());
				}*/


			//	SYSTEM_LOG("index = [%d], show_index = [%d], hex=[%d], cards = [%s]\n", index, show_index, *iter, value_iter->second.c_str());
			}
			else
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				//_data.m_cards = value_iter->second;
				m_data.push_back(_data);
			//	SYSTEM_LOG("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
			}
			
			//m_data.emplace()
		}

		SYSTEM_LOG(" -----------1. show_index = [%d]-------------------", show_index);
		SYSTEM_LOG("--------------four-------------\n");
		str_buf = "----------------four-------------------------";
		in.write(str_buf.c_str(), str_buf.length());
		in.write("\n", 1);
		//2. 四条
		for (std::vector<int>::const_iterator iter = m_four.begin(); iter != m_four.end(); ++iter)
		{
			++show_index;
			
			std::map<int, std::string>::const_iterator value_iter = m_four_key_map.find(*iter);
			if (value_iter != m_four_key_map.end())
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				m_part_data.push_back(_data);
				str_buf.clear();
				str_buf.append("index = [").append(std::to_string(index)).append("], show_index = [").append(std::to_string(show_index)).append("]");
				str_buf.append(", hex = [").append(std::to_string(*iter)).append("]");
				str_buf.append(", cards = [").append(value_iter->second).append("]");
				in.write(str_buf.c_str(), str_buf.length());
				in.write("\n", 1);
				//SYSTEM_LOG("index = [%d], show_index = [%d], hex=[%d], cards = [%s]\n", index, show_index, *iter, value_iter->second.c_str());
			}
			else
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				//_data.m_cards = value_iter->second;
				m_data.push_back(_data);
			//	SYSTEM_LOG("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
			}
			//m_four_key_map
			//printf("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
		}
		SYSTEM_LOG(" -----------1. show_index = [%d]-------------------", show_index);
		SYSTEM_LOG("--------------same-------------\n");
		str_buf = "----------------same-------------------------";
		in.write(str_buf.c_str(), str_buf.length());
		in.write("\n", 1);
		// 3. 同花
		for (std::vector<int>::const_iterator iter = m_same.begin(); iter != m_same.end(); ++iter)
		{
			++show_index;

			std::map<int, std::string>::const_iterator value_iter = m_key_map.find(*iter);
			if (value_iter != m_key_map.end())
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				m_same_data.push_back(_data);
				str_buf.clear();
				str_buf.append("index = [").append(std::to_string(index)).append("], show_index = [").append(std::to_string(show_index)).append("]");
				str_buf.append(", hex = [").append(std::to_string(*iter)).append("]");
				str_buf.append(", cards = [").append(value_iter->second).append("]");
				in.write(str_buf.c_str(), str_buf.length());
				in.write("\n", 1);
				str_buf.clear();
				str_buf.append(std::to_string(show_index)).append("\t ").append(std::to_string(*iter)).append("\t ").append(value_iter->second);
				same_in.write(str_buf.c_str(), str_buf.length());
				same_in.write("\n", 1);
				/*if (static_cast<int>(flushes[*iter]) != show_index)
				{
				ERROR_EX_LOG("show_index = %d,  persm = %d, %d, %s", show_index, cperms[*iter - 1], cperms[*iter], str_buf.c_str());
				}*/
				//	SYSTEM_LOG("index = [%d], show_index = [%d], hex=[%d], cards = [%s]\n", index, show_index, *iter, value_iter->second.c_str());
			}
			else
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				//_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				ERROR_LOG("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
			}
		}

		SYSTEM_LOG(" -----------1. show_index = [%d]-------------------", show_index);
		// 4. 葫芦
		SYSTEM_LOG("--------------m_gourd---------------\n");
		str_buf = "----------------m_gourd-------------------------";
		in.write(str_buf.c_str(), str_buf.length());
		in.write("\n", 1);
		for (std::vector<int>::const_iterator iter = m_gourd.begin(); iter != m_gourd.end(); ++iter)
		{
			++show_index;

			//m_ground_key_map
			std::map<int, std::string>::const_iterator value_iter = m_ground_key_map.find(*iter);
			if (value_iter != m_ground_key_map.end())
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				m_part_data.push_back(_data);
				str_buf.clear();
				str_buf.append("index = [").append(std::to_string(index)).append("], show_index = [").append(std::to_string(show_index)).append("]");
				str_buf.append(", hex = [").append(std::to_string(*iter)).append("]");
				str_buf.append(", cards = [").append(value_iter->second).append("]");
				in.write(str_buf.c_str(), str_buf.length());
				in.write("\n", 1);
				//SYSTEM_LOG("index = [%d], show_index = [%d], hex=[%d], cards = [%s]\n", index, show_index, *iter, value_iter->second.c_str());
			}
			else
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				//	_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				ERROR_LOG("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
			}
			//	printf("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
		}
		SYSTEM_LOG(" -----------1. show_index = [%d]-------------------", show_index);
		// 三条m_three_article
		SYSTEM_LOG("------------m_three_article------------\n");
		str_buf = "----------------m_three_article-------------------------";
		in.write(str_buf.c_str(), str_buf.length());
		in.write("\n", 1);
		for (std::vector<int>::const_iterator iter = m_three_article.begin(); iter != m_three_article.end(); ++iter)
		{
			++show_index;

			//m_ground_key_map
			std::map<int, std::string>::const_iterator value_iter = m_three_key_map.find(*iter);
			if (value_iter != m_three_key_map.end())
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				m_part_data.push_back(_data);
				str_buf.clear();
				str_buf.append("index = [").append(std::to_string(index)).append("], show_index = [").append(std::to_string(show_index)).append("]");
				str_buf.append(", hex = [").append(std::to_string(*iter)).append("]");
				str_buf.append(", cards = [").append(value_iter->second).append("]");
				in.write(str_buf.c_str(), str_buf.length());
				in.write("\n", 1);
				//SYSTEM_LOG("index = [%d], show_index = [%d], hex=[%d], cards = [%s]\n", index, show_index, *iter, value_iter->second.c_str());
			}
			else
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				//_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				ERROR_LOG("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
			}
			//printf("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
		}
		
		SYSTEM_LOG(" -----------1. show_index = [%d]-------------------", show_index);
		SYSTEM_LOG("--------------flower-------------\n");
		str_buf = "----------------flower-------------------------";
		in.write(str_buf.c_str(), str_buf.length());
		in.write("\n", 1);
		// 5. 顺子
		for (std::vector<int>::const_iterator iter = m_flower.begin(); iter != m_flower.end(); ++iter)
		{
			++show_index;
			
			std::map<int, std::string>::const_iterator value_iter = m_key_map.find(*iter);
			if (value_iter != m_key_map.end())
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				m_height_data.push_back(_data);
				
				str_buf.clear();
				str_buf.append("index = [").append(std::to_string(index)).append("], show_index = [").append(std::to_string(show_index)).append("]");
				str_buf.append(", hex = [").append(std::to_string(*iter)).append("]");
				str_buf.append(", cards = [").append(value_iter->second).append("]");
				in.write(str_buf.c_str(), str_buf.length());
				in.write("\n", 1);

				//if (static_cast<int>(unique5[*iter]) != show_index)
				//{
				//	ERROR_EX_LOG("show_index = %d,  persm = %d, %d, %s", show_index, cperms[*iter - 1], cperms[*iter], str_buf.c_str());
				//}
			//	SYSTEM_LOG("index = [%d], show_index = [%d], hex=[%d], cards = [%s]\n", index, show_index, *iter, value_iter->second.c_str());
			}
			else
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				//	_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				ERROR_LOG("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
			}
		//	printf("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
		}


		
		SYSTEM_LOG(" -----------1. show_index = [%d]-------------------", show_index);
		//两对 m_two_pair
		SYSTEM_LOG("------------------m_two_pair----------------------\n");
		str_buf = "----------------m_two_pair-------------------------";
		in.write(str_buf.c_str(), str_buf.length());
		in.write("\n", 1);
		for (std::vector<int>::const_iterator iter = m_two_pair.begin(); iter != m_two_pair.end(); ++iter)
		{
			++show_index;
			

			// m_two_key_map
			std::map<int, std::string>::const_iterator value_iter = m_two_key_map.find(*iter);
			if (value_iter != m_two_key_map.end())
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				m_part_data.push_back(_data);
				str_buf.clear();
				str_buf.append("index = [").append(std::to_string(index)).append("], show_index = [").append(std::to_string(show_index)).append("]");
				str_buf.append(", hex = [").append(std::to_string(*iter)).append("]");
				str_buf.append(", cards = [").append(value_iter->second).append("]");
				in.write(str_buf.c_str(), str_buf.length());
				in.write("\n", 1);
				//SYSTEM_LOG("index = [%d], show_index = [%d], hex=[%d], cards = [%s]\n", index, show_index, *iter, value_iter->second.c_str());
			}
			else
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
			//	_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				ERROR_LOG("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
			}
			printf("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
		}

		SYSTEM_LOG(" -----------1. show_index = [%d]-------------------", show_index);
		str_buf = "----------------m_first_pair-------------------------";
		in.write(str_buf.c_str(), str_buf.length());
		in.write("\n", 1);
		// 一对
		printf("----------------m_first_pair-------------------------\n");
		for (std::vector<int>::const_iterator iter = m_first_pair.begin(); iter != m_first_pair.end(); ++iter)
		{
			++show_index;
			

			// m_first_key_map
			std::map<int, std::string>::const_iterator value_iter = m_first_key_map.find(*iter);
			if (value_iter != m_first_key_map.end())
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				m_part_data.push_back(_data);
				str_buf.clear();
				str_buf.append("index = [").append(std::to_string(index)).append("], show_index = [").append(std::to_string(show_index)).append("]");
				str_buf.append(", hex = [").append(std::to_string(*iter)).append("]");
				str_buf.append(", cards = [").append(value_iter->second).append("]");
				in.write(str_buf.c_str(), str_buf.length());
				in.write("\n", 1);
			//	SYSTEM_LOG("index = [%d], show_index = [%d], hex=[%d], cards = [%s]\n", index, show_index, *iter, value_iter->second.c_str());
			}
			else
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				//_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				ERROR_LOG("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
			}
			//printf("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
			
		}
		SYSTEM_LOG(" -----------1. show_index = [%d]-------------------", show_index);
		SYSTEM_LOG("--------------height-------------\n");
		str_buf = "----------------height-------------------------";
		in.write(str_buf.c_str(), str_buf.length());
		in.write("\n", 1);
		// 高牌
		for (std::vector<int>::const_iterator iter = m_height.begin(); iter != m_height.end(); ++iter)
		{
			++show_index;
			
			std::map<int, std::string>::const_iterator value_iter = m_key_map.find(*iter);
			if (value_iter != m_key_map.end())
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				m_height_data.push_back(_data);
				str_buf.clear();
				str_buf.append("index = [").append(std::to_string(index)).append("], show_index = [").append(std::to_string(show_index)).append("]");
				str_buf.append(", hex = [").append(std::to_string(*iter)).append("]");
				str_buf.append(", cards = [").append(value_iter->second).append("]");
				in.write(str_buf.c_str(), str_buf.length());
				in.write("\n", 1);
				/*if (static_cast<int>(unique5[*iter]) != show_index)
				{
					ERROR_EX_LOG("show_index = %d,  persm = %d, %d, %s", show_index, cperms[*iter - 1], cperms[*iter], str_buf.c_str());
				}*/
				/*cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				m_data.push_back(_data);*/
			//	SYSTEM_LOG("index = [%d], show_index = [%d], hex=[%d], cards = [%s]\n", index, show_index, *iter, value_iter->second.c_str());
			}
			else
			{
				cpoker_data _data;
				_data.m_index = show_index;
				_data.m_data = *iter;
				//_data.m_cards = value_iter->second;
				m_data.push_back(_data);
				ERROR_LOG("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
			}
			//printf("index = [%d], show_index = [%d], hex=[%d]\n", index, show_index, *iter);
		}
		SYSTEM_LOG(" -----------1. show_index = [%d]-------------------", show_index);
		SYSTEM_LOG("----------------all short start-------------------------");
		str_buf = "----------------all short start-------------------------";
		in.write(str_buf.c_str(), str_buf.length());
		in.write("\n", 1);
	
		SYSTEM_LOG("size = %d， m_same_index = %d\n", m_data_map.size(), m_same_index);
		str_buf = "----------------all short end-------------------------";
		in.write(str_buf.c_str(), str_buf.length());
		in.write("\n", 1);


		// 同花顺 和同花
		std::sort(m_same_data.begin(), m_same_data.end(), sort_data<cpoker_data>);
		// 

		str_buf.clear();
		str_buf = "---------------------------------------------";
		same_in_data.write(str_buf.c_str(), str_buf.length());
		same_in_data.write("\n", 1);
		int same_data_index = 0;
		for (int i = 0; i <= m_same_data[m_same_data.size() - 1].m_data; ++i)
		{
			
			str_buf.clear();
			// 写入数据
			if (i == m_same_data[same_data_index].m_data)
			{
				SYSTEM_LOG(" index = [%d], data = [%d], cards = [%s]", m_same_data[same_data_index].m_index, m_same_data[same_data_index].m_data, m_same_data[same_data_index].m_cards.c_str());
				
				//str_buf = "----------------all short end-------------------------";
				str_buf.append(std::to_string(m_same_data[same_data_index].m_index)).append(", ");
				++same_data_index;
				// write data
			}
			else
			{
				str_buf.append("0, ");
				// write '0'
			}
			same_in_data.write(str_buf.c_str(), str_buf.length());
			//SYSTEM_LOG("i = %d", i);
			if (i % 20 == 0 && i != 0)
			{
				same_in_data.write("\n", 1);
			}
		}
		same_in_data.write("\n", 1);
		str_buf = "---------------------------------------------";
		same_in_data.write(str_buf.c_str(), str_buf.length());
		same_in_data.write("\n", 1);


		// 2. 顺子 和高牌
		std::sort(m_height_data.begin(), m_height_data.end(), sort_data<cpoker_data>);
		str_buf.clear();
		str_buf = "---------------------------------------------";
		same_in_data.write(str_buf.c_str(), str_buf.length());
		same_in_data.write("\n", 1);
		same_data_index = 0;
		for (int i = 0; i <= m_height_data[m_height_data.size() - 1].m_data; ++i)
		{

			str_buf.clear();
			// 写入数据
			if (i == m_height_data[same_data_index].m_data)
			{
				SYSTEM_LOG(" index = [%d], data = [%d], cards = [%s]", m_height_data[same_data_index].m_index, m_height_data[same_data_index].m_data, m_height_data[same_data_index].m_cards.c_str());

				//str_buf = "----------------all short end-------------------------";
				str_buf.append(std::to_string(m_height_data[same_data_index].m_index)).append(", ");
				++same_data_index;
				// write data
			}
			else
			{
				str_buf.append("0, ");
				// write '0'
			}
			same_in_data.write(str_buf.c_str(), str_buf.length());
			//SYSTEM_LOG("i = %d", i);
			if (i % 20 == 0 && i != 0)
			{
				same_in_data.write("\n", 1);
			}
		}
		same_in_data.write("\n", 1);
		str_buf = "---------------------------------------------";
		same_in_data.write(str_buf.c_str(), str_buf.length());
		same_in_data.write("\n", 1);


		// 3. 其他的牌型   data
		std::sort(m_part_data.begin(), m_part_data.end(), sort_data<cpoker_data>);
		str_buf.clear();
		str_buf = "---------------------------------------------";
		same_in_data.write(str_buf.c_str(), str_buf.length());
		same_in_data.write("\n", 1);
		same_data_index = 0;
		for (uint32 i = 0; i < m_part_data.size(); ++i)
		{
			str_buf.clear();
			str_buf.append(std::to_string(m_part_data[i].m_data)).append(", ");
			same_in_data.write(str_buf.c_str(), str_buf.length());
			if (i % 20 == 0 && i != 0)
			{
				same_in_data.write("\n", 1);
			}
		}
		same_in_data.write("\n", 1);
		str_buf = "---------------------------------------------";
		same_in_data.write(str_buf.c_str(), str_buf.length());
		same_in_data.write("\n", 1);
		str_buf.clear();
		str_buf = "---------------------------------------------";
		same_in_data.write(str_buf.c_str(), str_buf.length());
		same_in_data.write("\n", 1);
		same_data_index = 0;
		for (uint32 i = 0; i < m_part_data.size(); ++i)
		{
			str_buf.clear();
			str_buf.append(std::to_string(m_part_data[i].m_index)).append(", ");
			same_in_data.write(str_buf.c_str(), str_buf.length());
			if (i % 20 == 0 && i != 0)
			{
				same_in_data.write("\n", 1);
			}
		}
		same_in_data.write("\n", 1);
		str_buf = "---------------------------------------------";
		same_in_data.write(str_buf.c_str(), str_buf.length());
		same_in_data.write("\n", 1);
		// 4. index

		/*for (std::vector<cpoker_data>::const_iterator iter = m_same_data.begin(); iter != m_same_data.end(); ++iter)
		{
		}*/


		// 排序一下
		//SYSTEM_LOG("----------------short array sort start-------------------------");
		//std::sort(m_part_data.begin(), m_part_data.end(), sort_data<cpoker_data>);
		////SYSTEM_LOG("----------------short array sort end  -------------------------");
		//SYSTEM_LOG("----------------short array sort show  start-------------------------");
		//int _temp_index = 0;
		//for (std::vector<cpoker_data>::const_iterator iter = m_part_data.begin(); iter != m_part_data.end(); ++iter)
		//{
		//	if (products[_temp_index] != iter->m_data || values[_temp_index] != iter->m_index)
		//	{
		//		ERROR_EX_LOG("products[%d] = %d, values[%d] = %d, data = [%d], index = [%d], cards = [%s]", _temp_index, products[_temp_index], _temp_index, values[_temp_index], iter->m_data, iter->m_index, iter->m_cards.c_str());
		//	}
		//	++_temp_index;
		//	//SYSTEM_LOG(" data = [%d], index = [%d], cards = [%s]", iter->m_data, iter->m_index, iter->m_cards.c_str());
		//}
		//SYSTEM_LOG("----------------short array sort show  end-------------------------");
		if (in.is_open())
		{
			in.close();
		}

		if (same_in.is_open())
		{
			same_in.close();
		}


		if (same_in_data.is_open())
		{
			same_in_data.close();
		}


	}

	static std::string get_key(int key)
	{
		switch (key)
		{
		case 0:
		{
			return "2";
			break;
		}
		case 1:
		{
			return "3";
			break;
		}
		case 2:
		{
			return "4";
			break;
		}
		case 3:
		{
			return "5";
			break;
		}
		case 4:
		{
			return "6";
			break;
		}
		case 5:
		{
			return "7";
			break;
		}
		case 6:
		{
			return "8";
			break;
		}
		case 7:
		{
			return "9";
			break;
		}
		case 8:
		{
			return "10";
			break;
		}
		case 9:
		{
			return "J";
			break;
		}
		case 10:
		{
			return "Q";
			break;
		}
		case 11:
		{
			return "K";
			break;
		}
		case 12:
		{
			return "A";
			break;
		}
		default:
			break;
		}
	}
	std::string show_data(int v1, int v2, int v3, int v4, int v5)
	{
		std::string str_buf;
		str_buf.clear();
		str_buf .append( get_key(v1)).append( "-" + get_key(v2)) .append("-" + get_key(v3)).append("-" + get_key(v4)).append("-" + get_key(v5)) ;
		return str_buf;
	}

} // namespace chen