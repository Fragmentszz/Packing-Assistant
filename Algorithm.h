#pragma once
#include<string>
#include<vector>
#include<set>
using namespace std;
const double len_cons[5] = { 63-1.2,63-1.2,63-1.2,63-1.2,60-1.2 };
const double weight_cons[5] = { 22,22,15,22.5,40 };
const double w_carton = 0.54*1e-4;
const double t_carton = 0.6;
struct Pos
{
	double x, y, z;
};
struct Shape
{
	double length, width, height;
	bool operator<(const Shape y)	const;
	double getVolum()const;
	double getArea() const;
};

class Space
{
public:
	Pos pos;
	Shape shape;
	Space(Pos _p, Shape _s);
	bool put(Shape) const;
	vector<Space> partition(Shape) const;
	bool operator<(const Space y)	const;
	bool operator == (const Space y) const;
};

class Goods
{
public:
	string identifier;
	Pos pos;
	Shape shape;
	Goods(string _i = "",double _w=0);
	Goods(string, Pos, Shape,double);
	double weight;
	void print() const;
	int index;
};
class Solve;
class Carton
{
public:
	Carton(int _id);
	bool put(Goods);
	friend class Solve;
private:
	int id;
	vector<Goods> goods;
	set<Space> spaces;
	//最小形状
	Shape shape;
	//货物总重量
	double weight;
	double volumn_goods;
};

class Carton2
{
public:
	vector<Goods> goods;
	Shape shape;
	double weight;
	double volum;
	double weight_goods;
	double volum_goods;
	double rate_w;
	double rate_v;
	
};

class Solution
{
public:
	int num;
	vector<Carton2> s_cartons;
	vector<Goods> unpackaged;
	double V_valid;
	void plot(string filename,int i=-1) const;
	double totr_V, totr_W;
};

class Solve
{
public:
	Solution solution;
	vector<Carton> cartons;
	vector<Goods> goods;
	int id;
	Solve(int _id, const vector<Goods>& goods);
	Solution getSolution() const;
	
};

