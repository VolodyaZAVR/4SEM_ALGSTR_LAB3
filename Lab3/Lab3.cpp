#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "List.h"

using namespace std;

bool alreadyInList(List<string>& arr, string str) {
	for (size_t i = 0; i < arr.getSize(); i++) {
		if (arr[i] == str) {
			return true;
		}
	}
	return false;
}

void bellmanFord(int** A, int V) {
	int k = 0;
	while (k != V) {
		for (int i = 0; i < V; i++) {
			if (i == k)
				continue;
			for (int j = 0; j < V; j++) {
				if (j == k)
					continue;
				if (A[i][j] > A[i][k] + A[k][j] && A[i][k] + A[k][j] > 0)
					A[i][j] = A[i][k] + A[k][j];
			}
		}
		k++;
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	fstream f;

	f.open("input.txt");
	int stringCount = 0;
	string bufString;
	while (!f.eof()) {
		getline(f, bufString);
		stringCount++;
	}
	f.close();

	f.open("input.txt");
	string** input = new string* [stringCount];
	for (int i = 0; i < stringCount; i++) {
		input[i] = new string[4];
		for (int j = 0; j < 3; j++) {
			getline(f, bufString, ';');
			if (bufString != "N/A")
				input[i][j] = bufString;
			else
				input[i][j] = "-1";
		}
		getline(f, bufString);
		if (bufString != "N/A")
			input[i][3] = bufString;
		else
			input[i][3] = "-1";
	}
	f.close();

	for (int i = 0; i < stringCount; i++) {
		for (int j = 0; j < 4; j++) {
			cout << input[i][j] << " ";
		}
		cout << endl;
	}
	List<string> cities;
	for (int i = 0; i < stringCount; i++) {
		if (!alreadyInList(cities, input[i][0])) {
			cities.push_back(input[i][0]);
		}
		if (!alreadyInList(cities, input[i][1])) {
			cities.push_back(input[i][1]);
		}
	}
	for (int i = 0; i < cities.getSize(); i++) {
		cout << i + 1 << " - " << cities[i] << endl;
	}
	int start;
	int end;
	int V = cities.getSize();
	cout << "Ведите номер города из которого вы хотите рассчитать маршрут:" << endl;
	cin >> start;
	cout << "Ведите номер города в который вы хотите рассчитать маршрут:" << endl;
	cin >> end;
	int** matrix = new int* [V];
	for (int i = 0; i < V; i++) {
		matrix[i] = new int[V];
		for (int j = 0; j < V; j++) {
			if (i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = INT_MAX;
		}
	}
	for (int i = 0; i < stringCount; i++) {
		matrix[cities.find(input[i][0])][cities.find(input[i][1])] = atoi(input[i][2].c_str());
		if (matrix[cities.find(input[i][0])][cities.find(input[i][1])] == -1)
			matrix[cities.find(input[i][0])][cities.find(input[i][1])] = INT_MAX;
		matrix[cities.find(input[i][1])][cities.find(input[i][0])] = atoi(input[i][3].c_str());
		if(matrix[cities.find(input[i][1])][cities.find(input[i][0])] == -1)
			matrix[cities.find(input[i][1])][cities.find(input[i][0])] = INT_MAX;
	}
	bellmanFord(matrix, V);
	cout << "Матрица смежности:" << endl;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Кратчайший пусть из города " << cities[start - 1] << " в город " << cities[end - 1] << ": " << matrix[start - 1][end - 1] << endl;
	return 0;
}