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
		Data[i] = data; //Delete old reference and point to new item
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
				//Rows
					this->rows[r].Data[i]->data = 1;
				else if (base->rows[r].Data[i]->data != 0)
					this->rows[r].Data[i]->data = 0;
				
				//Columns
				this->columns[i].link(r, this->rows[r].Data[i]);
				
				//Blocks
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
				//Comes back true if atleast one item in Unit is already a 1
			}
			
			if (row)
				for (int i = 0; i <= 8; i++)
					if (this->rows[r].Data[i]->data == -1)
						this->rows[r].Data[i]->data = 0;
			if (column)
				for (int i = 0; i <= 8; i++)
					if (this->columns[r].Data[i]->data == -1)
						this->columns[r].Data[i]->data = 0;
			if (block)
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
	//Fill in 1s where definite
	int fill()
	{
		int row = 0;
		int column = 0;
		int block = 0;
		
		int filled = 0;
		//Sum up totals in each Unit
		for (int r = 0; r <= 8; r++)
		{
			for (int i = 0; i <= 8; i++)
				row+=    this->rows[r].Data[i]->data;
			if (row == -1) {
				filled = 1;
				for (int i = 0; i <= 8; i++)
					if (this->rows[r].Data[i]->data == -1)
						this->rows[r].Data[i]->data = 1; }
			row = 0;
		}
		this->clean();
			
		for (int r = 0; r <= 8; r++)
		{
			for (int i = 0; i <= 8; i++)
				column+= this->columns[r].Data[i]->data;
			if (column == -1) {
				filled = 1;
				for (int i = 0; i <= 8; i++)
					if (this->columns[r].Data[i]->data == -1)
						this->columns[r].Data[i]->data = 1; }
			column = 0;
		}
		this->clean();
				
		for (int r = 0; r <= 8; r++)
		{
			for (int i = 0; i <= 8; i++)
				block+=  this->blocks[r].Data[i]->data;
			if (block == -1) {
				filled = 1;
				for (int i = 0; i <= 8; i++)
					if (this->blocks[r].Data[i]->data == -1)
						this->blocks[r].Data[i]->data = 1; }
			block = 0;
		}
		this->clean();
		
		return filled;
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
	//Prints all boards with formating
	void print_all()
	{
		cout << "LAYER 1" << endl;
		l1->print();
		cout << endl << "LAYER 2" << endl;
		l2->print();
		cout << endl << "LAYER 3" << endl;
		l3->print();
		cout << endl << "LAYER 4" << endl;
		l4->print();
		cout << endl << "LAYER 5" << endl;
		l5->print();
		cout << endl << "LAYER 6" << endl;
		l6->print();
		cout << endl << "LAYER 7" << endl;
		l7->print();
		cout << endl << "LAYER 8" << endl;
		l8->print();
		cout << endl << "LAYER 9" << endl;
		l9->print();
		cout << endl;
	}
	//Fill all layers till nothing can be filled
	void fill_all()
	{
		int filled = 1;
		while (filled)
		{
			filled = 0;
			filled+= this->l1->fill();
			filled+= this->l2->fill();
			filled+= this->l3->fill();
			filled+= this->l4->fill();
			filled+= this->l5->fill();
			filled+= this->l6->fill();
			filled+= this->l7->fill();
			filled+= this->l8->fill();
			filled+= this->l9->fill();
			cout << filled << endl;
		}
	}
};


int main()
{
	
	Board main("sudoku1.txt");
	
	main.extrapolate();
	
	main.fill_all();
	
	main.print_all();
}