#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <stdio.h>
using namespace std;

class Person {
public:
	map <string, string> studprop;
};

class Table {

private:


public:

	vector<string> names_column;
	vector<Person> table;

	void delete_table(string name) {
		name += ".txt";
		int ok = remove(name.c_str());
	}

	void load_file(string name) {
		ifstream input(name + ".txt");
		string names;
		getline(input, names);
		string tmp = "";

		for (auto u : names)
		{
			if (u == ' ') {
				if (tmp != "") {
					names_column.push_back(tmp);
					tmp = "";
				}
			}
			else {
				tmp += u;
			}
		}
		if (tmp != "") {
			names_column.push_back(tmp);
		}

		int posColumn = 0;
		string now;

		while (input >> now) {
			if (posColumn == 0) {
				Person stud;
				table.push_back(stud);
			}
			table[table.size() - 1].studprop[names_column[posColumn]] = now;
			posColumn++;
			posColumn %= names_column.size();
		}
	}

	void delete_column() {

		int count = 0;
		string column;
		cout << "Enter name of column:";

		cin >> column;
		for (int i = 0; i < names_column.size(); i++) {
			if (column == names_column[i]) count++;
		}

		if (count == 1) {
			for (int i = 0; i < table.size(); i++) {
				table[i].studprop.erase(column);
			}
			names_column.erase(find(names_column.begin(), names_column.end(), column));
		}
		else cout << "No column";
	}

	void add_column() {

		int count = 0;
		string column;
		cout << "Enter name of column:";

		cin >> column;
		for (int i = 0; i < names_column.size(); i++) {
			if (column == names_column[i]) count++;
		}

		if (count == 0) {
			names_column.push_back(column);
			for (int i = 0; i < table.size(); i++) {
				table[i].studprop[column] = "_";
			}
		}
		else {
			bool isWork = true;
			string tmp = column + "_" + to_string(count);

			while (isWork) {
				tmp = column + "_" + to_string(count);
				isWork = false;
				for (int i = 0; i < names_column.size(); i++) {
					if (tmp == names_column[i]) {
						isWork = true;
						count++;
					}
				}
			}
			names_column.push_back(tmp);
			for (int i = 0; i < table.size(); i++) {
				table[i].studprop[tmp] = "_";
			}
		}

	}

	void show() {

		cout << "Click on 'ESC' to close a table" << endl;

		for (int i = 0; i < names_column.size(); i++) {
			cout << setw(10) << names_column[i];
		}

		cout << endl;


		for (int i = 0; i < table.size(); i++) {
			for (auto u : names_column) {
				cout << setw(10) << table[i].studprop[u];
			}
			cout << endl;
		}
		while (static_cast<int>(_getch()) != 27) continue;
	}

	void add_item() {
		Person tmp;
		for (auto u : names_column) {
			cout << "Enter " << u << " :";
			string prop;
			cin >> prop;
			cout << endl;
			tmp.studprop[u] = prop;
		}
		table.push_back(tmp);
	}

	void save_file() {

		string name;
		cout << "Please enter file name: ";
		cin >> name;
		ofstream output(name + ".txt");

		for (int i = 0; i < names_column.size(); i++) {
			output << setw(10) << names_column[i] << " ";
		}

		output << endl;

		for (int i = 0; i < table.size(); i++) {
			for (auto u : names_column) {
				output << setw(10) << table[i].studprop[u] << " ";
			}
			output << endl;
		}
	}

};

void viewCommands(int parametr) {

	cout << "_____________________________________________________________________________________" << endl;
	cout << "Syntax: 'name of command'" << endl
		<< "Commands:" << endl;

	if (parametr == 1) {
		cout << "1)Save table        2)Delete table        3)Edit table		4)Load table		5)Union table" << endl;
	}

	else if (parametr == 2) {
		cout << "1)Add student's info        2)Delete student's info       3)Add column		" << endl << "4)Delete column		5)Show table		6)Main menu" << endl;
	}

	cout << "_____________________________________________________________________________________" << endl;
}

Table table_ass(string column, Table startTable, Table secondTable) {
	Table result;
	for (auto u : startTable.table) {
		for (auto k : secondTable.table) {
			if (u.studprop[column] == k.studprop[column]) {
				Person tmp;
				bool addColumn = result.names_column.size() == 0;
				for (auto w : startTable.names_column) {
					tmp.studprop[w] = u.studprop[w];
					if (addColumn) {
						result.names_column.push_back(w);
					}
				}
				for (auto w : secondTable.names_column) {
					tmp.studprop[w] = k.studprop[w];
					if (addColumn && w != column) {
						result.names_column.push_back(w);
					}
				}
				result.table.push_back(tmp);
			}
		}
	}
	return result;
}

int main(void) {
	string name;
	string command = "0";
	map <string, Table> tables;

	viewCommands(1);

	while (cin >> command) {

		if (command == "Edit") {

			system("CLS");
			viewCommands(2);

			cout << "Please enter table name: ";
			cin >> name;

			system("CLS");
			viewCommands(2);

		}

		if (command == "Show") {
			tables[name].show();
			system("CLS");
			viewCommands(2);
		}

		if (command == "Save") {
			tables[name].save_file();
			system("CLS");
			viewCommands(1);
		}

		if (command == "Add") {
			tables[name].add_item();
			system("CLS");
			viewCommands(2);
		}

		if (command == "Addcolumn") {
			tables[name].add_column();
			system("CLS");
			viewCommands(2);
		}

		if (command == "Deletecolumn") {
			tables[name].delete_column();
			system("CLS");
			viewCommands(2);
		}

		if (command == "Load") {
			cout << "Enter file name:";
			cin >> name;

			Table tmp; tmp.load_file(name);
			tables[name] = tmp;
			system("CLS");
			viewCommands(1);
		}

		if (command == "Delete") {
			if (tables.size() != 0) {
				tables[name].delete_table(name);
				//delete tables[name];
				tables.erase(name);
			}
			system("CLS");
			viewCommands(1);
		}

		if (command == "Main") {
			system("CLS");
			viewCommands(1);
		}

		if (command == "Union") {

			cout << "Enter table's count:";
			int n;
			cin >> n;

			cout << "Enter first name of table:";

			string name;
			string nameColumn;
			cin >> name;

			Table result = tables[name];
			for (int i = 0; i < n - 1; i++)
			{
				cout << "Enter name of table:";
				cin >> name;
				cout << "Enter name of column:";
				cin >> nameColumn;
				result = table_ass(nameColumn, result, tables[name]);
				result.show();
			}
		}
	}
}

