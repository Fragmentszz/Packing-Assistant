#include "Algorithm.h"

#include<iostream>
#include<fstream>

bool Shape::operator<(const Shape y) const
{
	return getVolum() < y.getVolum();
}

double Shape::getVolum() const
{
	return width * length * height;
}

double Shape::getArea() const
{
	return (width * length + length * height + width * height) * 2;
}




Goods::Goods(string _i,double _w)
	:Goods(_i, {0,0,0},{0,0,0},_w)
{
}

Goods::Goods(string _i, Pos _p, Shape _s,double _w)
	:identifier(_i),pos(_p),shape(_s),weight(_w),index(-1)
{

}

void Goods::print() const
{
	cout << identifier << " " << index << " " << " (" << pos.x << "," << pos.y << "," << pos.z  <<  ") (" << shape.length << "," << shape.width << "," << shape.height << ") " << weight << endl;
}

//Goods::operator Shape()
//{
//	return shape;
//}

Carton::Carton(int _id)
	:id(_id),shape({0.6,0.6,0.6}),weight(0),volumn_goods(0)
{
	spaces.insert(Space({ 0,0,0 }, { len_cons[id],len_cons[id],len_cons[id] }));
}

/**
 * @brief 将货物放入纸箱
 * 
 * @param newgoods 要放入的货物
 * @return true 放入成功
 * @return false 放入失败
 */
bool Carton::put(Goods newgoods)
{
    if (newgoods.weight + weight > weight_cons[id]) return false;
    //newgoods.print();

    bool flag = 0;
    Shape box;
    Shape newshape = {0, 0, 0};
    double ys[3] = {newgoods.shape.length, newgoods.shape.width, newgoods.shape.height};
    auto ptr = spaces.begin();

    double maxrate = 0;
    Shape ansshape = {0, 0, 0}, ansbox = {0, 0, 0};
    Space ansremoved({0, 0, 0}, {0, 0, 0});
    vector<Space> newspaces;
    Space removed({0, 0, 0}, {0, 0, 0});

    for (; ptr != spaces.end(); ptr++)
    {
        const Space &space = *ptr;
        int perm[3] = {0, 1, 2};
        for (int i = 0; i < 3 && !flag; i++)
        {
            double newlength = 0, newwidth = 0, newheight = 0;
            swap(perm[0], perm[i]);
            box.length = ys[perm[0]];
            for (int j = 1; j < 3 && !flag; j++)
            {
				
                swap(perm[1], perm[j]);
                box.width = ys[perm[1]], box.height = ys[perm[2]];
                if (space.put(box))
                {
                    // newgoods.print();
                    newshape.length = max(shape.length, box.length + space.pos.x);
                    newshape.width = max(shape.width, box.width + space.pos.y);
                    newshape.height = max(shape.height, box.height + space.pos.z);
					if (newshape.length > len_cons[id] || newshape.height > len_cons[id] || newshape.width > len_cons[id])
					{
						if (box.length > space.shape.length || box.width > space.shape.width || box.height > space.shape.height)
						{
							cout << "this above" << endl;
							cout << box.length << " " << box.width << " " << box.height << endl;
							cout << space.shape.length << " " << space.shape.width << " " << space.shape.height << endl;
						}
					}
                    else if (weight + newshape.getArea() * w_carton < weight_cons[id])
                    {
                        if (maxrate < box.getVolum() / newshape.getVolum())
                        {
                            maxrate = box.getVolum() / newshape.getVolum();
                            ansbox = box;
                            ansshape = newshape;
                            newspaces = space.partition(box);
                            newgoods.pos = space.pos;
                            //flag = 1;
                            removed = space;
                        }
                    }
                }
                swap(perm[1], perm[j]);
            }
            swap(perm[0], perm[i]);
        }
    }
    if (ansbox.getArea() > 1e-12)
    {
        weight += newgoods.weight;
		auto ptr = spaces.begin();
		for (;ptr!=spaces.end();++ptr)
		{
			if(*ptr == removed)	break;
		}
        spaces.erase(ptr);
        newgoods.shape = ansbox;
        shape = ansshape;
        volumn_goods += ansbox.getVolum();
        for (const Space &newspace : newspaces)
            spaces.insert(newspace);
        goods.push_back(newgoods);
        return true;
    }
    return false;
}


Space::Space(Pos _p, Shape _s)
	:pos(_p),shape(_s)
{

}

bool Space::put(Shape box)	const
{
	if (box.height <= shape.height && box.length <= shape.length && box.width <= shape.width)	return true;
	return false;
}


vector<Space> Space::partition(Shape box) const
{
	if (box.height > shape.height || box.length > shape.length || box.width > shape.width) {
		// 如果 box 大于 shape 的任何维度，则抛出异常或返回空集合
		throw std::invalid_argument("Box dimensions must be smaller than Shape dimensions for partitioning.");
	}
	double z = pos.z + box.height, x = pos.x + box.length, y = pos.y + box.width;
	vector<Space> ans;
	if (fabs(box.height - shape.height) > 1e-6)
		ans.push_back(Space({ pos.x,pos.y,z }, { box.length,box.width,shape.height - box.height }));
	if (fabs(box.length - shape.length) > 1e-6)
		ans.push_back(Space({ x,pos.y,pos.z }, { shape.length - box.length,box.width,shape.height }));
	if (fabs(box.width - shape.width) > 1e-6)
		ans.push_back(Space({ pos.x,y,pos.z }, { shape.length,shape.width - box.width,shape.height }));
	return ans;
}

bool Space::operator<(const Space y) const
{
	return shape < y.shape;
}

bool Space::operator==(const Space y) const
{
	if(fabs(pos.x-y.pos.x)<1e-6 && fabs(pos.y - y.pos.y) < 1e-6 && fabs(pos.z - y.pos.z) < 1e-6 && fabs(shape.length - y.shape.length)<1e-6 && fabs(shape.width - y.shape.width)<1e-6 && fabs(shape.height - y.shape.height)<1e-6)	return true;
	return false;
}
#include<algorithm>
static bool cmp(const Goods& x,const Goods& y)
{
	return x.shape.getVolum() > y.shape.getVolum();
}

Solve::Solve(int _id, const vector<Goods>& _goods)
	:id(_id),goods(_goods)
{
	sort(goods.begin(), goods.end(),cmp);

	for (int i = 0; i < goods.size(); i++)
	{
		bool flag = 0;
		for (int j = 0; j < cartons.size(); j++)
		{
			if (cartons[j].put(goods[i]))
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			Carton free(id);
			if (free.put(goods[i]))
			{
				//cout << cartons.size() << endl;
				cartons.push_back(free);
			}
			else
			{
				solution.unpackaged.push_back(goods[i]);
			}
		}
	}
	double totV=0,totV_v=0,totW=0,totW_v=0;
	for (int i = 0; i < cartons.size(); i++)
	{
		Carton2 carton;
		cartons[i].shape.height += 1.2, cartons[i].shape.width += 1.2, cartons[i].shape.length += 1.2;
		carton.shape = cartons[i].shape;
		carton.weight = cartons[i].weight + cartons[i].shape.getArea() * w_carton;
		carton.weight_goods = cartons[i].weight;
		carton.volum = carton.shape.getVolum();
		// cout << carton.volum << " " << carton.shape.getVolum() << endl;
		carton.volum_goods = cartons[i].volumn_goods;
		carton.rate_w = carton.weight_goods / carton.weight;
		carton.rate_v = carton.volum_goods / carton.volum;
		for (int j = 0; j < cartons[i].goods.size(); j++)
		{
			Goods nowgoods = cartons[i].goods[j];
			nowgoods.pos.x += 0.6, nowgoods.pos.y += 0.6, nowgoods.pos.z += 0.6;
			nowgoods.index = i;
			carton.goods.push_back(nowgoods);
		}
		solution.s_cartons.push_back(carton);
		totV += carton.volum;
		totV_v += carton.volum_goods;
		totW += carton.weight;
		totW_v += carton.weight_goods;
	}
	solution.num = cartons.size();
	solution.totr_V = totV_v / totV;
	solution.totr_W = totW_v / totW;
}

Solution Solve::getSolution() const
{
	return solution;
}

void Solution::plot(string filename,int i) const
{
	ofstream fout;
	fout.open("./docs/" + filename,ios::out);
	if (i == -1)
	{
		fout << num << endl;
		for (int i = 0; i < num; i++)
		{
			fout << s_cartons[i].shape.length << " " << s_cartons[i].shape.width << " " << s_cartons[i].shape.height << endl;
			fout << s_cartons[i].weight << endl;
			fout << s_cartons[i].goods.size() << endl;
			for (const Goods& goods : s_cartons[i].goods)
			{
				fout << goods.identifier << " " << goods.pos.x << " " << goods.pos.y << " " << goods.pos.z << " " << goods.shape.length << " " << goods.shape.width << " " << goods.shape.height << endl;
			}
		}
		fout.close();
	}
	else if (i >= 0)
	{
		fout << 1 << endl;
		fout << s_cartons[i].shape.length << " " << s_cartons[i].shape.width << " " << s_cartons[i].shape.height << endl;
		fout << s_cartons[i].weight << endl;
		fout << s_cartons[i].goods.size() << endl;
		for (const Goods& goods : s_cartons[i].goods)
		{
			fout << goods.identifier << " " << goods.pos.x << " " << goods.pos.y << " " << goods.pos.z << " " << goods.shape.length << " " << goods.shape.width << " " << goods.shape.height << endl;
		}
		fout.close();
		system(("python plot.py " + filename).c_str());
	}
	
}
