#pragma once
#include <fstream>
#include "List.h"
#include<string>
#include"Map.h"
#include "Algorithm.h"
using namespace std;
class Flow {
public:
	~Flow() {
		delete[] excess_flow;
		delete[] height;
		for(int i=0;i<vertexCount;++i)
		delete[] capacity_edge[i];
	}
	Flow(ifstream& file)
	{
		Map<char, int>* Map_from_char_to_number = new Map<char, int>();
		vertexCount = 0;
		int str_num = 1;
		while (!file.eof()) {
			string s1;
			getline(file, s1);
			if (s1.size() >= 5) {//greater than or equal to 5, because this is the minimum possible input(two letters, two spaces,one digit)
				if (!((s1[0] >= 'A' && s1[0] <= 'Z') && (s1[1] == ' '))) {
					throw std::exception(string(("Error entering the first character in the string or missing a space after it. Check the correctness of the input in the file and correct these errors in the line under the number: " + to_string(str_num))).c_str());
				}
				if (!((s1[2] >= 'A' && s1[2] <= 'Z') && (s1[3] == ' '))) {
					throw std::exception(string(("Error entering the second character in the string or missing a space after it. Check the correctness of the input in the file and correct these errors in the line under the number: " + to_string(str_num))).c_str());
				}
				string cur;
				for (int i = 4; i < s1.size(); ++i) {
					if (s1[i] >= '0' && s1[i] <= '9')
						cur += s1[i];
					else {
						throw std::exception(string(("Error entering the third character (bandwidth) in the string or the presence of a space after it.Please note that the bandwidth cannot be negative. Check that you entered the file correctly and correct these errors in the line number: " + to_string(str_num))).c_str());
					}
				}
				if (!Map_from_char_to_number->find_is(s1[0])) {//checking the presence of a symbol in the Map, if it is not present, we write it to the Map and assign it an individual index
					Map_from_char_to_number->insert(s1[0], vertexCount);
					++vertexCount;
				}
				if (!Map_from_char_to_number->find_is(s1[2])) {
					Map_from_char_to_number->insert(s1[2], vertexCount);
					++vertexCount;
				}

			}
			else
			{
				throw std::exception(string(("A data-entry error. Check the correctness of the input in the file and correct these errors in the line under the number: " + to_string(str_num))).c_str());
			}
			++str_num;
		}
		if (Map_from_char_to_number->find_is('S'))
			sourceVertex = Map_from_char_to_number->find('S');
		else {
			throw std::exception("Source is missing");
		}

		if (Map_from_char_to_number->find_is('T'))
			destinationVertex = Map_from_char_to_number->find('T');
		else {
			throw std::exception("Sink is missing");
		}
		file.clear();
		file.seekg(ios::beg);
		excess_flow = new int[vertexCount];
		height = new int[vertexCount];
		capacity_edge = new int* [vertexCount];
		for (int i = 0; i < vertexCount; ++i) {
			excess_flow[i] = 0;
			height[i] = 0;
		}
		for (int i = 0; i < vertexCount; ++i) {
			capacity_edge[i] = new int[vertexCount];
			for (int j = 0; j < vertexCount; ++j)
				capacity_edge[i][j] = 0;
		}
		str_num = 1;
		while (!file.eof()) {
			string s1;
			int vert1, vert2, cap;
			getline(file, s1);
			vert1 = Map_from_char_to_number->find(s1[0]);
			vert2 = Map_from_char_to_number->find(s1[2]);
			if(vert1==vert2)
				throw std::exception(string("The path from the vertex to itself is impossible in the string under the number: "+to_string(str_num)).c_str());
			capacity_edge[vert1][vert2] = stoi(s1.substr(4));
			++str_num;
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int max_flow() {
		if (vertexCount > 2) {
			for (int i = 0; i < vertexCount; i++)
			{
				if (i == sourceVertex)
					continue;
				excess_flow[i] = capacity_edge[sourceVertex][i];
				capacity_edge[i][sourceVertex] += capacity_edge[sourceVertex][i];
			}
			height[sourceVertex] = vertexCount;
			List<int> l;
			int cur;
			int cur_index = 0;
			int old_height;
			for (int i = 0; i < vertexCount; i++)
				if (i != sourceVertex && i != destinationVertex)
					l.push_front(i);
			cur = l.at(0);
			while (cur_index < l.get_size())
			{
				old_height = height[cur];
				discharge(cur);
				if (height[cur] != old_height)
				{
					l.push_front(cur);
					l.remove(++cur_index);
					cur = l.at(0);
					cur_index = 0;
				}
				++cur_index;
				if (cur_index < l.get_size())
					cur = l.at(cur_index);

			}
			return excess_flow[destinationVertex];
		}
		else
			return capacity_edge[0][1];
	}
	void push(int edge, int vertex)
	{
		int f = min(excess_flow[edge], capacity_edge[edge][vertex]);
		excess_flow[edge] -= f;
		excess_flow[vertex] += f;
		capacity_edge[edge][vertex] -= f;
		capacity_edge[vertex][edge] += f;
	}

	void lift(int edge)
	{
		int min = 2 * vertexCount + 1;

		for (int i = 0; i < vertexCount; i++)
			if (capacity_edge[edge][i] && (height[i] < min))
				min = height[i];
		height[edge] = min + 1;
	}

	void discharge(int edge)
	{
		int vertex = 0;
		while (excess_flow[edge] > 0)
		{
			if (capacity_edge[edge][vertex] && height[edge] == height[vertex] + 1)
			{
				push(edge, vertex);
				vertex = 0;
				continue;
			}
			++vertex;
			if (vertex == vertexCount)
			{
				lift(edge);
				vertex = 0;
			}
		}
	}
private:
	int* excess_flow;
	int** capacity_edge;
	int* height;
	int vertexCount, sourceVertex, destinationVertex;
};