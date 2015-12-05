#ifndef KS_VECTOR_H
#define KS_VECTOR_H

class ksVector
{
public:
	ksVector() { x = 0; y = 0; }
	ksVector(int pos_x, int pos_y) { x = pos_x; y = pos_y; }

	int x;
	int y;
};

#endif