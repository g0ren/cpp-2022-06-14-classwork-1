#include <iostream>
#include <string>
using namespace std;

class Person {
public:
	int id;
	Person(int id) :
			id { id } {
	}
};

class SMSMemento {
	Person *from;
	Person *to;
	string text;
	SMSMemento(Person *from, Person *to, string text) :
			from { from }, to { to } {
		this->text = text;
	}
	friend class SMS;
};

class SMS {
	Person *from;
	Person *to;
	string text;
	SMSMemento *memento;
	void makeMemento() {
		this->memento = new SMSMemento(this->from, this->to, this->text);
	}
public:
	SMS(Person *from, Person *to, string text) :
			from { from }, to { to } {
		this->text = text;
	}
	void send() {
		cout << "From ID: " << this->from->id << endl;
		cout << "To ID: " << this->to->id << endl;
		cout << this->text << endl;
	}
	void edit() {
		this->makeMemento();
		cout << "Enter new text:" << endl;
		getline(cin, this->text);
	}
	void undoEdit() {
		if (this->memento) {
			this->from = this->memento->from;
			this->to = this->memento->to;
			this->text = this->memento->text;
		}
	}
};

int main() {
	Person *p1 = new Person(rand());
	Person *p2 = new Person(rand());
	SMS sms(p1, p2, "Hello");
	sms.send();
	sms.edit();
	sms.send();
	sms.undoEdit();
	sms.send();

	return 0;
}
