/*
	"factory method" design pattern 

		Factory Method is a creational design pattern 
		that provides an interface for creating objects in a superclass, 
		but allows subclasses to alter the type of objects that will be created.
*/


#include<iostream>
#include<string>
class Button {      //button hierarchy is button ui family
public:             //we can have checkbox hierarchy, dropdown hierarchy 
	virtual ~Button() {}
	virtual void render() const = 0;
	virtual void onClick() const = 0;
};
class HtmlButton : public Button {
public:
	void render() const override {
		std::cout << "Html Button is diplayed.\n";
	}
	void onClick() const override {
		std::cout << "Html Button is clicked.\n";
	}
};
class WinButton : public Button {
public:
	void render() const override {
		std::cout << "Windows Button is diplayed.\n";
	}
	void onClick() const override {
		std::cout << "Windows Button is clicked.\n";
	}
};
class MyDialog {

public:
	virtual ~MyDialog() {};
	virtual Button* CreateButton() const = 0;


	Button* render() const {
		Button* btn = this->CreateButton();

		btn->render();

		return btn;
	}
};

class HtmlDialog : public MyDialog { //factory for html uis such as button, checkbox, dropdowns
public:
	Button* CreateButton() const override {
		return new HtmlButton();
	}
};
class WinDialog : public MyDialog { //factory for windows uis such as button, checkbox, dropdowns
public:
	Button* CreateButton() const override {
		return new WinButton();
	}
};

int main() {
	int menu;
	std::cout << "Chioice(1-HTML, 2-Windows):"; std::cin >> menu;
	MyDialog* dlgAddr = nullptr;

	if (1 == menu) {
		std::cout << "Web App: Launched.\n";
		dlgAddr = new HtmlDialog();
	}
	else {
		std::cout << "Desktop App: Lanuched.\n";
		dlgAddr = new WinDialog();
	}

	Button *btnAddr = dlgAddr->render();
	btnAddr->onClick();
	
	std::cout << std::endl;
   
    delete btnAddr;
	delete dlgAddr;

	return 0;
}