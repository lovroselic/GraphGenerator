#pragma once
#ifndef LS_LIB
#define LS_LIB
#define PI 3.14159265

template <typename T>
double average(std::vector<T>& vect) {
	auto const count = static_cast<float>(vect.size());
	return std::accumulate(vect.begin(), vect.end(), 0.0) / count;
}

template <typename T>
double st_dev(std::vector<T>& vect) {
	const double avg = average(vect);
	auto const count = static_cast<float>(vect.size());
	double sum = 0.0;
	for (const auto& v : vect) {
		sum += (v - avg) * (v - avg);
	}
	return std::sqrt(sum / count);
}

template <typename T1, typename T2>
double st_dev(std::vector<T1>& vect, T2 avg) {
	auto const count = static_cast<float>(vect.size());
	double sum = 0.0;
	for (const auto& v : vect) {
		sum += (v - avg) * (v - avg);
	}
	return std::sqrt(sum / count);
}

template <typename T>
T to_radians(T deg) {
	return deg * PI / 180;
}

template <typename T>
T to_degree(T rad) {
	return rad * 180 / PI;
} 

std::string NumberToBin(int n);
int BinToNumber(std::string bin);

#endif // !LS_LIB

