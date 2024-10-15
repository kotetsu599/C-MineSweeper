#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <sstream>

/*
* 座標は配列を用いて表します。頭の中では  012  のように考えていますが、プログラム上では123456789です。
*                                      345
*                                      678
*/

//それぞれの辺の隣の座標を返す関数
int* get_locations_of_neighbors_of_top_side(int location, int length_of_one_side) {
	int* neighbor_locations = new int[5]; 
	neighbor_locations[0] = location - 1;
	neighbor_locations[1] = location + 1;
	neighbor_locations[2] = location + length_of_one_side - 1;
	neighbor_locations[3] = location + length_of_one_side;
	neighbor_locations[4] = location + length_of_one_side + 1;
	return neighbor_locations;
}

int* get_locations_of_neighbors_of_left_side(int location, int length_of_one_side) {
	int* neighbor_locations = new int[5];
	neighbor_locations[0] = location - length_of_one_side;
	neighbor_locations[1] = location - length_of_one_side + 1;
	neighbor_locations[2] = location + 1;
	neighbor_locations[3] = location + length_of_one_side;
	neighbor_locations[4] = location + length_of_one_side + 1;
	return neighbor_locations;
}

int* get_locations_of_neighbors_of_lower_side(int location, int length_of_one_side) {
	int* neighbor_locations = new int[5]; 
	neighbor_locations[0] = location - 1;
	neighbor_locations[1] = location - length_of_one_side - 1;
	neighbor_locations[2] = location - length_of_one_side;
	neighbor_locations[3] = location - length_of_one_side + 1;
	neighbor_locations[4] = location + 1;
	return neighbor_locations;
}

int* get_locations_of_neighbors_of_right_side(int location, int length_of_one_side) {
	int* neighbor_locations = new int[5]; 
	neighbor_locations[0] = location - length_of_one_side;
	neighbor_locations[1] = location - length_of_one_side - 1;
	neighbor_locations[2] = location - 1;
	neighbor_locations[3] = location + length_of_one_side - 1;
	neighbor_locations[4] = location + length_of_one_side;
	return neighbor_locations;
}

int* get_locations_of_neighbors_of_middle_of_the_pixel(int location, int length_of_one_side) {
	int* neighbor_locations = new int[8]; 
	neighbor_locations[0] = location - 1;
	neighbor_locations[1] = location - length_of_one_side - 1;
	neighbor_locations[2] = location - length_of_one_side;
	neighbor_locations[3] = location - length_of_one_side + 1;
	neighbor_locations[4] = location + 1;
	neighbor_locations[5] = location + length_of_one_side + 1;
	neighbor_locations[6] = location + length_of_one_side;
	neighbor_locations[7] = location + length_of_one_side - 1;
	return neighbor_locations;
}

int main() {
	std::cout << "Enter length of one side:";
	int32_t length_of_one_side;
	std::cin >> length_of_one_side;
	int32_t area = length_of_one_side * length_of_one_side;
	std::cout << "Enter the amount of bombs:";
	int32_t amount_of_bombs;
	std::cin >> amount_of_bombs;
	std::vector<int> pixel;
	for (int i = 0; area > i; i++) {
		pixel.push_back(0);
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, area - 1);
	//爆弾をランダムに置きます。かぶったらiを減らす。
	for (int i = 0; amount_of_bombs > i; i++) {
		int location = dist(gen);
		if (pixel[location] == 9) {
			i = i - 1;
		}
		else {
			pixel[location] = 9;
		}
	}

	//四隅の隣人の座標
	int neighbors_of_top_left[3] = { 1,length_of_one_side,length_of_one_side + 1 };
	int neighbors_of_lower_left[3] = { area - length_of_one_side * 2,area - length_of_one_side * 2 + 1,area - length_of_one_side + 1 };
	int neighbors_of_top_right[3] = { length_of_one_side - 2,length_of_one_side * 2 - 2,length_of_one_side * 2 - 1 };
	int neighbors_of_lower_right[3] = { area - 2,area - length_of_one_side - 2,area - length_of_one_side - 1 };

	//左上(座標は0)
	int bombs = 0;
	if (pixel[0] != 9) {
		for (int i = 0; i < 3; i++) {
			if (pixel[neighbors_of_top_left[i]] == 9) {
				bombs++;
			}
		}
		pixel[0] = bombs;
	}
	//左下(座標は一辺の長さ^2 - 一辺の長さ)
	bombs = 0;
	if (pixel[area - length_of_one_side] != 9) {
		for (int i = 0; i < 3; i++) {
			if (pixel[neighbors_of_lower_left[i]] == 9) {
				bombs++;
			}
		}
		pixel[area - length_of_one_side] = bombs;
	}

	//右上(座標は一辺の長さ-1)
	bombs = 0;
	if (pixel[length_of_one_side - 1] != 9) {
		for (int i = 0; i < 3; i++) {
			if (pixel[neighbors_of_top_right[i]] == 9) {
				bombs++;
			}
		}
		pixel[length_of_one_side - 1] = bombs;
	}
	//右下(座標はarea-1)
	bombs = 0;
	if (pixel[area - 1] != 9) {
		for (int i = 0; i < 3; i++) {
			if (pixel[neighbors_of_lower_right[i]] == 9) {
				bombs++;
			}
		}
		pixel[area - 1] = bombs;
	}

	for (int i = 0; i < area; i++) {
		if (i <= length_of_one_side - 1 && i != 0 && i != length_of_one_side - 1 && pixel[i] != 9) {
			for (int n = 0; n < 5; n++) {
				int* neighbor_locations = get_locations_of_neighbors_of_top_side(i, length_of_one_side);
				if (pixel[neighbor_locations[n]] == 9) {
					pixel[i]++;

				}
				delete[] neighbor_locations;
			}
		}
		
		else if ((i + 1) % length_of_one_side == 0 && i != length_of_one_side - 1 && i != area - 1 && pixel[i] != 9) {
			for (int n = 0; n < 5; n++) {
				int* neighbor_locations = get_locations_of_neighbors_of_right_side(i, length_of_one_side);
				if (pixel[neighbor_locations[n]] == 9) {
					pixel[i]++;
				}
				delete[] neighbor_locations;
			}
		}

		else if (i % length_of_one_side == 0 && i != 0 && i != area - length_of_one_side && pixel[i] != 9) {
			for (int n = 0; n < 5; n++) {
				int* neighbor_locations = get_locations_of_neighbors_of_left_side(i, length_of_one_side);
				if (pixel[neighbor_locations[n]] == 9) {
					pixel[i]++;
				}
				delete[] neighbor_locations;
			}
		}
		else if (i >= area - length_of_one_side && i != area - length_of_one_side && i != area - 1 && pixel[i] != 9) {
			for (int n = 0; n < 5; n++) {
				int* neighbor_locations = get_locations_of_neighbors_of_lower_side(i, length_of_one_side);
				if (pixel[neighbor_locations[n]] == 9) {
					pixel[i]++;
				}
				delete[] neighbor_locations;
			}
		}
		else if (i != 0 && i != length_of_one_side - 1 && i != area - length_of_one_side  && i != area - 1 && pixel[i] != 9) {
			for (int n = 0; n < 8; n++) {
				int* neighbor_locations = get_locations_of_neighbors_of_middle_of_the_pixel(i, length_of_one_side);
				if (pixel[neighbor_locations[n]] == 9) {
					pixel[i]++;
				}
				delete[] neighbor_locations;
			}
		}
	}
	int m = 0;
	std::stringstream buffer;
	for (int i = 0; i < area / length_of_one_side; i++) {
		for (int n = 0; n < length_of_one_side; n++) {
			buffer << (pixel[m] == 9 ? "@" : std::to_string(pixel[m])) << " ";
			m++;
		}
		buffer << "\n";
	}

	std::cout << buffer.str();
	int n;
	std::cin >> n;
}
