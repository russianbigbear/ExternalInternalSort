#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <locale>
#include <tchar.h>
#include <string>
using namespace std;

#define count_elements 100000

/*
Структура "Элемент"
поля:
_numbers - целочисленный массив с 3 элементами;
_strings - массив, содержащий 2 строки;
методы:
_element() - конструктор без параметра;
_element(int first, int second, int third, string str_f, string str_s) - конструктор с параметром;
~_element() - деструктор элемента
compare_if_they_are_equal(_element *other_element, int field_number) - метод сравнения текущего и переданного аргументов, если равны то true
compare_if_the_first_is_greater_than_the_second(_element *other_element, int field_number)  - метод сравнения текущего и переданного аргументов, если первый больше второго то true
*/
struct _element {
	int _numbers[3];
	string _strings[2];

	/*конструктор без параметра*/
	_element() {
		//генерация трёх численных полей
		for (int i = 0; i < 3;)
			_numbers[i++] = rand() % 10;

		//генерация двух строк
		string tmp[2];
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < rand() % 3 + 1; j++) {
				tmp[i] += (char)(rand() % 26 + 65);
			}
			_strings[i] = tmp[i];
		}
	}

	/*конструктор с параметром (first-первое число, second-второе число, third-третье число, str_f-первая строка, str_s-вторая строка)*/
	_element(int first, int second, int third, string str_f, string str_s) {
		_numbers[0] = first;
		_numbers[1] = second;
		_numbers[2] = third;
		_strings[0] = str_f;
		_strings[1] = str_s;
	}

	/*деструктор*/
	~_element() {}

	/*сравнение двух элементов; возращает true, если элементы равны, иначе false*/
	bool compare_element(_element *other_element, int field_number) {

		switch (field_number) {
			//сравнение числовых полей
		case 1: {
			if (this->_numbers[0] == other_element->_numbers[0])
				return true;
			else
				return false;
			break;
		}
		case 2: {
			if (this->_numbers[1] == other_element->_numbers[1])
				return true;
			else
				return false;
			break;
		}
		case 3: {
			if (this->_numbers[2] == other_element->_numbers[2])
				return true;
			else
				return false;
			break;
		}
				//сравнение строковых полей
		case 4: {
			if (this->_strings[0] == other_element->_strings[0])
				return true;
			else
				return false;
			break;
		}
		case 5: {
			if (this->_strings[1] == other_element->_strings[1])
				return true;
			else
				return false;
			break;
		}

		default: {
			return true;
			break;
		}
		}
	}

	/*сравнение двух элементов; возращает true, если первый элемент больше второго, иначе false*/
	bool largest_element(_element *other_element, int field_number) {

		switch (field_number) {
			//сравнение числовых полей
		case 1: {
			if (this->_numbers[0] > other_element->_numbers[0])
				return true;
			else
				return false;
			break;
		}
		case 2: {
			if (this->_numbers[1] > other_element->_numbers[1])
				return true;
			else
				return false;
			break;
		}
		case 3: {
			if (this->_numbers[2] > other_element->_numbers[2])
				return true;
			else
				return false;
			break;
		}
				//сравнение строковых полей
		case 4: {
			if (this->_strings[0] > other_element->_strings[0])
				return true;
			else
				return false;
			break;
		}
		case 5: {
			if (this->_strings[1] > other_element->_strings[1])
				return true;
			else
				return false;
			break;
		}

		default: {
			return true;
			break;
		}
		}
	}
	
	/*сравнение двух элементов, если второй элемент больше первого, возращает true*/
	bool compare_all_element(_element *other_element, vector<int> sort_fields) {
		for (int i = 0; i < 3; i++) {
			switch (sort_fields[i]) {
			case 1:
				if (this->_numbers[0] < other_element->_numbers[0]) return true;
				if (this->_numbers[0] > other_element->_numbers[0]) return false;
				break;
			case 2:
				if (this->_numbers[1] < other_element->_numbers[1]) return true;
				if (this->_numbers[1] > other_element->_numbers[1]) return false;
				break;
			case 3:
				if (this->_numbers[2] < other_element->_numbers[2]) return true;
				if (this->_numbers[2] > other_element->_numbers[2]) return false;
				break;
			case 4:
				if (this->_strings[0] < other_element->_strings[0]) return true;
				if (this->_strings[0] > other_element->_strings[0]) return false;
				break;
			case 5:
				if (this->_strings[1] < other_element->_strings[1]) return true;
				if (this->_strings[1] > other_element->_strings[1]) return false;
				break;
			default:
				break;
			}
		}

		return true;
	}	

};


/*
Класс "Массив данных"
поля:
_element - елемент, содержащий 3 целых поля, и 2 строковых;
методы:
reading_from_a_file(string name, vector<_element*> &elements) - чтение элементов из файла и запись их в вектор элементов
sifting(vector<_element*> &tmp_elements, int current, int size, int number_of_sort_field, int first_index) - проссеивание элементов, для построения пирамиды
sort(vector<_element*> &tmp_elements, int number_of_sort_field, int first_index) - пирамидальная сортировка
*/
class data_array {
public:
	vector<_element*> _elements;

	/*чтение элементов из файла*/
	void reading_from_a_file(string name) {

		ifstream fin; //входной поток
		fin.open(name); //открыли поток

		//читаем элементы
		while (!fin.eof()) {

			int first; fin >> first;
			int second; fin >> second;
			int third; fin >> third;
			string str_f; fin >> str_f;
			string str_s; fin >> str_s;

			_element *tmp = new _element(first, second, third, str_f, str_s);

			if (!fin.eof()) _elements.push_back(tmp);

		}

		fin.close(); //закрыли поток

	}

	/*проссеивание, используется для построения пирамиды*/
	void sifting(vector<_element*> &tmp_elements, int current, int size, int number_of_sort_field, int first_index) {
		if (size == 1) return;

		int index_child = 0;

		//выбираем большего предка; если правого предка нет, то берем левого
		if ((current + 1) * 2 == size)
			index_child = current * 2 + 1;
		else
			//если первый элемент больше второго, по какому то столбцу, то 
			if (tmp_elements[current * 2 + 1]->largest_element(tmp_elements[current * 2 + 2], number_of_sort_field))
				index_child = current * 2 + 1;
			else
				index_child = current * 2 + 2;

		//если текущее число меньше предка, меняем их
		if (tmp_elements[index_child]->largest_element(tmp_elements[current], number_of_sort_field)) {
			//переставляем во вспомогательном векторе
			_element *tmp = tmp_elements[current];
			tmp_elements[current] = tmp_elements[index_child];
			tmp_elements[index_child] = tmp;

			//переставляем в основном векторе
			_element *tmpp = _elements[current + first_index];
			_elements[current + first_index] = _elements[index_child + first_index];
			_elements[index_child + first_index] = tmpp;
		}
		//если предок больше, меняем их
		if (index_child * 2 + 2 <= size)
			sifting(tmp_elements, index_child, size, number_of_sort_field, first_index);
	}

	/*сортировка пирамидой*/
	void sort(vector<_element*> &tmp_elements, int number_of_sort_field, int first_index) {

		//1 этап, преобразование в пирамиду путём проссеивания
		for (int i = tmp_elements.size() / 2 - 1; i >= 0; i--) {
			sifting(tmp_elements, i, tmp_elements.size(), number_of_sort_field, first_index);
		}

		//2 этап, сортировка пирамиды
		for (int i = tmp_elements.size() - 1; i >= 1; i--) {

			//меняем первый и последний элемент во вспомогательном векторе
			_element* tmp = tmp_elements[0];
			tmp_elements[0] = tmp_elements[i];
			tmp_elements[i] = tmp;

			//меняем в основном векторе
			_element *tmpp = _elements[0 + first_index];
			_elements[0 + first_index] = _elements[i + first_index];
			_elements[i + first_index] = tmpp;

			//просеиваем
			sifting(tmp_elements, 0, i, number_of_sort_field, first_index);
		}
	}

	/*сортировка пирамидой по заданным столбцам*/
	void pill_sort(vector<int> sort_fields) {

		//первая сортировка по всему столбцу
		vector<_element*> tmp_elements;								// вспомогательный вектор из одинаковых элементов
		for (unsigned int i = 0; i < this->_elements.size(); i++)
			tmp_elements.push_back(this->_elements[i]);

		this->sort(tmp_elements, sort_fields[0], 0);

		//теперь сортируем в зависимости от прошлой сортировки
		for (int i = 1; i < 3; i++) {

			tmp_elements.clear();						//очищаем вспомогательный вектор

			int index = sort_fields[i];					//индекс сортируемого столбца
			int index_last = sort_fields[i - 1];		//индекс прошлого сортированного столбца

			int index_sample = 0;								//индекс первого элемента, с которого идут одинаковые
			_element* sample = this->_elements[index_sample];	//присваиваем образцу первый элемент, далее с ним и будем сравнивать

			int size_obj = this->_elements.size(); //размер вектора элементов

			for (unsigned int j = 0; j < size_obj; j++) {
				if (sample->compare_element(this->_elements[j], index_last))
					tmp_elements.push_back(this->_elements[j]);

				else {

					this->sort(tmp_elements, index, index_sample);
					tmp_elements.clear();

					sample = this->_elements[j];
					index_sample = j;
					tmp_elements.push_back(this->_elements[j]);
				}


				if (j == this->_elements.size() - 1) {
					this->sort(tmp_elements, index, index_sample);
				}
			}

		}		
	}
};

/*функция деления строки на подстроки*/
void str_split(vector<string> *list, string str){ 

	string tok = " ";
	int b,
		e = 0;

	while ( ( b = str.find_first_not_of(tok, e)) != str.npos) {
		e = str.find_first_of(tok, b);
		list->push_back(str.substr(b, e - b));
		b = e;
	}
	
}

/*функция копирование файла*/
void copy_file(string nameF, string nameS) {

	ifstream infile;  infile.open(nameF);
	ofstream outfile; outfile.open(nameS);
	string str;

	getline(infile, str);
	while(true){
		
		outfile << str;
		getline(infile, str);

		if (str != "-1 -1 -1 *** ***") outfile << endl;
		else break;
	} 
}

/*функция поиска количества вхождений строки в файл*/
int StrInFile() {
	//подсчёт количества блоков
	ifstream ifs; ifs.open("buffer_file.txt");
	int count = 0;

	while (!ifs.eof()) {
		string temp_str;
		getline(ifs, temp_str);

		if (temp_str == "-1 -1 -1 *** ***") count++;
	}

	ifs.close();

	fflush(stdin); fflush(stdout);

	return count;
}

/*функция записи блоков в буфферный файл*/
void block_recording(ifstream & main, string name, int border) {

	string str;
	ofstream ofs; ofs.open(name);

	for (int i = 0; i < border;) {
		getline(main, str);
		if (i == border - 1)
			if (str == "-1 -1 -1 *** ***") {
				ofs << str;
				i++;
			}
			else
				ofs << str << endl;
		else
			if (str == "-1 -1 -1 *** ***") {
				ofs << str << endl;
				i++;
			}
			else
				ofs << str << endl;
	}

	ofs.close();
	fflush(stdin); fflush(stdout);
}

/*функция слияния двух блоков*/
void merge(vector<int> fields, int cab) {

	ofstream bofs;
	bofs.open("buffer_file.txt");

	ifstream ifile_f; ifstream ifile_s;
	ifile_f.open("file1.txt"); 
	ifile_s.open("file2.txt");

	int cab_counter = 0;

	string str_f; getline(ifile_f, str_f);
	string str_s; getline(ifile_s, str_s);

	do {
		//если 1 строка равна порогу, заносим строки 2 файла в основной, пока не дойдем до порога
		if (str_f == "-1 -1 -1 *** ***") {
			while (str_s != "-1 -1 -1 *** ***") {
				bofs << str_s << endl;
				getline(ifile_s, str_s);
			}
			cab_counter++;
			
			if(cab_counter != cab)
				bofs << "-1 -1 -1 *** ***" << endl;
			else
				bofs << "-1 -1 -1 *** ***" ;
			
			getline(ifile_f, str_f);
			getline(ifile_s, str_s);
		}
		else
			//если 2 строка равна порогу, заносим строки 1 файла в основной, пока не дойдем до порога
			if (str_s == "-1 -1 -1 *** ***") {
				while (str_f != "-1 -1 -1 *** ***") {
					bofs << str_f << endl;
					getline(ifile_f, str_f);
				}
				cab_counter++;

				if (cab_counter != cab)
					bofs << "-1 -1 -1 *** ***" << endl;
				else
					bofs << "-1 -1 -1 *** ***";

				getline(ifile_f, str_f);
				getline(ifile_s, str_s);
			}
		//сравниваем 2 строки
			else {

				vector<string> list_f;
				str_split(&list_f, str_f);
				_element *elF = new _element(atoi(list_f[0].c_str()), atoi(list_f[1].c_str()), atoi(list_f[2].c_str()), list_f[3], list_f[4]);
				list_f.clear();

				vector<string> list_s;
				str_split(&list_s, str_s);
				_element *elS = new _element(atoi(list_s[0].c_str()), atoi(list_s[1].c_str()), atoi(list_s[2].c_str()), list_s[3], list_s[4]);
				list_s.clear();


				if (elF->compare_all_element(elS, fields)) {
					bofs << str_f << endl;
					getline(ifile_f, str_f);
				}

				else {
					bofs << str_s << endl;
					getline(ifile_s, str_s);
				}

				delete elF; delete elS;
			}

	} while (!ifile_f.eof() || !ifile_s.eof());


	ifile_f.close(); 
	ifile_s.close();
	bofs.close();
	remove("file1.txt");
	remove("file2.txt");

}

/*функция деления файла на две части*/
void split(vector<int> fields) {
	ifstream main; 

	int max_blocks;
	int cbf ; //количество блоков в первом файле
	int cbs ; //количество блоков во втором файле

	do {
	
		//подсчёт блоков в файле
		max_blocks = StrInFile();

		//разделение на два файла
		if (max_blocks > 1) {
			main.open("buffer_file.txt");

			cbf = max_blocks / 2;
			cbs = max_blocks - cbf; 

			//переписываем блоки в первый файл
			block_recording(main, "file1.txt", cbf);

			//переписываем блоки во второй файл
			block_recording(main, "file2.txt", cbs);

			main.close();
		}
		
		if (max_blocks > 1) merge(fields, cbs);

	} while (max_blocks > 1);

	remove("file1.txt"); remove("file2.txt");
	fflush(stdin); fflush(stdout);

}

/*основная функция*/
int main() {
	srand(time(0));
	setlocale(LC_ALL, "rus");

	//удаление старых файлов в каталоге
	remove("input.txt");
	remove("output.txt");

	//файл для записи
	ofstream mofs;
	mofs.open("input.txt");

	ofstream bofs;
	bofs.open("buffer_file.txt");

	//ввод полей для сортировки
	cout << "Введите номера трёх столбцов для сортировки через пробел: ";
	vector<int> fields(3, 1);
	cin >> fields[0] >> fields[1] >> fields[2];

	///ГЕНЕРАЦИЯ БЛОКОВ, СОРТИРОВКА, ЗАПИСЬ В ФАЙЛ
	for (int all_record = 0; all_record < count_elements;) {

		data_array *block = new data_array();

		///СОЗДАНИЕ БЛОКА И ЗАПИСЬ ЕГО В ФАЙЛ
		ofstream ofs;
		ofs.open("block_file.txt");

		int rand_count = rand() % 1000;

		for (int i = 0; i < rand_count; i++) {
			_element *tmp = new _element();

			//запись блока
			if (i == rand_count) 
				ofs << tmp->_numbers[0] << " "<< tmp->_numbers[1] << " " << tmp->_numbers[2] << " " << tmp->_strings[0] << " " << tmp->_strings[1];
			else
				ofs << tmp->_numbers[0] << " " << tmp->_numbers[1] << " " << tmp->_numbers[2] << " " << tmp->_strings[0] << " " << tmp->_strings[1] << endl;

			//запись во входной файл
			if (all_record + rand_count >= count_elements && i == rand_count -1) 
				mofs << tmp->_numbers[0] << " " << tmp->_numbers[1] << " " << tmp->_numbers[2] << " " << tmp->_strings[0] << " " << tmp->_strings[1];
			else 
				mofs << tmp->_numbers[0] << " " << tmp->_numbers[1] << " " << tmp->_numbers[2] << " " << tmp->_strings[0] << " " << tmp->_strings[1] << endl;

			delete tmp;
		}

		ofs.close();
		fflush(stdin); fflush(stdout);
		///-------------------------------------------------------------------------------------------------------------------------------------------------------

		///ЧИТАЕМ БЛОК ИЗ ФАЙЛА
		block->reading_from_a_file("block_file.txt");
		///-------------------------------------------------------------------------------------------------------------------------------------------------------

		///СОРТИРОВКА БЛОКА
		block->pill_sort(fields);
		///---------------------------------------------------------------------------------------------------------------------------------------------------------

		///ЗАПИСЬ РЕЗУЛЬТАТА СОРТИРОВКИ БЛОКА
		for (unsigned int i = 0; i < block->_elements.size(); i++) {
			bofs << block->_elements[i]->_numbers[0] << " "
				<< block->_elements[i]->_numbers[1] << " "
				<< block->_elements[i]->_numbers[2] << " "
				<< block->_elements[i]->_strings[0] << " "
				<< block->_elements[i]->_strings[1] << endl;
		}

		if(all_record + rand_count >= count_elements)
			bofs << "-1 -1 -1 *** ***";
		else
			bofs << "-1 -1 -1 *** ***" << endl;
		///--------------------------------------------------------------------------------------------------------------------------------------------------------

		all_record += rand_count;
		delete block;
		fflush(stdin); fflush(stdout);
	}

	remove("block_file.txt");
	mofs.close(); bofs.close();

	///---------------------------------------------------------------------------------------------------------------------------------------------------------------------

	///ЕСТЕСТВЕННОЕ СЛИЯНИЕ С ПОРОГОМ

	split(fields);
	copy_file("buffer_file.txt", "output.txt");
	remove("buffer_file.txt");;
    
	///---------------------------------------------------------------------------------------------------------------------------------------
	
}
