#include "head.h"
int getPrio(char op) {
	switch (op)
	{
	case'@':return 0;
	case'(':return 1;
	case'+':return 2;
	case'-':return 2;
	case'*':return 3;
	case'/':return 3;
	case')':return 4;
	default:
		return -1;
	}
}
int getVal(char op, int right, int left) {
	switch (op)
	{
	case'+':return left + right; 
	case'-':return left - right;
	case'*':return left*right;
	case'/':return left / right;
	}
}
double getNumber(char*& arr) {
	bool isNeg = false;
	double sum[20] = { 0 };
	int i = 0;
	double result = 0;
	//judge whether the number is negative
	if (*arr == '#') {
		isNeg = true;
		arr++;
	}
	
	while (*arr != ' '&&*arr!='.') {
		sum[i] = *arr - 48;
		i++;
		arr++;
	}
	int k = i - 1;
	for (int j = 0; j < i; j++, k--) {
		result += (sum[j] * pow(10, k));
	}
	
	//if the number is float,get the value of decimal
	if (*arr == '.') {
		arr++;
		for (int n = 0; n < 20; n++) {
			sum[n] = 0;
		}
		i = 0;
		while (*arr != ' ') {
			sum[i] = *arr - 48;
			i++;
			arr++;
		}
		for (int m = 0; m < i; m++) {
			result += (sum[m] / pow(10, m + 1));
		}
	}

	if (isNeg) return -result;
	else return result;
}
void calInfixExp(string expression) {
	const char* p = expression.c_str();
	LStack<char> optr;
	LStack<int> opnd;
	optr.push('#');
	for (int i = 0; i < expression.length(); i++) {
		if (isdigit(p[i])) {
			opnd.push(p[i]-48);
		}
		else {
			if (p[i] == '(') {
				optr.push(p[i]);
			}
			else if (p[i] == ')') {
				while (optr.topValue() != '(') {
					opnd.push(getVal(optr.pop(),opnd.pop(),opnd.pop()));
				}
				optr.pop();
			}
			else if (getPrio(p[i]) > getPrio(optr.topValue())) {
				optr.push(p[i]);
			}
			else if (getPrio(p[i]) <= getPrio(optr.topValue())) {
				opnd.push(getVal(optr.pop(), opnd.pop(), opnd.pop()));
				optr.push(p[i]);
			}
		}
	}
	while (optr.topValue()!='#') {
		opnd.push(getVal(optr.pop(), opnd.pop(), opnd.pop()));
	}
	cout << "the result is "<<opnd.topValue() << endl;
}
string infixToPostfix(string expression) {
	const char*p = expression.c_str();
	char tar[50] = {0};
	int cnt = 0;
	LStack<char> optr;
	optr.push('#');
	for (int i = 0; i < expression.length(); i++) {
		if (isdigit(p[i])) {
			tar[cnt++] = p[i];
		}
		else {
			if (p[i] == '(') {
				optr.push(p[i]);
			}
			else if (p[i] == ')') {
				while (optr.topValue() != '(') {
					tar[cnt++] = optr.pop();
				}
				optr.pop();
			}
			else if (getPrio(p[i]) > getPrio(optr.topValue())) {
				optr.push(p[i]);
			}
			else if (getPrio(p[i]) <= getPrio(optr.topValue())) {
				tar[cnt++] = optr.pop();
				optr.push(p[i]);
			}
		}
	}
	while (optr.topValue() != '#') {
		tar[cnt++] = optr.pop();
	}
	tar[cnt] = '\0';
	return string(tar);
}
string infixToPostfixBeta(string expression) {
	char *middle = new char [30];
	char *back = new char[30];
	char *newBack = back;
	middle = const_cast<char*>(expression.c_str());
	*back = 0;
	LStack<char> optr;
	optr.push('@');
	while (*middle) {
		if (isdigit(*middle) || *middle == '.') {
			*back = *middle;
			back++;
			middle++;
		}
		else {
			if (*back) {
				if (isdigit(*(back - 1))) {
					*back = ' ';
					back++;
				}
			}
			if ((*middle == '-' && !*back)||(*middle == '-' && !isdigit(*(middle-1))&&*(middle-1)!=')')) {
				*back = '#';
				back++;
				middle++;
				continue;
			}
			if (*middle == ')') {
				while (optr.topValue() != '(') {
					*back = optr.pop();
					back++;
					*back = ' ';
					back++;
				}
				char temp = optr.pop();
				middle++;
			}
			else if (*middle == '(') {
				optr.push(*middle);
				middle++;
			}
			else if (getPrio(*middle) > getPrio(optr.topValue())) {
				optr.push(*middle);
				middle++;
			}
			else if (getPrio(*middle) <= getPrio(optr.topValue())) {
				*back = optr.pop();
				optr.push(*middle);
				back++;
				middle++;
				*back = ' ';
				back++;
			}
		}
	}
	while (optr.topValue()!='@') {
		*back = ' ';
		back++;
		*back = optr.pop();
		back++;
	}
	*back = '\0';
	cout << "back expression is "<< newBack << endl;
	return string(newBack);
}
void calcPostfixExp(string expression) {
	cout << "back expression is " << expression << endl;
	const char *p = expression.c_str();
	LStack<int> opnd;
	for (int i = 0; i < expression.length(); i++) {
		if (isdigit(p[i])) {
			int val = p[i]-'0';
			int cnt = 1;
			opnd.push(val);
		}
		else {
			opnd.push(getVal(p[i],opnd.pop(),opnd.pop()));
		}
	}
	cout << "the result is "<<opnd.topValue() << endl;
}
void calcPostfixExpBeta(string expression) {
	char *back = new char[30];
	back = const_cast<char*>(expression.c_str());
	LStack<double> opnd;
	while (*back) {
		if (isdigit(*back)||*back=='#') {
			opnd.push(getNumber(back));
		}
		else if (*back==' ') {
			back++;
		}
		else {
			double r = opnd.pop();
			double l = opnd.pop();
			switch (*back)
			{
			case'+':opnd.push(l + r); break;
			case'-':opnd.push(l - r); break;
			case'*':opnd.push(l*r); break;
			case'/':opnd.push(l / r); break;
			default:
				break;
			}
			back++;
		}
	}
	while (opnd.length() >= 2) {
		double r = opnd.pop();
		double l = opnd.pop();
		switch (*back)
		{
		case'+':opnd.push(l + r); break;
		case'-':opnd.push(l - r); break;
		case'*':opnd.push(l*r); break;
		case'/':opnd.push(l / r); break;
		default:
			break;
		}
	}
	cout << "the result is "<< opnd.topValue() << endl;
}
int main() {
	string expression;
	int option = -1;
	while (1) {
		try {
			cout << "Welcome!" << endl;
			cout << "0.exit" << endl;
			cout << "1.calculate by mid expression" << endl;
			cout << "2.calculate by back expression" << endl;
			char temp;
			cin >> temp;
			if (isdigit(temp))
			{
				option = temp-'0';
			}
			if (option >= 0 && option <= 2) {
				switch (option) {
				case 1:
					cout << "please input a mid expression" << endl;
					cin >> expression;
					calInfixExp(expression);
					break;
				case 2:
					cout << "please input a mid expression" << endl;
					cin >> expression;
					calcPostfixExpBeta(infixToPostfixBeta(expression));
					break;
				case 0:
					exit(-1);
				}
			}
			else {
				throw "valid value of option";
			}
			option = -1;
		}
		catch (char *str) {
			cout << str << endl;
		}
		catch (exception &e) {
			cout << e.what() << endl;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
