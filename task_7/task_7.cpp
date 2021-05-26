#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

enum color { red, blue, black };

struct Item {
	Item() {

	}
	Item(int id) {
		this->id = id;
	}
	~Item() {}
	int id;
	union {
		struct {
			char title[30];
			int isbn;
			int pages;
		} book;
		struct {
			int rigidity;
			color color;
		} pencil;
	};
};

struct List {
	List() {
	}
	List(Item* data) {
		this->data = data;
	}
	~List() {}
	Item* data;
	List* next = nullptr;
};

void print(Item* item, int nb) {
	if (item->id == 0) {
		std::cout << std::setw(86) << std::left << std::setfill('_') << "_" << std::endl;
		std::cout << std::setfill(' ') << "| " << std::setw(5) << "#" << " | " << std::setw(50) << "TITLE" << " | " << std::setw(13) << "ISBN" << " | " << std::setw(5) << "Pages" << " |" << std::endl;
		std::cout << std::setfill(' ') << "| " << std::setw(5) << nb << " | " << std::setw(50) << item->book.title << " | " << std::setw(13) << item->book.isbn << " | " << std::setw(5) << item->book.pages << " |" << std::endl;
		std::cout << std::setfill('_') << std::setw(86) << std::setfill('_') << "_" << std::endl;
	}
	else if (item->id == 1) {
		std::string color;
		switch (item->pencil.color)
		{
		case red:
			color = "red";
			break;
		case blue:
			color = "blue";
			break;
		case black:
			color = "black";
			break;
		default:
			color = "unknown";
			break;
		}
		std::cout << std::setw(33) << std::left << std::setfill('_') << "_" << std::endl;
		std::cout << std::setfill(' ') << "| " << std::setw(5) << "#" << " | " << std::setw(8) << "Rigidity" << " | " << std::setw(10) << "Color" << " |" << std::endl;
		std::cout << std::setfill(' ') << "| " << std::setw(5) << nb << " | " << std::setw(8) << item->pencil.rigidity << " | " << std::setw(10) << color << " |" << std::endl;
		std::cout << std::setw(33) << std::left << std::setfill('_') << "_" << std::endl;
	}
}

void delete_item(List** head, int* size, int idx) {
	List* curr = *head;
	if (*head == nullptr) {
		return;
	}

	if (idx == 0) {
		*head = curr->next;
		delete curr;
		(*size)--;
		return;
	}

	for (int i = 0; curr != nullptr && i < idx - 1; i++) {
		curr = curr->next;
	}
		

	if (curr == nullptr || curr->next == nullptr) {
		(*size)--;
		return;
	}
	List* next = curr->next->next;
	delete curr->next;
	curr->next = next;
	(*size)--;
}

Item* create_new_item() {
	int id;
	std::cout << "Enter the item type (0 for books, 1 for pencils): ";
	std::cin >> id;
	Item* new_item = new Item(id);

	std::string color_s;
	if (new_item->id == 0) {
		std::cout << "Enter title, ISBN and number of pages of book: ";
		std::cin >> new_item->book.title >> new_item->book.isbn >> new_item->book.pages;
	}
	else if (new_item->id == 1) {
		std::cout << "Enter rigidity and color of pencil: ";
		std::cin >> new_item->pencil.rigidity >> color_s;
		if (color_s == "red") {
			new_item->pencil.color = red;
		}
		else if (color_s == "blue") {
			new_item->pencil.color = blue;
		}
		else if (color_s == "black") {
			new_item->pencil.color = black;
		}
	}
	return new_item;
}


void controller() {
	std::string command;
	bool flag = 1;

	List* head = nullptr;
	List* curr = nullptr;
	int size = 0;

	while (flag) {
		std::cout << "Enter command (SELECT, INSERT, DELETE, EXIT): ";
		std::cin >> command;
		if (command == "SELECT") {
			std::string filter;
			int id = -2;
			int counter = 0;
			std::cout << "Which elements SELECT (ALL or by ID)? ";
			std::cin >> filter;
			if (filter == "ALL") {
				id = -1;
			}
			else if (filter == "ID") {
				std::cout << "Enter ID: ";
				std::cin >> id;
			}
			if (id != -2) {
				curr = head;
				while (curr != nullptr) {
					if ((curr->data->id == id) || (id == -1)) {
						print(curr->data, counter);
						counter++;
					}
					curr = curr->next;
				}
			}
		}
		else if (command == "INSERT") {
			if (size > 0) {
				curr = head;
				while (curr->next != nullptr) {
					curr = curr->next;
				}
				curr->next = new List(create_new_item());
				size++;
			}
			else {
				head = new List(create_new_item());
				size++;
			}
		}
		else if (command == "DELETE") {
			int idx;
			std::cout << "Enter index: ";
			std::cin >> idx;
			if ((idx >= 0) && (idx < size)) {
				delete_item(&head, &size, idx);
			}
		}
		else if (command == "EXIT") {
			flag = 0;
		}
		else {
			std::cout << "Unknown command!" << std::endl;
		}
	}
}



int main()
{
	controller();
}

