#include "GameWin.h"
using namespace std;
using namespace sf;

Vector2u GameWin::id2px(Vector2u a) {
	array <int, 3> id = {a.x, a.y, 1};
	Vector2u px;
	for (char j = 0; j < 3; j++) {
		px.x += unsigned int(Mid2px[0][j] * id[j]);
		px.y += unsigned int(Mid2px[1][j] * id[j]);
	}
	return px;
}