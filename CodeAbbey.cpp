/*
	selection of helper functions
	v1.2
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "CodeAbbey.h"

std::string joinVector(const std::vector<std::string>& data, const std::string separator) {
	std::string result = "";
	if (data.size() == 0) return result;
	result += data.at(0);
	if (data.size() > 1) {
		for (auto i = 1; i < data.size(); i++) {
			result += separator;
			result += data.at(i);
		}
	}
	return result;
}

std::vector<std::string> loadData(std::string name) {
	try {
		std::ifstream file;
		std::string line;
		std::vector<std::string> data;
		file.open(name);
		if (!file) {
			throw std::runtime_error("Could not open file: " + name);
		}
		while (std::getline(file, line)) {
			data.push_back(line);
		}

		file.close();
		return data;
	}

	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return {};
	}
}

std::vector<std::string> splitString(std::string str, const std::string separator) {
	std::vector<std::string> result;
	while (str.size()) {
		auto index = str.find(separator);
		if (index != std::string::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + separator.size());
		}
		else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}

std::vector<std::string> splitString(std::string str) {
	std::vector<std::string> result;
	for (int i = 0; i < str.size(); i++) {
		result.push_back(str.substr(i, 1));
	}
	return result;
}

std::vector<int> stringVectorToInt(std::vector<std::string>& vct) {
	std::vector<int> data;
	for (auto& el : vct) {
		data.push_back(std::stoi(el));
	}
	return data;
}

std::vector<float> stringVectorToFloat(std::vector<std::string>& vct) {
	std::vector<float> data;
	for (auto& el : vct) {
		data.push_back(std::stof(el));
	}
	return data;
}

std::vector<int> splitToInt(std::string str, const std::string separator) {
	std::vector<std::string> data = splitString(str, separator);
	std::vector<int> intData = stringVectorToInt(data);
	return intData;
}

std::vector<int> splitToInt(std::string str) {
	std::vector<std::string> data = splitString(str);
	std::vector<int> intData = stringVectorToInt(data);
	return intData;
}

std::vector<float> splitToFloat(std::string str, const std::string separator) {
	std::vector<std::string> data = splitString(str, separator);
	std::vector<float> floatData = stringVectorToFloat(data);
	return floatData;
}

std::string Compact(std::string str) {
	std::vector<std::string> S = splitString(str);
	std::sort(S.begin(), S.end());
	std::string packed = Pack(S);
	return packed;
}

std::string Pack(std::vector<std::string>& cell) {
	std::string compacted = "";
	std::string pchar = "";
	int count = 0;
	for (auto& c : cell) {
		if (c == pchar) {
			count++;
		}
		else {
			if (count > 0) {
				compacted += std::to_string(count);
				compacted += pchar;
			}
			pchar = c;
			count = 1;
		}
	}
	compacted += std::to_string(count);
	compacted += pchar;

	return compacted;
}

std::string StringToUpper(std::string str) {
	std::string strUp = "";
	for (auto& c : str) {
		strUp += std::toupper(c);
	}
	return strUp;
}

std::vector<std::string> IntToHex(std::vector<int>& ints) {
	std::vector<std::string> hexs;

	for (auto& i : ints) {
		std::ostringstream ss;
		ss.width(2);
		ss.fill('0');
		ss << std::hex << i;
		std::string result = ss.str();
		hexs.push_back(StringToUpper(result));
	}

	return hexs;
}