// ChessLikeGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <map>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <time.h> 

using namespace std;

// Point class with x and y coords
struct TPoint {
	int x;
	int y;

	explicit TPoint(int x,  int y) : x(x), y(y)
	{};

	TPoint() : x(0), y(0)
	{};

	TPoint operator+(TPoint another) {
		return TPoint(x + another.x, y + another.y);
	}

	TPoint operator-(TPoint another) {
		return TPoint(x - another.x, y - another.y);
	}

	TPoint operator*(int scalar) {
		return TPoint(x * scalar, y * scalar);
	}

	bool operator==(TPoint another) {
		return x == another.x && y == another.y;
	}

	void operator=(TPoint another) {
		x = another.x;
		y = another.y;
	}
};

bool operator<(const TPoint& a, const TPoint& b) {
	if (a.x <= b.x)
		return a.x < b.x ? true : a.y < b.y;
	else
		return false;
}

// Formulae to calculate damage after armor reduction. Returns resulting damage
int DamageAfterReduction( int damage,  int armor) {
	return damage - armor / damage; 
}

// Colors
enum TColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

const int COLOR_MODE = TColor::White;
const int WIDTH = 25;
const int HEIGHT = 16;
const int ARMY = 10;
const int ACTIONS = 3;
const bool AREAS = true;

HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

// Set output text and background color
void SetColor(TColor text, TColor background)
{
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
}

// Set output text and background color
void SetColor(int text, int background = 15) {
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
}

enum TTeam { NEUTRAL = COLOR_MODE, TEAM_1 = TColor::Blue, TEAM_2 = TColor::Red };

// Basic class for structures
class Structure {
protected:
	TPoint pos;
	bool breakable;
	bool walkable;
	char chr;
	int team;

	int health;
	int armor;

public:
	virtual bool TakeDamage( int& damage) { 
		if (breakable) {
			health -= DamageAfterReduction(damage, armor);
		}
		return breakable;
	};

friend class Warrior;
friend class Ranger;
friend class Mage;
friend class Manager;
friend class Log;
};

// Structure Wall
class Wall : public Structure {
public:
	explicit Wall(int x,  int y) {
		pos = TPoint(x, y);
		breakable = false;
		walkable = false;
		chr = char(178);
		team = TTeam::NEUTRAL;

		health = 1; // For Killed() function. Delete it if I'll create friendly manager
	}
};

// Structure Fortress
class Fortress : public Structure {
public:
	explicit Fortress(int x, int y, int _team) {
		pos = TPoint(x, y);
		breakable = false;
		walkable = false;
		chr = char(178);
		team = _team;

		health = 30;
		armor = 10;
	}
};

// Structure Grass
class Grass : public Structure {
public:
	Grass() {
		breakable = false;
		walkable = true;
		chr = ' ';
		team = TTeam::NEUTRAL;
		
		health = 1;
	}
};

// Unit types
enum TUnitType { WARRIOR, RANGER, MAGE };
const string UNIT_NAMES[3] = { "Warrior", "Ranger", "Mage" };
const string UNIT_DESCR[3] = { "+1 dmg to first attack", "Long range shots", "AOE damage in square 3x3" };

// Basic class for units
class Unit {
protected:
	TPoint pos;
	TUnitType unit_t;
	int attack_range;
	int damage;
	int health;
	int team;
	int armor;
	char chr;
	bool friendly_fire;
	bool target_attack;

public:
	void Move(TPoint new_pos) { // Manager will check, if move is possible
		pos = new_pos;
	}

	// First val - damage; second - array of Positions, where damage will come; third - length of array
	virtual tuple<int, vector<TPoint>> Attack(TPoint target) {
		vector<TPoint> v{ target };
		return make_tuple(damage, v);
	}

	void TakeDamage(int dmg) {
		health -= DamageAfterReduction(dmg, armor);
	}

friend class Warrior;
friend class Ranger;
friend class Mage;
friend class Manager;
friend class Log;
};

// Warrior unit
class Warrior : public Unit {
private:
	int first_attack_bonus;
public:
	explicit Warrior(int x, int y, int _team) {
		damage = 7;
		health = 10;
		armor = 10;
		attack_range = 1;
		friendly_fire = false;
		target_attack = true;
		first_attack_bonus = 1;

		pos = TPoint(x, y);
		chr = 'W';
		team = _team;
		unit_t = WARRIOR;
	}

	virtual tuple<int, vector<TPoint>> Attack(TPoint target) {
		vector<TPoint> v{ target };
		return make_tuple(first_attack_bonus ? damage + first_attack_bonus-- : damage, v);
	}
};

// Ranger unit
class Ranger : public Unit {
public:
	explicit Ranger(int x, int y, int _team) {
		damage = 5;
		health = 8;
		armor = 6;
		attack_range = 6;
		friendly_fire = false;
		target_attack = true;

		pos = TPoint(x, y);
		chr = 'R';
		team = _team;
		unit_t = RANGER;
	}
};

// Mage unit
class Mage : public Unit {
public:
	explicit Mage(int x, int y, int _team) {
		damage = 4;
		health = 6;
		armor = 2;
		attack_range = 4;
		friendly_fire = true;
		target_attack = false;

		pos = TPoint(x, y);
		chr = 'M';
		team = _team;
		unit_t = MAGE;
	}

	tuple<int, vector<TPoint>> Attack(TPoint target) override {
		vector<TPoint> points;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				points.push_back(TPoint(i - 1, j - 1) + target);
			}
		}
		return make_tuple(damage, points);
	}
};

//    Manager stuff    //

#include <iostream>

// Function, that checks if key (point) in container. Could use just map::count, but I'm dumb and it was too late
template<class T>
bool in_container(const T& container, TPoint p) {
	return container.find(p) != container.end();
}

template<class T>
void Print(T c, bool inverse, int text = TTeam::NEUTRAL, int background = TTeam::NEUTRAL == TColor::Black ? TColor::White : TColor::Black) {
	if (inverse) {
		if (text == TColor::Black || text == TColor::White)
			text = text == TColor::Black ? TColor::White : TColor::Black;

		background = background == TColor::Black ? TColor::White : TColor::Black;
	}
	SetColor(text, background);
	cout << c;
	SetColor(TTeam::NEUTRAL, TTeam::NEUTRAL == TColor::Black ? TColor::White : TColor::Black);
}

const string SPACE = "  ";

//   Finally manager class   //

// Controls units and structures
class Manager {
private:
	TPoint size;
	map<TPoint, Unit*> units;
	map<TPoint, Structure*> structures;

	Structure* grass = new Grass();
	Unit* choosen = nullptr;
	TPoint current = TPoint();
	TPoint last = TPoint();
	TPoint before_attack = TPoint();

	int current_player = TTeam::TEAM_1;
	int actions = 1;

public:
	explicit Manager(int w, int h) { 
		size = TPoint(w, h); 
		CreateBorders(); 
		CreateArmy(0, TTeam::TEAM_1);
		CreateArmy(w / 2 + w % 2, TTeam::TEAM_2);
	}

	// Main display function
	void Show(int state) {
		SetColor(TTeam::NEUTRAL, TTeam::NEUTRAL == TColor::Black ? TColor::White : TColor::Black);
		system("CLS");
		cout << endl;
		cout << SPACE << "(" << current.x << ", " << current.y << ")";
		cout << "    Player: "; 
		Print(current_player == TTeam::TEAM_1 ? 1 : 2, false, current_player);
		cout << "  Actions: " << ACTIONS - actions + 1 << endl;
		for (int y = -1; y <= size.y; y++) {
			cout << SPACE;
			for (int x = -1; x <= size.x; x++) {
				TPoint pos(x, y);
				TColor background = AREAS && state && (Distance(pos, choosen->pos) <= choosen->attack_range) ? DarkGray : TTeam::NEUTRAL == TColor::Black ? TColor::White : TColor::Black;
				if (AREAS && state && Distance(pos, choosen->pos) <= 1)
					background = TColor::LightGray;
				if (in_container(units, pos)) {
					
					Print(units[pos]->chr, pos == current, units[pos]->team, background);
				}
				else if (in_container(structures, pos)) {
					Print(structures[pos]->chr, pos == current, structures[pos]->team, background);
				}
				else {
					Print(grass->chr, pos == current, TTeam::NEUTRAL, background);
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	// Adds object to container
	
	bool Add(Unit* unit) {
		bool cond = !InContainers(unit->pos);
		if (cond)
			units.insert({ unit->pos, unit });
		return cond;
	}

	void Remove(TPoint pos) {
		if (InContainers(pos)) {
			if (in_container(units, pos))
				units.erase(pos);
			else
				structures.erase(pos);
		}
	}

	bool Add(Structure* structure) {
		bool cond = !InContainers(structure->pos);
		if (cond)
			structures.insert({ structure->pos, structure });
		return cond;
	}

	// Choose unit from current position
	bool ChooseUnit(TPoint pos) {
		bool cond = in_container(units, pos) && units[pos]->team == current_player;
		if (cond) {
			before_attack = current;
			choosen = units[pos];
		}
		return cond;
	}

	// Move choosen unit to new position
	bool Move(TPoint target) {
		bool cond = Distance(target, choosen->pos) == 1 && !InContainers(target);
		if (cond) {
			Remove(choosen->pos);
			choosen->Move(target);
			Add(choosen);
		}
		return cond;
	}

	bool Attack(TPoint pos) {
		bool cond_attack_range = Distance(choosen->pos, pos) <= choosen->attack_range;
		bool success = false; // if somebody got hurt. This doesnt allow misses
		if (cond_attack_range) {
			tuple<int, vector<TPoint>> info = choosen->Attack(pos);
			int attack_damage = get<0>(info);
			vector<TPoint> targets = get<1>(info);
			for (int i = 0; i < targets.size(); i++) {
				TPoint attack_pos = targets[i];
				// If there is unit (or structure) and it can be attacked (enemy or attacker can attack allies)
				if (in_container(units, attack_pos) && (units[attack_pos]->team != choosen->team || choosen->friendly_fire)) {
					Unit* unit = units[attack_pos];
					unit->TakeDamage(attack_damage);
					if (unit->health <= 0)
						Remove(attack_pos);
					success = true;
				}
				// Same for structures, but also I check if it's breakable
				else if (in_container(structures, attack_pos) && structures[attack_pos]->breakable)
					if (structures[attack_pos]->team != choosen->team || choosen->friendly_fire) {
						Structure* structure = structures[attack_pos];
						structure->TakeDamage(attack_damage);
						if (structure->health <= 0)
							Remove(attack_pos);
						success = true;
					}
			}
		}
		if (success)
			current = before_attack;
		return success;
	}

	// Additional functions

	// Distance between two points. It's max dist between one of coordinates (x or y)
	int Distance(TPoint p1, TPoint p2) {
		/*
		int dx = abs(p1.x - p2.x);
		int dy = abs(p1.y - p2.y);
		return max(dx, dy);
		*/
		int dx = p1.x - p2.x;
		int dy = p1.y - p2.y;
		return int(sqrt(dx*dx + dy*dy));
	}

	bool InContainers(TPoint pos) {
		return in_container(units, pos) || in_container(structures, pos);
	}

	void ChangePlayer() {
		actions++;
		if (actions > ACTIONS) {
			current_player = current_player == TTeam::TEAM_1 ? TTeam::TEAM_2 : TTeam::TEAM_1;
			TPoint temp = current;
			current = last;
			last = temp;
			actions = 1;
		}
	}

	void CreateBorders() {
		for (int i = -1; i <= size.x; i++) {
			Add(new Wall(i, -1));
			Add(new Wall(i, size.y));
		}

		for (int i = -1; i <= size.y; i++) {
			Add(new Wall(-1, i));
			Add(new Wall(size.x, i));
		}

		for (int i = -2; i <= 1; i++) {
			Add(new Wall(size.x / 2 - 2, size.y / 2 + i));
			Add(new Wall(size.x / 2 + 1, size.y / 2 + i));
		}
	}

	void CreateArmy(int shift, TTeam team) {
		int i = ARMY;
		while (i > 0) {
			TPoint p(rand() % (size.x / 2) + shift, rand() % size.y);
			if (!InContainers(p)) {
				Unit* temp[3] = { new Warrior(p.x, p.y, team), new Ranger(p.x, p.y, team), new Mage(p.x, p.y, team) };
				Add(temp[i % 3]);
				i--;
			}
		}
	}

	// Debug functions

	void ShowContainers() {
		for (auto it : units) {
			Unit* unit = it.second;
			cout << unit->chr << ": " << unit->pos.x << " " << unit->pos.y << endl;
		}
		cout << endl;
		for (auto it : structures) {
			Structure* str = it.second;
			cout << str->chr << ": " << str->pos.x << " " << str->pos.y << endl;
		}
	}
	
friend class InputHandler;
friend class Log;
};

class Log {
private:
	Manager& manager;
public:
	explicit Log(Manager& _manager) : manager(_manager) {}

	void ShowUnitInfo(int state) {
		if (manager.InContainers(manager.current)) {
			if (in_container(manager.units, manager.current)) {
				Unit* unit = manager.units[manager.current];
				cout << SPACE << "Unit: ";
				Print(UNIT_NAMES[unit->unit_t], false, unit->team);
				cout << endl;
				cout << SPACE << "Damage: " << unit->damage << endl;
				cout << SPACE << "Health: " << unit->health << endl;
				cout << SPACE << "Armor: " << unit->armor << endl;
				cout << SPACE << "Attack range: " << unit->attack_range << endl;
				cout << SPACE << "Description: " << UNIT_DESCR[unit->unit_t] << endl;
			}
		}
		if (state > 0) {
			cout << SPACE << "Distance between: " << manager.Distance(manager.current, manager.choosen->pos) << endl;
			cout << SPACE;
			if (manager.Distance(manager.current, manager.choosen->pos) <= 1)
				Print("Can move", false, TColor::Green);
			else
				Print("Too far to move", false, TColor::Red);
			cout << endl;
			cout << SPACE;
			if (manager.Distance(manager.current, manager.choosen->pos) <= manager.choosen->attack_range)
				Print("Can attack", false, TColor::Green);
			else
				Print("Too far to attack", false, TColor::Red);
			cout << endl;

		}
	}
};

class InputHandler {
private:
	Manager manager = Manager(30, 16);
	Log log = Log(manager);

	// 0 - choosing unit, 1 - choosing target
	int state = 0;

public:
	void PressedMoveKey(char key) {
		if (key == 'w')
			manager.current = manager.current + TPoint( 0, -1);
		if (key == 's')
			manager.current = manager.current + TPoint( 0,  1);
		if (key == 'a')
			manager.current = manager.current + TPoint(-1,  0);
		if (key == 'd')
			manager.current = manager.current + TPoint( 1,  0);

		if (manager.current.x < 0)
			manager.current.x = 0;

		if (manager.current.x >= manager.size.x)
			manager.current.x = manager.size.x - 1;

		if (manager.current.y < 0)
			manager.current.y = 0;

		if (manager.current.y >= manager.size.y)
			manager.current.y = manager.size.y - 1;

		manager.Show(state);
		log.ShowUnitInfo(state);
	}

	void ChooseUnit() {
		if (manager.ChooseUnit(manager.current))
			state++;
	}

	void PressedActionKey() {
		if (state == 0) {
			ChooseUnit();
		}
		else {
			if (manager.Attack(manager.current)) {
				state = 0;
				manager.ChangePlayer();
			}
		}
		manager.Show(state);
		log.ShowUnitInfo(state);
	}

	void PressedMoveUnitKey() {
		if (state == 0) {
			ChooseUnit();
		}
		else {
			if (manager.Move(manager.current)) {
				state = 0;
				manager.ChangePlayer();
			}
		}
		manager.Show(state);
		log.ShowUnitInfo(state);

	}

	void PressedCancelKey() {
		state = 0;
		manager.Show(state);
		log.ShowUnitInfo(state);
	}

	void StartFlow() {
		manager.Show(state);
		char key;
		do {
			key = _getch();
			if (key == 'w' || key == 'a' || key == 's' || key == 'd')
				PressedMoveKey(key);
			if (key == 'h')
				PressedActionKey();
			if (key == 'j')
				PressedMoveUnitKey();
			if (key == 'k')
				PressedCancelKey();
		} while (key != '=');
	}

	void ShowContainers() {
		manager.ShowContainers();
	}
};

int main(){
	srand(time(NULL));
	InputHandler handler;
	handler.StartFlow();
	system("pause");
    return 0;
}
