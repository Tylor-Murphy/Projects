#include "DLL.h"

void test_add_back() {
	vector<Node> v = { Node("one", 1), Node("two", 2) };
	auto list = DLL(v);
	cout << "My result: " << list << '\n';
	cout << "Expected:  " << Node("one", 1) << ", " << Node("two", 2) << '\n';
}

void test_add_front() {
	vector<Node> v = { Node("one", 1), Node("two", 2) };
	auto list = DLL(v);
	list.add_front("zero", 0);
	cout << "\nMy result: " << list << '\n';
	cout << "Expected:  " << Node("zero", 0) << ", " << Node("one", 1) << ", " << Node("two", 2) << '\n';
}

void test_add_after() {
	vector<Node> v = { Node("one", 1), Node("two", 2) };
	auto list = DLL(v);
	list.add_after("one", "middle", 0);
	cout << "\nMy result: " << list << '\n';
	cout << "Expected:  " << Node("one", 1) << ", " << Node("middle", 0) << ", " << Node("two", 2) << '\n';
}

void test_remove_front() {
	vector<Node> v = { Node("one", 1), Node("two", 2) };
	auto list = DLL(v);
	list.remove_front();
	cout << "\nMy result: " << list << '\n';
	cout << "Expected:  " << Node("two", 2) << '\n';
}

void test_remove_back() {
	vector<Node> v = { Node("one", 1), Node("two", 2) };
	auto list = DLL(v);
	list.remove_back();
	cout << "\nMy result: " << list << '\n';
	cout << "Expected:  " << Node("one", 1) << '\n';
}

void test_remove_key() {
	vector<Node> v = { Node("one", 1), Node("two", 2), Node("three", 3) };
	auto list = DLL(v);
	list.remove_key("two");
	cout << "\nMy result: " << list << '\n';
	cout << "Expected:  " << Node("one", 1) << ", " << Node("three", 3) << '\n';
}

void test_search() {
	vector<Node> v = { Node("one", 1), Node("two", 2), Node("three", 3) };
	auto list = DLL(v);
	auto result = list.search("two");
	cout << "\nMy result: " << result << '\n';
	cout << "Expected:  " << Node("two", 2) << '\n';
}

void test_update_value() {
	vector<Node> v = { Node("one", 1), Node("two", 2), Node("three", 3) };
	auto list = DLL(v);
	list.update_value("two", 22);
	cout << "\nMy result: " << list << '\n';
	cout << "Expected:  " << Node("one", 1) << ", " << Node("two", 22) << ", " << Node("three", 3) << '\n';
}

int main() {
	// test_add_back();
	// test_add_front();
	// test_add_after();
	// test_remove_front();
	// test_remove_back();
	// test_remove_key();
	// test_search();
	// test_update_value();
	return 0;
}
