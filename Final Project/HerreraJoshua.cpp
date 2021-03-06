#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

class item { //Refers to individual cells in a 9x9 sudoku board
public:
	int data = -1;
}; //End item

class Unit { //General class encompasing rows, columns, and blocks
public:

	item* Data[9] = { new item, new item, new item, new item, new item, new item, new item, new item, new item };
	
	//Function used to point Unit Data item pointer to other items
	void link(int i, item *data)
	{
		if (Data[i] != NULL) delete Data[i]; 
		Data[i] = data; //Delete old reference and point to new item
	}
	
}; //End Unit

class Layer //Class that contains Units of items, where Units are organized into rows, columns, and blocks. Includes an identifier that describes what data the Layer holds. 0 is base, 1 is 1s, 2 is 2s, etc.
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


			//Next code block links column Units' items and block Units' items to corresponding items in row Units
				//Columns. Easy to link, just switch indices
				this->columns[i].link(r, this->rows[r].Data[i]);
				
				//Blocks. Harder to link. If else logic to determine which block to fill based on current row indices
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
	//Fill base board with determined 1s in other layers
	void populate_base(const Layer* l)
	{
		for (int r = 0; r <= 8; r++) {
			for (int i = 0; i <= 8; i++)
			{
				if (l->rows[r].Data[i]->data == 1)
				//Rows
					this->rows[r].Data[i]->data = l->identifier;
			}
		}
	}
	
	//Functions that clean rows and columns for block_reserve function based on block composition
	void block_cclean(int block, int column)
	{
		for (int i = 0; i <= 8; i++)
		{
			if (block <= 2) {
				if (i > 2)
				this->columns[column].Data[i]->data = 0; }
			else if (block >= 3 && block <= 5) {
				if (i < 3 || i > 5)
					this->columns[column].Data[i]->data = 0; }
			else {
				if (i < 6)
					this->columns[column].Data[i]->data = 0; }
		}
	}
	void block_rclean(int block, int row)
	{
		
		if (block <= 2)
			if (row == 2)
				row = 0;
			else if (row == 5)
				row = 1;
			else
				row = 2;
		else if (block >= 3 && block <= 5)
			if (row == 2)
				row = 3;
			else if (row == 5)
				row = 4;
			else
				row = 5;
		else 
			if (row == 2)
				row = 6;
			else if (row == 5)
				row = 7;
			else
				row = 8;
		
		for (int i = 0; i <= 8; i++)
		{
			if (block == 0 || block == 3 || block == 6)
				if (i > 2)
				{
					this->rows[row].Data[i]->data = 0;
				}
			else if (block == 1 || block == 4 || block == 7)
				if (i < 3 && i > 5)
				{
					this->rows[row].Data[i]->data = 0;
				}
			else
				if (i < 6)
				{
					this->rows[row].Data[i]->data = 0;
				}
		}
	}
	
	//Finds blocks whose empty items are aligned in a row or a column and 0s out the row/column outside of the block
	void block_reserve()
	{
		int bsum = 0;
		int brsum = 0;
		int bc1sum = 0;
		int bc2sum = 0;
		int bc3sum = 0;
		for (int b = 0; b <= 8; b++) {
			for (int i = 0; i <= 8; i++)
				//block sum to see how many -1s in a block
				bsum+= this->blocks[b].Data[i]->data;
			
			//Should be no more than 3 -1s
			if (bsum >= -3 && bsum != 1)
			{
				for (int i = 0; i <= 8; i++)
				{
					//Rows. If all -1s are in the same row, should clean the rest of the row
					brsum+= this->blocks[b].Data[i]->data;
					if (i==2 || i==5 || i==8)
					{
						if (brsum == bsum)
							block_rclean(b, i);
						brsum = 0;
					}
					
					//Columns. If all -1s are in the same column, should clean the rest of the column
					if (i==0 || i==3 || i==6)
					{
						bc1sum+= this->blocks[b].Data[i]->data;
						if (bc1sum == bsum)
						{
							if (b <= 2)
								block_cclean(b, (3*b));
							else if (b >= 3 && b <= 5)
								block_cclean(b, (3*(b-3)));
							else 
								block_cclean(b, (3*(b-6)));
							bc1sum = 0;
						}
					}
					else if (i==1 || i==4 || i==7)
					{
						bc2sum+= this->blocks[b].Data[i]->data;
						if (bc2sum == bsum)
						{
							if (b <= 2)
								block_cclean(b, 1+(3*b));
							else if (b >= 3 && b <= 5)
								block_cclean(b, 1+(3*(b-3)));
							else 
								block_cclean(b, 1+(3*(b-6)));
							bc2sum = 0;
						}
					}
					else if (i==2 || i==5 || i==8)
					{
						bc3sum+= this->blocks[b].Data[i]->data;
						if (bc3sum == bsum)
						{
							if (b <= 2)
								block_cclean(b, 2+(3*b));
							else if (b >= 3 && b <= 5)
								block_cclean(b, 2+(3*(b-3)));
							else 
								block_cclean(b, 2+(3*(b-6)));
							bc3sum = 0;
						}
					}
				}
			}
		
		brsum = 0;
		bc1sum = 0;
		bc2sum = 0;
		bc3sum = 0;
		bsum = 0;
		}
	}
	
	//0 out unfillable items
	void clean(const Layer* base)
	{
		bool row = false;
		bool column = false;
		bool block = false;
		
		for (int r = 0; r <= 8; r++) {
			for (int i = 0; i <= 8; i++)
			{
			//Variable for each Unit comes back true if one item in Unit is already a 1
				if (this->rows[r].Data[i]->data == 1)
					row = true;
				if (this->columns[r].Data[i]->data == 1)
					column = true;
				if (this->blocks[r].Data[i]->data == 1)
					block = true;
				
				//0 out items that already have a value in base layer
				if (base->rows[r].Data[i]->data != 0 && base->rows[r].Data[i]->data != this->identifier)
					this->rows[r].Data[i]->data = 0;
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
				if (j == 0)
					//Fixes misalignment when first item in row is negative
					cout << " "; 
				if (this->rows[i].Data[j]->data < 0) 
					//Fixes misalignment when any item is negative
					cout << "\b" << this->rows[i].Data[j]->data;
				else
					cout << this->rows[i].Data[j]->data;
				
				if (j == 2 || j == 5)
					cout << " | ";
				else cout << " ";
				
			}
			cout << endl;
			if (i == 2 || i == 5)
				cout << "-----------------------" << endl;
		}
	}
	//Write layer to text file with formating
	void write()
	{
		ofstream myfile;
		string filename = to_string(identifier);
		filename+= ".txt";
		myfile.open (filename);
		
		for (int i = 0; i<=8; i++) {
			for (int j = 0; j<=8; j++)
			{
				if (this->rows[i].Data[j]->data < 0) 
					//Fixes misalignment when any item is negative
					myfile << " ";
				else
					myfile << this->rows[i].Data[j]->data;
				
				if (j == 2 || j == 5)
					myfile << " | ";
				else myfile << " ";
				
			}
			myfile << "\r\n";
			if (i == 2 || i == 5)
				myfile << "-----------------------" << "\r\n";
		}
		myfile.close();
	}
	
	//Fill in 1s where definite
	int fill(const Layer* base)
	{
		int row = 0;
		int column = 0;
		int block = 0;
		
		int filled = 0;
		//Sum up totals in each Unit
		for (int r = 0; r <= 8; r++)
		{
			for (int i = 0; i <= 8; i++)
				row+= this->rows[r].Data[i]->data;
			if (row == -1) { //If there's only one -1 in row, must be a 1. Same applies for columns and blocks
				filled = 1;
				for (int i = 0; i <= 8; i++)
					if (this->rows[r].Data[i]->data == -1)
						this->rows[r].Data[i]->data = 1; }
			row = 0;
		}
		this->clean(base);
			
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
		this->clean(base);
				
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
		this->clean(base);
		
		return filled;
	}
	
	//Functions that are called to reserve spots for layers with matching units. Returns index number of reservable items
	int find_buns(Layer* _layer)
	{
		int blocksum = 0;
		
		for (int b = 0; b <= 8; b++) {
			for (int i = 0; i <= 8; i++)
			{
				blocksum+= this->blocks[b].Data[i]->data;
			}
			
			if (blocksum == -2)
				if (compare_buns(b, _layer))
					return b;
				
			blocksum = 0;
		}
		return -1;
	}
	int find_runs(Layer* _layer)
	{
		int rowsum = 0;
		
		for (int b = 0; b <= 8; b++) {
			for (int i = 0; i <= 8; i++)
			{
				rowsum+= this->rows[b].Data[i]->data;
			}
			
			if (rowsum == -2)
				if (compare_runs(b, _layer))
					return b;
			rowsum = 0;
		}
		return -1;
	}
	int find_cuns(Layer* _layer)
	{
		int columnsum = 0;
		
		for (int b = 0; b <= 8; b++) {
			for (int i = 0; i <= 8; i++)
			{
				columnsum+= this->columns[b].Data[i]->data;
			}
			
			if (columnsum == -2)
				if (compare_cuns(b, _layer))
					return b;
			columnsum = 0;
		}
		return -1;
	}
	
	//Functions that compare Units to see if they are missing the same items
	int compare_buns(int block, Layer* _layer)
	{
		for (int i = 0; i <= 8; i++)
			if (this->blocks[block].Data[i]->data != _layer->blocks[block].Data[i]->data)
				return 0;
		return 1;
	}
	int compare_runs(int row, Layer* _layer)
	{
		for (int i = 0; i <= 8; i++)
			if (this->rows[row].Data[i]->data != _layer->rows[row].Data[i]->data)
				return 0;
		return 1;
	}
	int compare_cuns(int column, Layer* _layer)
	{
		for (int i = 0; i <= 8; i++)
			if (this->columns[column].Data[i]->data != _layer->columns[column].Data[i]->data)
				return 0;
		return 1;
	}
	
	//Functions that 0 out reservable items based on index from find_uns
	int big_buns(int block, Layer* _layer)
	{
		if (block == -1) return 0;
		for (int i = 0; i <= 8; i++)
		{
			if (this->blocks[block].Data[i]->data == -1)
				_layer->blocks[block].Data[i]->data = 0;
		}
		return 1;
	}
	int big_runs(int row, Layer* _layer)
	{
		if (row == -1) return 0;
		for (int i = 0; i <= 8; i++)
		{
			if (this->rows[row].Data[i]->data == -1)
				_layer->rows[row].Data[i]->data = 0;
		}
		return 1;
	}
	int big_cuns(int column, Layer* _layer)
	{
		if (column == -1) return 0;
		for (int i = 0; i <= 8; i++)
		{
			if (this->columns[column].Data[i]->data == -1)
				_layer->columns[column].Data[i]->data = 0;
		}
		return 1;
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
	
	Layer* layers[10] = { base, l1, l2, l3, l4, l5, l6, l7, l8, l9};
	
	//Constructor
	Board(string filename)
	{
		ifstream infile(filename);
		string line;
		int i = 0;

		//Read sudoku board from file
		while (getline(infile, line)) {
			
			istringstream iss(line);
			for (int j = 0; j<=8; j++)
				if (!(iss >> this->base->rows[i].Data[j]->data)) { break; } // error
			i++;
		}
		//Link rows to columns and blocks
		for (int r = 0; r <= 8; r++) {
			for (int i = 0; i <= 8; i++)
			{
				//Columns
				this->base->columns[i].link(r, this->base->rows[r].Data[i]);
				
				//Blocks
				if (r <= 2)
				{
					if (i <= 2)
						this->base->blocks[0].link(i+3*r, this->base->rows[r].Data[i]);
					else if (i >= 3 && i <= 5)
						this->base->blocks[1].link(i-3+3*r, this->base->rows[r].Data[i]);
					else
						this->base->blocks[2].link(i-6+3*r, this->base->rows[r].Data[i]);
				}
				else if (r >= 3 && r <= 5)
				{
					if (i <= 2)
						this->base->blocks[3].link(i+3*(r-3), this->base->rows[r].Data[i]);
					else if (i >= 3 && i <= 5)
						this->base->blocks[4].link(i-3+3*(r-3), this->base->rows[r].Data[i]);
					else
					this->base->blocks[5].link(i-6+3*(r-3), this->base->rows[r].Data[i]);
				}
				else
				{
					if (i <= 2)
						this->base->blocks[6].link(i+3*(r-6), this->base->rows[r].Data[i]);
					else if (i >= 3 && i <= 5)
						this->base->blocks[7].link(i-3+3*(r-6), this->base->rows[r].Data[i]);
					else
						this->base->blocks[8].link(i-6+3*(r-6), this->base->rows[r].Data[i]);
				}
			}
		}
	}
	
	//Extrapolate base layer into layers 1-9
	void extrapolate()
	{
		for (int i = 1; i <= 9; i++)
			layers[i]->populate(base);
		for (int i = 1; i <= 9; i++)
			layers[i]->clean(base);
	}
	
	//Prints all Layers with formating
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
	void print_base()
	{
		for (int i = 0; i<=8; i++) {
			for (int j = 0; j<=8; j++)
			{
				if (j == 0)
					cout << " "; 
				if (this->base->rows[i].Data[j]->data == 0) 
					cout << " ";
				else
					cout << this->base->rows[i].Data[j]->data;
				
				if (j == 2 || j == 5)
					cout << " | ";
				else cout << " ";
				
			}
			cout << endl;
			if (i == 2 || i == 5)
				cout << "-----------------------" << endl;
		}
		cout << endl;
	}
	//Writes all Layers to file with formating
	void write_all()
	{
		for (int i = 0; i <= 9; i++)
			layers[i]->write();
	}
	
	//Fill all layers till nothing can be filled
	void fill_all()
	{
		int filled = 1;
		while (filled)
		{
			filled = 0;
			for (int i = 1; i <= 9; i++)
				filled+= layers[i]->fill(base);
		}
	}
	
	//Populates base board
	void populate()
	{
		for (int i = 1; i <= 9; i++)
			this->base->populate_base(layers[i]);
	}

	//Finds and reserves unkowns (uns) that can't be determined with simple methods
	void uns()
	{
		for (int i = 1; i<=9; i++)
			for (int j = i+1; j<=9; j++)
				for (int b = 1; b<=9; b++)
					if (b != i && b != j)
					{
						layers[i]->big_buns(layers[i]->find_buns(layers[j]), layers[b]);
						layers[i]->big_runs(layers[i]->find_runs(layers[j]), layers[b]);
						layers[i]->big_cuns(layers[i]->find_cuns(layers[j]), layers[b]);
					}
	}

	//Check if board is full
	bool done()
	{
		for (int r = 0; r <= 8; r++)
			for (int i = 0; i <= 8; i++)
				if (this->base->rows[r].Data[i]->data == 0)
					return false;
		return true;
	}
	
	//Return sum of board items. Used to check if board has changed
	int sum()
	{
		int sum = 0;
		for (int r = 0; r <= 8; r++)
			for (int i = 0; i <= 8; i++)
				sum += this->base->rows[r].Data[i]->data;
		return sum;
	}
	
	void solve()
	{
		this->extrapolate();
		this->fill_all();
		
		int boardsum = 0;
		
		while (boardsum != this->sum())
		{
			boardsum = this->sum();
			this->uns();
			this->populate();
			this->fill_all();
			for (int i = 1; i <= 9; i++)
				this->layers[i]->block_reserve();
			this->fill_all();
			this->populate();
		}
		
		if (this->sum()!=405)
		{
			cout << endl;
			this->print_base();
			cout << "Unable to solve with current methods" << endl << endl;
		}
		
		else
		{
			cout << endl << "Solved! Written to file: 0.txt" << endl << endl;
			this->base->write();
		}
	}
}; //End Board


int main()
{
	Board main("sudoku1.txt");
	
	main.solve();
	
}