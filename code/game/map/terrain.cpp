#include "GameWin.h"
using namespace std;
using namespace sf;

void GameWin::gen_map() {
    sqlite3_open("map/data.db", &mapDB);
	
    string sql = "CREATE TABLE IF NOT EXISTS tiles(x INT, y INT, z INT, tilt VARCHAR(3));";

    char* messaggeError;
    sqlite3_exec(mapDB, sql.c_str(), NULL, 0, &messaggeError);

	gen_map_t();
	
	 sql = "INSERT INTO tiles (x, y, z, tilt) VALUES ";

	for (int y = 0; y < grid_size; y++) {
		for (int x = 0; x < grid_size; x++) {
			if (x != 0 || y != 0) sql += ", ";
			sql += "(" + to_string(x) + " ," + to_string(y) + " ," + to_string(grid_peaks[y][x]) + " ,'" + get_tilt(y, x) + "')";
		}
	}
	sql += ";";
    sqlite3_exec(mapDB, sql.c_str(), NULL, 0, &messaggeError);
	
    sqlite3_close(mapDB);
	
	gen_map_t_layer();
}

string GameWin::get_tilt(int y, int x) {
	string tilt = "";
	tilt = to_string(grid_peaks[y][x + 1] - grid_peaks[y][x] + 1);
	tilt += to_string(grid_peaks[y + 1][x] - grid_peaks[y][x] + 1);
	tilt += to_string(grid_peaks[y + 1][x + 1] - grid_peaks[y][x] + 2);
	return tilt;
}

int min3(array<int,3> got) {
	int min = 21;
	for (int i = 0; i < 3; i++) {
		min > got[i] ? min = got[i] : min = min;
	}
	return min;
}

int max3(array<int,3> got) {
	int max = -11;
	for (int i = 0; i < 3; i++) {
		max < got[i] ? max = got[i] : max = max;
	}
	return max;
}

int min4(array<int,4> got) {
	int min = 21;
	for (int i = 0; i < 4; i++) {
		min > got[i] ? min = got[i] : min = min;
	}
	return min;
}

int max4(array<int,4> got) {
	int max = -11;
	for (int i = 0; i < 4; i++) {
		max < got[i] ? max = got[i] : max = max;
	}
	return max;
}

void GameWin::soft(int x, int y) {
	unsigned char where_to_check;
	where_to_check = 16;
	if (y != 0) where_to_check |= (1 << 0);
	else where_to_check &= ~(0 << 0);
	if (x != grid_size) where_to_check |= (1 << 1);
	else where_to_check &= ~(0 << 1);
	if (y != grid_size) where_to_check |= (1 << 2);
	else where_to_check &= ~(0 << 2);
	if (x != 0) where_to_check |= (1 << 3);
	else where_to_check &= ~(0 << 3);
	
	if (std::popcount(where_to_check) == 5) {
		if (max4({grid_peaks[y][x + 1], grid_peaks[y][x - 1], grid_peaks[y + 1][x], grid_peaks[y - 1][x]}) - min4({grid_peaks[y][x + 1], grid_peaks[y][x - 1], grid_peaks[y + 1][x], grid_peaks[y - 1][x]}) <= 2) {
			grid_peaks[y][x] = max4({grid_peaks[y][x + 1], grid_peaks[y][x - 1], grid_peaks[y + 1][x], grid_peaks[y - 1][x]}) - 1;
			where_to_check &= ~(1 << 4);
		}
	}
	else if (std::popcount(where_to_check) == 4) {
		if (!(where_to_check & (1 << 0))) {
			if (max3({grid_peaks[y][x + 1], grid_peaks[y][x - 1], grid_peaks[y + 1][x]}) - min3({grid_peaks[y][x + 1], grid_peaks[y][x - 1], grid_peaks[y + 1][x]}) <= 2) {
				grid_peaks[y][x] = max3({grid_peaks[y][x + 1], grid_peaks[y][x - 1], grid_peaks[y + 1][x]}) - 1;
				where_to_check &= ~(1 << 4);
			}
		}
		else if (!(where_to_check & (1 << 1))) {
			if (max3({grid_peaks[y][x - 1], grid_peaks[y + 1][x], grid_peaks[y - 1][x]}) - min3({grid_peaks[y][x - 1], grid_peaks[y + 1][x], grid_peaks[y - 1][x]}) <= 2) {
				grid_peaks[y][x] = max3({grid_peaks[y][x - 1], grid_peaks[y + 1][x], grid_peaks[y - 1][x]}) - 1;
				where_to_check &= ~(1 << 4);
			}
		}
		else if (!(where_to_check & (1 << 2))) {
			if (max3({grid_peaks[y][x + 1], grid_peaks[y][x - 1], grid_peaks[y - 1][x]}) - min3({grid_peaks[y][x + 1], grid_peaks[y][x - 1], grid_peaks[y - 1][x]}) <= 2) {
				grid_peaks[y][x] = max3({grid_peaks[y][x + 1], grid_peaks[y][x - 1], grid_peaks[y - 1][x]}) - 1;
				where_to_check &= ~(1 << 4);
			}
		}
		else {
			if (max3({grid_peaks[y][x + 1], grid_peaks[y + 1][x], grid_peaks[y - 1][x]}) - min3({grid_peaks[y][x + 1], grid_peaks[y + 1][x], grid_peaks[y - 1][x]}) <= 2) {
				grid_peaks[y][x] = max3({grid_peaks[y][x + 1], grid_peaks[y + 1][x], grid_peaks[y - 1][x]}) - 1;
				where_to_check &= ~(1 << 4);
			}
		}
	}
	else {
		if (!(where_to_check & (1 << 0))) {
			if (!(where_to_check & (1 << 1))) {
				if (max(grid_peaks[y][x - 1], grid_peaks[y + 1][x]) - min(grid_peaks[y][x - 1], grid_peaks[y + 1][x]) <= 2) {
					grid_peaks[y][x] = max(grid_peaks[y][x - 1], grid_peaks[y + 1][x]) - 1;
					where_to_check &= ~(1 << 4);
				}
			}
			else if (!(where_to_check & (1 << 2))) {
				if (max(grid_peaks[y][x - 1], grid_peaks[y][x + 1]) - min(grid_peaks[y][x - 1], grid_peaks[y][x + 1]) <= 2) {
					grid_peaks[y][x] = max(grid_peaks[y][x - 1], grid_peaks[y][x + 1]) - 1;
					where_to_check &= ~(1 << 4);
				}
			}
			else {
				if (max(grid_peaks[y][x + 1], grid_peaks[y + 1][x]) - min(grid_peaks[y][x + 1], grid_peaks[y + 1][x]) <= 2) {
					grid_peaks[y][x] = max(grid_peaks[y][x + 1], grid_peaks[y + 1][x]) - 1;
					where_to_check &= ~(1 << 4);
				}
			}
		}
		else if (!(where_to_check & (1 << 1))) {
			if (!(where_to_check & (1 << 2))) {
				if (max(grid_peaks[y][x + 1], grid_peaks[y - 1][x]) - min(grid_peaks[y][x + 1], grid_peaks[y - 1][x]) <= 2) {
					grid_peaks[y][x] = max(grid_peaks[y][x + 1], grid_peaks[y - 1][x]) - 1;
					where_to_check &= ~(1 << 4);
				}
			}
			else {
				if (max(grid_peaks[y + 1][x], grid_peaks[y - 1][x]) - min(grid_peaks[y - 1][x], grid_peaks[y + 1][x]) <= 2) {
					grid_peaks[y][x] = max(grid_peaks[y + 1][x], grid_peaks[y - 1][x]) - 1;
					where_to_check &= ~(1 << 4);
				}
			}
		}
		else {
			grid_peaks[y][x] = max(grid_peaks[y][x + 1], grid_peaks[y - 1][x]) - 1;
			where_to_check &= ~(1 << 4);
		}
	}
	if (where_to_check & (1 << 4)) {
		if (where_to_check & (1 << 0)) {
			if (grid_peaks[y - 1][x] - grid_peaks[y][x] < -1) {
				grid_peaks[y - 1][x] = grid_peaks[y][x] - 1;
				soft (x, y - 1);
			}
			else if (grid_peaks[y - 1][x] - grid_peaks[y][x] > 1) {
				grid_peaks[y - 1][x] = grid_peaks[y][x] + 1;
				soft (x, y - 1);
			}
		}
		if (where_to_check & (1 << 1)) {
			if (grid_peaks[y][x + 1] - grid_peaks[y][x] < -1) {
				grid_peaks[y][x + 1] = grid_peaks[y][x] - 1;
				soft (x + 1, y);
			}
			else if (grid_peaks[y][x + 1] - grid_peaks[y][x] > 1) {
				grid_peaks[y][x + 1] = grid_peaks[y][x] + 1;
				soft (x + 1, y);
			}
		}
		if (where_to_check & (1 << 2)) {
			if (grid_peaks[y + 1][x] - grid_peaks[y][x] < -1) {
				grid_peaks[y + 1][x] = grid_peaks[y][x] - 1;
				soft (x, y + 1);
			}
			else if (grid_peaks[y + 1][x] - grid_peaks[y][x] > 1) {
				grid_peaks[y + 1][x] = grid_peaks[y][x] + 1;
				soft (x, y + 1);
			}
		}
		if (where_to_check & (1 << 3)) {
			if (grid_peaks[y][x - 1] - grid_peaks[y][x] < -1) {
				grid_peaks[y][x - 1] = grid_peaks[y][x] - 1;
				soft (x - 1, y);
			}
			else if (grid_peaks[y][x - 1] - grid_peaks[y][x] > 1) {
				grid_peaks[y][x - 1] = grid_peaks[y][x] + 1;
				soft (x - 1, y);
			}
		}
	}
}

void GameWin::gen_map_t() {
	
	// create gridmap of peaks & necessary stuff
	int gr = grid_size / 2, gr0 = grid_size;
	int x, y, q; // x, y - coordinates; q - peaks weight
	for (y = 0; y <= grid_size; y++) {
		for (x = 0; x <= grid_size; x++) {
			grid_peaks[y][x] = -11;
		}
	}
	
	// set primary peaks
	for (y = 0; y <= grid_size; y+=50) {
		for (x = 0; x <= grid_size; x+=50) {
			switch (y){
				case 0: {
					grid_peaks[y][x] = rand() % 5 + 16;
					break;
				}
				case grid_size / 2: {
					grid_peaks[y][x] = rand() % 5 + 5;
					break;
				}
				case grid_size: {
					grid_peaks[y][x] = rand() % 5 - 10;
					break;
				}
			}
			
		}
	}
	
	// generate regular peaks
	while ((gr % 2 == 0 || gr % 5 == 0)) {
		gr0 = gr;
		if (gr % 2 == 0) gr /= 2;
		else if (gr % 5 == 0) gr /= 5;
		for (y = 0; y <= grid_size; y += gr0) {
			for (x = 0; x <= grid_size; x += gr0) {
				for (int i = 0; i < gr0; i += gr) {
					for (int j = 0; j < gr0; j += gr) {
						if (y + i > grid_size || x + j > grid_size) break;
						if (grid_peaks[y + i][x + j] == -11) {
							q = (gr0 - max(i, j)) / gr;
							grid_peaks[y + i][x + j] = grid_peaks[y][x] * q;
							if (x != grid_size) {
								grid_peaks[y + i][x + j] += grid_peaks[y][x + gr0] * (min(gr0 - i, j) / gr);
								q += min(gr0 - i, j) / gr;
							}
							if (y != grid_size) {
								grid_peaks[y + i][x + j] += grid_peaks[y + gr0][x] * (min(i, gr0 - j) / gr);
								q += min(i, gr0 - j) / gr;
							}
							if (x != grid_size && y != grid_size) {
								grid_peaks[y + i][x + j] += grid_peaks[y + gr0][x] * (min(i, j) / gr);
								q += min(i, j) / gr;
							}
							grid_peaks[y + i][x + j] /= q;
							if (gr != 1) grid_peaks[y + i][x + j] += rand() % 4 - 2;
							else grid_peaks[y + i][x + j] += rand() % 2 - 1;
							if (grid_peaks[y + i][x + j] < -10) grid_peaks[y + i][x + j] = -10;
							else if (grid_peaks[y + i][x + j] > 20) grid_peaks[y + i][x + j] = 20;
						}
					}
				}
			}
		}
	}
	
	// softening edges
	bool is_good = false;
	char y0 = 0;
	while (!is_good) {
		is_good = true;
		for (y = 0; y <= grid_size; y += gr) {
			for (x = 0; x <= grid_size; x += gr) {
				if (x != grid_size) {
					if (grid_peaks[y][x] - grid_peaks[y][x + 1] < -1 || grid_peaks[y][x] - grid_peaks[y][x + 1] > 1) {
						is_good = false;
						soft(x, y);
						break;
					} 
				}
				if (y != grid_size) {
					if (grid_peaks[y][x] - grid_peaks[y + 1][x] < -1 || grid_peaks[y][x] - grid_peaks[y + 1][x] > 1) {
						is_good = false;
						soft(x, y);
						break;
					} 
				}
			}
			if (!is_good) break;
		}
	}
}

void GameWin::gen_map_t_layer() {
	array<array<int, grid_size>, grid_size> T_height;
	array<array<string, grid_size>, grid_size> T_tilt;
	const unsigned char* text;
	int x, y, min_z, max_z = 0;
    sqlite3_open("map/data.db", &mapDB);
	
    string sql = "SELECT x, y, z, tilt FROM tiles;";
	
	sqlite3_stmt* stmt;

	sqlite3_prepare_v2(mapDB, sql.c_str(), -1, &stmt, nullptr);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		x = sqlite3_column_int(stmt, 0);
		y = sqlite3_column_int(stmt, 1);
		T_height[y][x] = sqlite3_column_int(stmt, 2);
		text = sqlite3_column_text(stmt, 3);
		T_tilt[y][x] = reinterpret_cast<const char*>(text);
	}
	sqlite3_finalize(stmt);
	
	sql = "SELECT z FROM tiles WHERE (x = 0 AND y = 0) OR (x = 99 AND y = 99);";

	sqlite3_prepare_v2(mapDB, sql.c_str(), -1, &stmt, nullptr);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		if (max_z == 0) max_z = sqlite3_column_int(stmt, 0);
		else min_z = sqlite3_column_int(stmt, 0);
	}
	sqlite3_finalize(stmt);
	
    sqlite3_close(mapDB);
	
	map_t_layer_image.resize({32 * grid_size, 16 * (grid_size + 1) + (max_z - min_z) * 8});
	
	y = 0;
	x = 0;
	for (int i = 0; i < 2 * grid_size - 1; i++) {
		if (i < grid_size) {
			x = i;
			y = 0;
		}
		else {
			x = grid_size - 1;
			y = i - grid_size + 1;
		}
		while (x + y == i && x >= 0 && y < grid_size){
			map_t_layer_image.copy(I_def[T_tilt[y][x]], Vector2u{id2px({unsigned int(x), unsigned int(y)}).x, id2px({unsigned int(x), unsigned int(y)}).y - (T_height[y][x] - max_z) * 8}, sf::IntRect({0, 0}, {32, 32}), true);
			y++;
			x--;
		}
	}
	terrain_map_tex.loadFromImage(map_t_layer_image);
	map_terrain_layer = std::make_unique<Sprite>(terrain_map_tex);
}

/*
	for (int i = 0; i < 2 * grid_size - 1; i++) {
		if (i < grid_size) {
			x = i;
			y = 0;
		}
		else {
			x = grid_size - 1;
			y = i - grid_size + 1;
		}
		while (x + y == i && x >= 0 && y < grid_size){
			map_t_layer_image.copy(I_def, Vector2u{id2px({unsigned int(x), unsigned int(y)}).x, id2px({unsigned int(x), unsigned int(y)}).y + T_height[y][x] * 8}, sf::IntRect({0, 0}, {32, 32}), true);
			y++;
			x--;
		}
	}
*/