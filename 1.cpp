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


class Table : public Simptom {
private:
	int* m_code;
	int m_length;
	int m_maxLength;
	Simptom** s;

public:
	Table() : Simptom() {
		m_code = NULL;
		s = NULL;
		m_length = 0;
		m_maxLength = 10;
	}

	Table(int length) : m_length(length) {
		if(m_length > 0) {
			m_maxLength = m_length * 2;
			if(m_length <= 16) {
				s = new Simptom*[m_length];
				m_code = new int[m_length];
				for(int i = 0; i < m_length; i++) {
					m_code[i] = i;
					s[i] = new Simptom(simptomi[i], m_code[i]);
				}
			} else {
				int m_size = 16;
				s = new Simptom*[m_length];
				m_code = new int[m_length];
				for(int i = 0; i < m_size; i++) {
					m_code[i] = i;
					s[i] = new Simptom(simptomi[i], m_code[i]);
				}
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
		s = new Simptom*[m_length];
		for(int i = 0; i < m_length; i++) {
			s[i] = new Simptom(o[i]);
			m_code[i] = o.m_code[i];
		}
	}


	Table* addSimptom(std::string str) {
		if(m_length > m_maxLength) { increaseSizeOfArray(); }
		Simptom* addS = new Simptom(str);

		s[m_length] = addS;
		m_code[m_length] = m_length;
		m_length++;

		sortCodesByInsertionMethod();
		sortSimptomBySelectionMethod();

		return this;
	}

	Table* addSimptom(Simptom* simp) {
		if(m_length > m_maxLength) { increaseSizeOfArray(); }

		s[m_length] = simp;
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
		Simptom* x;
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


	void deleteSimptom() {
		deleteSimptom(1);
	}

	void deleteSimptom(const int num) {
		if(num > 0 && num <= m_length) {
			Simptom* temp = s[num - 1];
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


	~Table() { for(int i = 0; i < m_length; i++) delete s[i]; delete[] s; delete[] m_code; }

	int* getCodes() { return m_code; }

	int& getLength() { return m_length; }

	int& getMaxLength() { return m_maxLength; }
	
	Simptom& operator[] (const int index) { 
		if(index >= 0 && index < m_length) {
			return *s[index];
		}

		throw ArrayException(std::to_string((_ULonglong)index));
	}

	void increaseSizeOfArray() {
		Simptom** temp = new Simptom*[m_length];
		for(int i = 0; i < m_length; i++) {
			temp[i] = s[i];
		}
		delete[] s;
		s = new Simptom*[m_maxLength * 2];
		for(int i = 0; i < m_length; i++) {
			s[i] = temp[i];
		}
		delete[] temp;
		
		m_maxLength *= 2;
	}

	void reduceSizeOfArray() {
		Simptom** temp = new Simptom*[m_length];
		for(int i = 0; i < m_length; i++) {
			temp[i] = s[i];
		}
		delete[] s;
		s = new Simptom*[m_maxLength / 2];
		for(int i = 0; i < m_length; i++) {
			s[i] = temp[i];
		}
		delete[] temp;

		m_maxLength /= 2;
	}


};

std::ostream& operator << (std::ostream& out, Table& ts) {
	for(int i = 0; i < ts.getLength(); i++) {
		out << "Код: " << ts.getCodes()[i] << ", Симптом: " << ts[i] << "\n";
	}
		
	return out;
}


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian"); // задаём русский текст

	try {
		Table tbl(16);

		std::cout << tbl << "\n";

		getch();
	
	} catch(ArrayException& e) {
		std::cerr << "Overflow, index " << e.what() << "\n";
	} catch(std::exception& e) {
		std::cerr << e.what() << "\n";
	}
	

	
	return 0;
}


// поработать с кодом, чтобы были отсортированы при удалении симптома(вторая лаба у поляка) (золотое сечение, дихотомия)

