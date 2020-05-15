/* Напишите программу, которая выводит на экран наименьший элемент введенного пользователем массива целых чисел. 
Для доступа к элементам массива используйте указатель.*/

#include <iostream>
#include <string>
#include <sstream>  // для превращения строки в число

using std::cout; using std::cin; using std::endl;
using std::string;

// ОБЪЯВЛЕНИЕ ВСЕХ ФУНКЦИЙ:
const string get_data_from_user();
const unsigned get_array_size_from_string(const string&);
inline bool is_number(const string&, int&);
void fullfill_array_from_string(const string&, int*);
void print_minimum(const int*, const unsigned&);

int main()
{
	setlocale(LC_CTYPE, "rus"); // подключаем кириллицу:

	const string users_array = get_data_from_user();

	// длина будущего массива:
    const unsigned length{ get_array_size_from_string (users_array)};
	/* т.к. размер не был известен при компиляции и по условию задачи нужно использовать указатель, 
	   массив будем выделять динамически: */
	int* array = new int[length];

	fullfill_array_from_string(users_array, array);
	print_minimum(array, length);

	delete[] array;
	array = nullptr;    // здесь это делать не обязательно, но для красоты
	return 0;
}

// ОПРЕДЕЛЕНИЯ ВСЕХ ОБЪЯВЛЕННЫХ ФУНКЦИЙ:
// 1. получаем от пользователя последовательность чисел и, возможно, не только числа в виде строки
const string get_data_from_user()
{
	cout << "Вводите последовательность целых чисел через пробел, прочие знаки будут проигнорированы.\n"
		<< "Для окончания ввода нажмите enter: ";
	string input;
	getline(cin, input);
	return input;
}

// 2. получаем количество целых чисел в строке, введённой пользователем
const unsigned get_array_size_from_string(const string& users_input)
{
	string future_number{};                // вспомогательная переменная для символов строки до пробела
	unsigned numbers_counter{ 0 };         // счётчик чисел в строке

	// будем собирать каждое число по символам-цифрам, каждый пробел проверяем, получили ли число, и если да, то считаем его
	for (unsigned int i = 0; i < users_input.length(); i++)
	{
		// если после пробела знак минус или просто число
		if (((future_number == "") && (users_input[i] == '-')) || (isdigit(users_input[i])))
			future_number += users_input[i];
		// если пробел или конец строки
		if ((users_input[i] == ' ') || (i == (users_input.length() - 1)))
		{
			if (future_number != "")
			{
				int one_more_number{ 0 };
				if (is_number(future_number, one_more_number))
					numbers_counter++;
			}
			future_number = "";
		}
	}
	return numbers_counter;
}

// 3. заполняем массив, переданный в виде указателя, числами из строки, введённой пользователем
void fullfill_array_from_string(const string& users_input, int* array)
{
	string future_number{};                // будущее число в виде строки
	// будем собирать каждое число по символам-цифрам, каждый пробел добавляем число в массив и начинаем заново
	for (unsigned int i = 0; i < users_input.length(); i++)
	{
		// если после пробела знак минус или просто число
		if (((future_number == "") && (users_input[i] == '-')) || (isdigit(users_input[i])))
			future_number += users_input[i];
		// если пробел или конец строки
		if ((users_input[i] == ' ') || (i == (users_input.length() - 1)))
		{
			if (future_number != "")
			{
				int one_more_number{ 0 };
				if (is_number(future_number, one_more_number))
				{
					*array = one_more_number;
					array++;
				}
			}
			future_number = "";
		}
	}
}

// 4. функция проверки, что можно превратить строку в число (выдаёт false, если не получилось)
inline bool is_number(const string& str, int& number)
{
	std::istringstream istream(str);
	return (istream >> number) ? true : false;
}

// 5. вывод на экран минимального элемента массива, переданного в виде указателя и длины
void print_minimum(const int* array, const unsigned& length)
{
	if (length == 0)
		cout << "В последовательности нет чисел" << endl;
	else
	{
		int min{ *array };
		for (unsigned i = 0; i < length; ++i)
		{
			if (*array < min)
				min = *array;
			array++;
		}
		cout << "Наименьший элемент введенного массива: " << min << endl;
	}
}