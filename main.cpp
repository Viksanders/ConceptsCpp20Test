#include <iostream>
#include <concepts>
#include <string>

class Test1		//с этим классом всЄ в пор€дке
{
public:

	Test1()
	{
		std::cout << "Usual constructor\n";
	}

	~Test1()
	{
		std::cout << "Usual destructor\n";
	}

	int hash()		//int коневертируетс€ в long, согласно заданию
	{
		return 42;
	}

	std::string toString()
	{
		std::string s = "Hello, I am string\n";
		return s;
	}
};

class Test2
{
public:

	Test2()
	{
		std::cout << "Usual constructor\n";
	}

	virtual ~Test2()		//виртуальный деструктор есть
	{
		std::cout << "Virtual destructor\n";
	}

	int hash()
	{
		return 42;
	}

	std::string toString()
	{
		std::string s = "Hello, I am string\n";
		return s;
	}
};

class Test3
{
public:

	Test3()
	{
		std::cout << "Usual constructor\n";
	}

	~Test3()
	{
		std::cout << "Usual destructor\n";
	}

	//нет метода hash

	std::string toString()
	{
		std::string s = "Hello, I am string\n";
		return s;
	}
};

class Test4
{
public:

	Test4()
	{
		std::cout << "Usual constructor\n";
	}

	~Test4()
	{
		std::cout << "Usual destructor\n";
	}

	int hash()
	{
		return 42;
	}

	void toString()		//метод возвращает не то
	{
		std::string s = "Hello, I am string\n";
		std::cout << s;
	}
};

class Test5 : public Test2		//тоже вирутальный деструктор
{};

template <typename T> concept SimpleConcept_1 = requires(T type)
{
	{ type.hash() } -> std::convertible_to<long>;
	{ type.toString() } -> std::same_as<std::string>;
};

template <typename T> concept SimpleConcept_2 = std::has_virtual_destructor<T>::value;


template <typename T> concept ComplexConcept = SimpleConcept_1<T> && !SimpleConcept_2<T>;


template <ComplexConcept T> 
void FunctionForTest(T& var)
{
	std::cout << "\n\n FUNCTION FOR TEST \n\n";
	std::cout << var.toString() << "\n";
	std::cout << var.hash() << "\n\n";
	std::cout << "\n\n FUNCTION FOR TEST END \n\n";
}

int main()
{
	Test1 t1;
	Test2 t2;
	Test3 t3;
	Test4 t4;

	FunctionForTest(t1);			//работает нормально
	//FunctionForTest(t2);			//ошибка компил€ции, виртуальный деструктор у t2
	//FunctionForTest(t3);			//нет hash(), ошибка при компл€ции
	//FunctionForTest(t4);			//toString() возвращает void, ошибка при компл€ции

	return 0;
}