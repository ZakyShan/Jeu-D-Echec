

class Position {
public:
	Position() = default;
	Position(int x, int y);

	int get_X();
	int get_Y();
	void set_X(int x);
	void set_Y(int y);
	
private:
	int x;
	int y;

};