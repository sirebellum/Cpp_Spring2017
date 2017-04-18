#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

class item {
public:
	int data = -1;
}; //End item

class Unit {
public:

	item* Data[9] = { new item, new item, new item, new item, new item, new item, new item, new item, new item };
	
	void link(int i, item *data)
	{
		delete Data[i];
		Data[i] = data;
	}
	
}; //End Unit

class Layer
{
	
public:
	
	Unit* rows    = new Unit[9];
	Unit* columns = new Unit[9];
	Unit* blocks  = new Unit[9];
	int identifier;

	//Constructor
	Layer(int id) {identifier = id; }
	
	//Populates layer according to input layer
	void populate(const Layer* base)
	{
		for (int r = 0; r <= 8; r++) {
			for (int i = 0; i <= 8; i++)
			{
				if (base->rows[r].Data[i]->data == this->identifier)
					this->rows[r].Data[i]->data = 1;

				this->columns[i].link(r, this->rows[r].Data[i]);
				
				if (r <= 2)
				{
					if (i <= 2)
						this->blocks[0].link(i+3*r, this->rows[r].Data[i]);
					else if (i >= 3 && i <= 5)
						this->blocks[1].link(i-3+3*r, this->rows[r].Data[i]);
					else
						this->blocks[2].link(i-6+3*r, this->rows[r].Data[i]);
				}
				else if (r >= 3 && r <= 5)
				{
					if (i <= 2)
						this->blocks[3].link(i+3*(r-3), this->rows[r].Data[i]);
					else if (i >= 3 && i <= 5)
						this->blocks[4].link(i-3+3*(r-3), this->rows[r].Data[i]);
					else
						this->blocks[5].link(i-6+3*(r-3), this->rows[r].Data[i]);
				}
				else
				{
					if (i <= 2)
						this->blocks[6].link(i+3*(r-6), this->rows[r].Data[i]);
					else if (i >= 3 && i <= 5)
						this->blocks[7].link(i-3+3*(r-6), this->rows[r].Data[i]);
					else
						this->blocks[8].link(i-6+3*(r-6), this->rows[r].Data[i]);
				}
			}
		}
	}
	//0 out unfillable items
	void clean()
	{
		bool row = false;
		bool column = false;
		bool block = false;
		
		for (int r = 0; r <= 8; r++) {
			for (int i = 0; i <= 8; i++)
			{
				if (this->rows[r].Data[i]->data == 1)
					row = true;
				if (this->columns[r].Data[i]->data == 1)
					column = true;
				if (this->blocks[r].Data[i]->data == 1)
					block = true;
			}
			
			if (row) //If there was eight -1s and one 1
				for (int i = 0; i <= 8; i++)
					if (this->rows[r].Data[i]->data == -1)
						this->rows[r].Data[i]->data = 0;
			if (column) //If there was eight -1s and one 1
				for (int i = 0; i <= 8; i++)
					if (this->columns[r].Data[i]->data == -1)
						this->columns[r].Data[i]->data = 0;
			if (block) //If there was eight -1s and one 1
				for (int i = 0; i <= 8; i++)
					if (this->blocks[r].Data[i]->data == -1)
						this->blocks[r].Data[i]->data = 0;
			
			row = false;
			column = false;
			block = false;	
		}
	}
	//Print layer with formatting
	void print()
	{
		for (int i = 0; i<=8; i++) {
			for (int j = 0; j<=8; j++)
			{
				if (this->rows[i].Data[j]->data < 0)
					cout << "\b" << this->rows[i].Data[j]->data;
				else
					cout << this->rows[i].Data[j]->data;
				
				if (j == 2 || j == 5)
					cout << " | ";
				else cout << " ";
				
			}
			cout << endl;
			if (i == 2 || i == 5)
				cout << "---------------------" << endl;
		}
	}
	
}; //End Layer

class Board
{
	
public:
	
	Layer *l1 = new Layer(1);
	Layer *l2 = new Layer(2);
	Layer *l3 = new Layer(3);
	Layer *l4 = new Layer(4);
	Layer *l5 = new Layer(5);
	Layer *l6 = new Layer(6);
	Layer *l7 = new Layer(7);
	Layer *l8 = new Layer(8);
	Layer *l9 = new Layer(9);
	
	Layer *base = new Layer(0);
	
	//Constructor
	Board(string filename)
	{
		ifstream infile(filename);
		string line;
		int i = 0;

		while (getline(infile, line)) {
			
			istringstream iss(line);
			for (int j = 0; j<=8; j++)
				if (!(iss >> this->base->rows[i].Data[j]->data)) { break; } // error
			i++;
		}
		
		
	}

	//Extrapolate base layer into layers 1-9
	void extrapolate()
	{
		l1->populate(base);
		l2->populate(base);
		l3->populate(base);
		l4->populate(base);
		l5->populate(base);
		l6->populate(base);
		l7->populate(base);
		l8->populate(base);
		l9->populate(base);
		l1->clean();
		l2->clean();
		l3->clean();
		l4->clean();
		l5->clean();
		l6->clean();
		l7->clean();
		l8->clean();
		l9->clean();
	}
};


int main()
{
	
	Board main("sudoku1.txt");
	
	main.extrapolate();

	main.l1->print();
}