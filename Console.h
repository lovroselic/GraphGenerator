#pragma once
#ifndef CONSOLE
#define CONSOLE

void printArray(int* data, int lenght);

template <typename T1, typename T2>
void printVector(std::vector<std::tuple<T1, T2>>& vct) {
	for (auto v : vct) {
		std::cout << std::get<0>(v) << "\t" << std::get<1>(v) << std::endl;
	}
}


template <typename T>
void printVector(std::vector<T>& vct) {
	for (auto v : vct) {
		std::cout << v << std::endl;
	}
}

template <typename T>
void print2DVector(std::vector<std::vector<T>>& vct) {
	for (const auto& row : vct) {
		for (const auto& col : row) {
			std::cout << col << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return;
}

template <typename T>
void print3DVector(std::vector<std::vector<std::vector<T>>>& vct) {
	for (const auto& row : vct) {
		for (const auto& col : row) {
			for (const auto& instance : col) {
				std::cout << instance;
			}
			std::cout << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return;
}

template <typename T1, typename T2>
void printMap(std::map<T1, T2> map) {
	for (const auto& el : map) {
		std::cout << el.first << "\t-> " << el.second << std::endl;
	}
};

#endif // !CONSOLE
