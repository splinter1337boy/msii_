// _lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

std::string simptomi[16] = {
	"Общее недомогание",
	"Сухость, першение",
	"Кашель сначала сухой, затем мокрый",
	"Голос хриплый или беззвучный",
	"Иногда боль при глотании",
	"Головная боль",
	"Повышенная температура тела",
	"Быстрая утомляемость гортани",
	"Периодический кашель с мокротой",
	"Охриплость с афонией",
	"Ощущение дискомфорта в гортани",
	"Жжение в горле",
	"Кашель при обострении",
	"Сухой кашель",
	"Слизистая покрыта густой слизью",
	"Откашливание с прожилками крови"
};

std::string diagnoz[4] = {
	"Ларингит острый",
	"Ларингит хронический катаральный",
	"Ларингит хронический гипертрофический",
	"Ларингит хронический атрофический"
};

class ArrayException : public std::exception {
private:
	std::string m_error;

public:
	ArrayException(std::string error) : m_error(error) {
	}

	const char* what() throw() { return m_error.c_str(); }

};

class Simptom {
private:
	std::string m_name;

public:
	Simptom(std::string name = "") : m_name(name) {
	}

	Simptom(Simptom& o) {
		m_name = o.m_name;
	}

	virtual ~Simptom() {}

	Simptom& operator = (Simptom& s) {
		if(this == &s) return *this;

		m_name = s.m_name;
		
		return *this;
	} // протестить, попробовать убрать этот метод

	Simptom& operator = (std::string name) {
		m_name = name;

		return *this;
	}

	std::string getSimptom() { return m_name; }
};

std::ostream& operator << (std::ostream& out, Simptom& s) {
	out << s.getSimptom() << "\n";
	
	return out;
}


class TableOfSimptoms : public Simptom {
private:
	int* m_code;
	int m_length;
	int m_maxLength;
	Simptom** s;

public:
	TableOfSimptoms() : Simptom() {
		m_code = NULL;
		s = NULL;
		m_length = 0;
		m_maxLength = 100;
	}

	TableOfSimptoms(int length) : m_length(length) {
		if(m_length > 0) {
			if(m_length <= 16) {
				s = new Simptom*[m_length];
				m_code = new int[m_length];
				for(int i = 0; i < m_length; i++) {
					s[i] = new Simptom(simptomi[i]);
					m_code[i] = i;
				}
			} else {
				int m_size = 16;
				s = new Simptom*[m_length];
				m_code = new int[m_length];
				for(int i = 0; i < m_size; i++) {
					s[i] = new Simptom(simptomi[i]);
					m_code[i] = i;
				}
			}
		} else {
			m_code = NULL;
			m_length = 0;
			m_maxLength = 10;
			s = NULL;
		}
	}

	TableOfSimptoms(TableOfSimptoms& o) {
		int m_length = o.m_length;
		m_code = new int[m_length];
		s = new Simptom*[m_length];
		for(int i = 0; i < m_length; i++) {
			s[i] = new Simptom(o[i]);
		}
	}


	~TableOfSimptoms() { for(int i = 0; i < m_length; i++) delete s[i]; delete[] s; delete[] m_code; }

	int* getCodes() { return m_code; }

	int getLength() { return m_length; }
	
	Simptom& operator[] (const int index) { 
		if(index >= 0 && index < m_length) {
			return *s[index];
		}

		throw ArrayException(std::to_string((_ULonglong)index));
	}
};

std::ostream& operator << (std::ostream& out, TableOfSimptoms& ts) {
	out << "Таблица Симптомов: \n";

	for(int i = 0; i < ts.getLength(); i++) {
		out << "Код: " << ts.getCodes()[i] << ", Симптом: " << ts[i] << "\n";
	}
		
	return out;
}


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian"); // задаём русский текст

	try {

		TableOfSimptoms tbl(16);

		std::cout << tbl << "\n";

		getch();
	
	} catch(ArrayException& e) {
		std::cerr << "Overflow, index " << e.what() << "\n";
	}
	

	
	return 0;
}

