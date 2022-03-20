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
	int m_code;

public:
	Simptom(std::string name = "", int code = 0) : m_name(name), m_code(code) {
	}

	Simptom(Simptom& o) {
		m_name = o.m_name;
		m_code = o.m_code;
	}

	virtual ~Simptom() {}

	Simptom& operator = (Simptom& s) {
		if(this == &s) return *this;

		m_name = s.m_name;
		m_code = s.m_code;
		
		return *this;
	} // протестить, попробовать убрать этот метод

	Simptom& operator = (std::string name) {
		m_name = name;

		return *this;
	}

	std::string getSimptom() { return m_name; }
	int getCode() { return m_code; }
};

std::ostream& operator << (std::ostream& out, Simptom& s) {
	out << s.getSimptom() << "\n";
	
	return out;
}

std::ostream& operator << (std::ostream& out, Simptom* s) {
	out << s->getSimptom() << "\n";
	
	return out;
}


class Diagnoz {
private:
	std::string m_name;
	int m_code;

public:
	Diagnoz(std::string name = "", int code = 0) : m_name(name), m_code(code) {
	}

	Diagnoz(Diagnoz& o) {
		m_name = o.m_name;
		m_code = o.m_code;
	}

	virtual ~Diagnoz() {}

	Diagnoz& operator = (Diagnoz& s) {
		if(this == &s) return *this;

		m_name = s.m_name;
		m_code = s.m_code;
		
		return *this;
	} // протестить, попробовать убрать этот метод

	Diagnoz& operator = (std::string name) {
		m_name = name;

		return *this;
	}

	std::string getDiagnoz() { return m_name; }
	int getCode() { return m_code; }
};


std::ostream& operator << (std::ostream& out, Diagnoz& s) {
	out << s.getDiagnoz() << "\n";
	
	return out;
}

std::ostream& operator << (std::ostream& out, Diagnoz* s) {
	out << s->getDiagnoz() << "\n";
	
	return out;
}


template<typename T>
class Table {
private:
	int* m_code;
	int m_length;
	int m_maxLength;
	T** s;

public:
	Table() {
		m_code = NULL;
		s = NULL;
		m_length = 0;
		m_maxLength = 10;
	}

	Table(std::string* arr, int length) : m_length(length) {
		if(m_length > 0) {
			m_maxLength = m_length * 2;
			s = new T*[m_length];
			m_code = new int[m_length];
			for(int i = 0; i < m_length; i++) {
				m_code[i] = i;
				s[i] = new T(arr[i], m_code[i]);
			}
		} else {
			m_code = NULL;
			m_length = 0;
			m_maxLength = 10;
			s = NULL;
		}
	}

	Table(Table& o) {
		m_length = o.m_length;
		m_maxLength = o.m_maxLength;
		m_code = new int[m_length];
		s = new T*[m_length];
		for(int i = 0; i < m_length; i++) {
			s[i] = new T(o[i]);
			m_code[i] = o.m_code[i];
		}
	}


	Table* addItem(std::string str) {
		if(m_length > m_maxLength) { increaseSizeOfArray(); }
		T* add = new T(str);

		s[m_length] = add;
		m_code[m_length] = m_length;
		m_length++;

		sortCodesByInsertionMethod();
		sortSimptomBySelectionMethod();

		return this;
	}

	Table* addItem(T* t) {
		if(m_length > m_maxLength) { increaseSizeOfArray(); }

		s[m_length] = t;
		m_code[m_length] = m_length;
		m_length++;

		sortCodesByInsertionMethod();
		sortSimptomBySelectionMethod();

		return this;
	}

	void sortCodesByInsertionMethod() {
		int x;
		for(int i = 1; i < m_length; i++) {
			x = m_code[i];
			int j = i - 1;
			while(j >= 0 && x < m_code[j]) {
				m_code[j + 1] = m_code[j];
				j--;
			}
			m_code[j + 1] = x;
		}
	}

	void sortSimptomBySelectionMethod() {
		int k;
		T* x;
		for(int i = 0; i < m_length; i++) {
			k = i;
			x = s[i];
			for(int j = i + 1; j < m_length; j++) {
				if(s[j] < x) {
					k = j;
					x = s[j];
				}
			}

			s[k] = s[i];
			s[i] = x;
		}
	}


	void deleteItem() {
		deleteItem(1);
	}

	void deleteItem(const int num) {
		if(num > 0 && num <= m_length) {
			T* temp = s[num - 1];
			delete s[num - 1];
			int code = m_code[num - 1];
			for(int i = num - 1; i < m_length - 1; i++) {
				s[i] = s[i + 1];
				m_code[i] = m_code[i + 1];
			}
			s[m_length - 1] = temp;
			m_code[m_length - 1] = code;
			m_length--;

			sortCodesByInsertionMethod();
			sortSimptomBySelectionMethod();
			
			if((m_length < m_maxLength / 2) && (m_maxLength > 1)) {
				reduceSizeOfArray();
			} 
		} else {
			throw ArrayException(std::to_string((_ULonglong)num - 1));
		}
	}


	virtual ~Table() { for(int i = 0; i < m_length; i++) delete s[i]; delete[] s; delete[] m_code; }

	int* getCodes() { return m_code; }

	int& getLength() { return m_length; }

	int& getMaxLength() { return m_maxLength; }
	
	T& operator[] (const int index) { 
		if(index >= 0 && index < m_length) {
			return *s[index];
		}

		throw ArrayException(std::to_string((_ULonglong)index));
	}

	void increaseSizeOfArray() {
		T** temp = new T*[m_length];
		for(int i = 0; i < m_length; i++) {
			temp[i] = s[i];
		}
		delete[] s;
		s = new T*[m_maxLength * 2];
		for(int i = 0; i < m_length; i++) {
			s[i] = temp[i];
		}
		delete[] temp;
		
		m_maxLength *= 2;
	}

	void reduceSizeOfArray() {
		T** temp = new T*[m_length];
		for(int i = 0; i < m_length; i++) {
			temp[i] = s[i];
		}
		delete[] s;
		s = new T*[m_maxLength / 2];
		for(int i = 0; i < m_length; i++) {
			s[i] = temp[i];
		}
		delete[] temp;

		m_maxLength /= 2;
	}


};

std::ostream& operator << (std::ostream& out, Table<Simptom>& ts) {
	for(int i = 0; i < ts.getLength(); i++) {
		out << "Код: " << ts.getCodes()[i] << ", Симптом: " << ts[i] << "\n";
	}
		
	return out;
}

std::ostream& operator << (std::ostream& out, Table<Diagnoz>& ts) {
	for(int i = 0; i < ts.getLength(); i++) {
		out << "Код: " << ts.getCodes()[i] << ", Диагноз: " << ts[i] << "\n";
	}
		
	return out;
}

template<typename T1, typename T2>
class TableMatches {
	private:
	int** m_codes;
	int m_rows;
	int m_cols;

public:
	TableMatches(Table<T1>& t1, Table<T2>& t2) {
		m_rows = t1.getLength();
		m_cols = t2.getLength();
		m_codes = new int*[m_rows];
		for(int i = 0; i < t1.getLength(); i++) {
			m_codes[i] = new int[m_cols];
			for(int j = 0; j < t2.getLength(); j++) {
				m_codes[i][j] = t1[i].getCode();
			}
		}
	}

	int** getCodes() { return m_codes; }
	int getLengthSimptom() { return m_rows; }
	int getLengthDiagnoz() { return m_cols; }

	~TableMatches() {
		delete[] m_codes; 
	}
};


std::ostream& operator << (std::ostream& out, TableMatches<Simptom, Diagnoz>& tblM) {
	for(int i = 0; i < tblM.getLengthSimptom(); i++) {
		for(int j = 0; j < tblM.getLengthDiagnoz(); j++) {
			out << tblM.getCodes()[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return out;
}




int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian"); // задаём русский текст

	try {
		Table<Simptom> tblS(simptomi, 16);
		Table<Diagnoz> tblD(diagnoz, 4);

		std::cout << "Таблица Симптомов: \n\n" << tblS << "\n";
		std::cout << "Таблица Диагнозов: \n\n" << tblD << "\n";

		TableMatches<Simptom, Diagnoz> tblMatches(tblS, tblD);

		std::cout << tblMatches;

		getch();
	
	} catch(ArrayException& e) {
		std::cerr << "Overflow, index " << e.what() << "\n";
	} catch(std::exception& e) {
		std::cerr << e.what() << "\n";
	}
	

	
	return 0;
}


// поработать с кодом, чтобы были отсортированы при удалении симптома(вторая лаба у поляка) (золотое сечение, дихотомия)

