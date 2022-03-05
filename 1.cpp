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
	int m_length;
	std::string* m_arr;

public:
	Simptom() {
		m_length = 0;
		m_arr = NULL;
	}

	Simptom(int length) : m_length(length) {
		if(m_length > 0) {
			if(m_length <= 16) {
				m_arr = new std::string[m_length];
				for(int i = 0; i < m_length; i++) {
					m_arr[i] = simptomi[i];
				}
			} else {
				int m_size = 16;
				m_arr = new std::string[m_length];
				for(int i = 0; i < m_size; i++) {
					m_arr[i] = simptomi[i];
				}
			}	
		} else {
			m_length = 0;
			m_arr = NULL;
		}
	}

	Simptom(Simptom& o) {
		m_length = o.m_length;
		m_arr = new std::string[m_length];

		for(int i = 0; i < m_length; i++) {
			m_arr[i] = o.m_arr[i];
		}
	}

	Simptom& operator = (Simptom& s) {
		if(this == &s) { return *this; }
		
		delete[] m_arr;

		m_length = s.m_length;
		m_arr = new std::string[m_length];

		for(int i = 0; i < m_length; i++) {
			m_arr[i] = s.m_arr[i];
		}
		
		return *this;
	}

	std::string& operator[] (const int index) {
		if(index >= 0 && index < m_length) {
			return m_arr[index];
		}

		throw ArrayException(std::to_string((_ULonglong)index));
	}

	int getLength() { return m_length; }
	std::string* getArray() { return m_arr; }
};

std::ostream& operator << (std::ostream& out, Simptom& s) {
	for(int i = 0; i < s.getLength(); i++) {
		out << "Симптом: " << s[i] << "\n";
	}
	
	return out;
}


class TableOfSimptoms : public Simptom {
private:
	int* m_code;
	Simptom* s;

public:
	TableOfSimptoms() : Simptom() {
		m_code = NULL;
		s = NULL;
	}

	TableOfSimptoms(Simptom& s) {
		int length = s.getLength();
		m_code = new int[length];
		this->s = new Simptom(s);
		for(int i = 0; i < length; i++) {
			m_code[i] = i;
		}
	}

	TableOfSimptoms(TableOfSimptoms& o) {
		int length = o.s->getLength();
		m_code = new int[length];
		s = new Simptom(o.getSimptom());

		for(int i = 0; i < length; i++) {
			m_code[i] = o.m_code[i];
		}
	}

	int& operator[] (const int index) {
		if(index >= 0 && index < s->getLength()) {
			return m_code[index];
		}

		throw ArrayException(std::to_string((_ULonglong)index));
	}	

	~TableOfSimptoms() { delete s; delete[] m_code; }

	int* getCodes() { return m_code; }
	Simptom& getSimptom() { return *s; }
};

std::ostream& operator << (std::ostream& out, TableOfSimptoms& ts) {
	out << "Таблица Симптомов: \n";

	for(int i = 0; i < ts.getSimptom().getLength(); i++) {
		out << "ID: " << ts[i] << "; Симптом: " << ts.getSimptom() << "\n";
	}
		
	return out;
}


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian"); // задаём русский текст
    
	Simptom s(16);

	TableOfSimptoms tbl(s);

	std::cout << tbl << "\n";

	getch();
	return 0;
}

