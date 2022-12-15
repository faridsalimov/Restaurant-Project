#pragma once

#include <iostream>
#include <Windows.h>
#include <fstream>

using namespace std;

void setColor(int fg, int bg) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, fg | (bg << 4));
}

void setAlert(string text, int color) {
	system("cls");
	setColor(color, 0);
	cout << "[!] ";
	setColor(15, 0);
	cout << text << "\n\n\a";
}

void writeLog(string type1, string type2, string text) {
	ofstream fs("logs.txt", ios::app);

	if (fs.is_open()) {
		if (type1 == "ingredient") {
			if (type2 == "add")
				fs << "[LOG] " << text << " adli ingredient elave olundu." << endl;
			else if (type2 == "delete")
				fs << "[LOG] " << text << " adli ingredient silindi." << endl;
		}

		else if (type1 == "yemek") {
			if (type2 == "add")
				fs << "[LOG] " << text << " adli yemek elave olundu." << endl;
			else if (type2 == "delete")
				fs << "[LOG] " << text << " adli yemek silindi." << endl;
		}

		else if (type1 == "menyu") {
			if (type2 == "add")
				fs << "[LOG] " << text << " adli menyu elave olundu." << endl;
			else if (type2 == "delete")
				fs << "[LOG] " << text << " adli menyu silindi." << endl;
		}
	}

	fs.close();
}

class Ingredient {
	string name;
	int capacity;

public:
	Ingredient() {
		name = "";
		capacity = 0;
	}

	Ingredient(string name, int capacity) {
		this->name = name;
		this->capacity = capacity;
	}

	string GetName() { return name; }
	int& GetCapacity() { return capacity; }

	Ingredient& operator-=(const int other) {
		this->capacity -= other;
		return *this;
	}
};

class Food {
	string name;
	int price;

public:
	Food() {
		name = "";
		price = 0;
	}

	Food(string name, int price) {
		this->name = name;
		this->price = price;
	}

	string GetName() { return name; }
	int GetPrice() { return price; }
};

class Menu {
	string name;
	int price;

public:
	Menu() {
		name = "";
		price = 0;
	}

	Menu(string name, int price) {
		this->name = name;
		this->price = price;
	}

	string GetName() { return name; }
	int GetPrice() { return price; }
};

bool loggedin = false;
int cashMoney = 0;

Ingredient** ingredients;
int sizei;

Food** foods;
int sizef;

Menu** menus;
int sizem;

void checkIngredients() {
	for (int i = 0; i < sizei; i++) {
		if (ingredients[i]->GetCapacity() <= 0) {
			Ingredient** temp = new Ingredient * [sizei + 1];

			for (int i = 0; i < sizei; i++) {
				temp[i] = ingredients[i];
			}

			delete[] ingredients;
			temp[sizei] = nullptr;
			ingredients = temp;
			temp = nullptr;
			sizei--;
		}
	}
}

void start();

class Admin {
	string username;
	string password;

public:
	Admin() {
		username = "";
		password = "";
	}

	Admin(string username, string password) {
		this->username = username;
		this->password = password;
	}

	void Panel() {
		while (true) {
			setColor(15, 0);
			cout << "======================" << endl;
			cout << "1. Ingredient Sehifesi" << endl;
			cout << "2. Yemek Sehifesi" << endl;
			cout << "3. Menyu Sehifesi" << endl;
			cout << "4. Kassadaki Pul" << endl;
			cout << "5. Hesabdan Cixis" << endl;
			cout << "6. Cixis" << endl;
			cout << "======================" << endl;
			cout << "SECIM: ";

			int select = 0;
			cin >> select;
			system("cls");

			if (select == 1) {
				setColor(15, 0);
				cout << "======================" << endl;
				cout << "1. Ingredientleri Goster" << endl;
				cout << "2. Ingredient Elave Et" << endl;
				cout << "3. Ingredient Sil" << endl;
				cout << "4. Geri" << endl;
				cout << "======================" << endl;
				cout << "SECIM: ";

				int select = 0;
				cin >> select;
				system("cls");

				if (select == 1) {
					if (sizei == 0)
						setAlert("Ingredient yoxdur.", 4);

					else {
						setAlert("Butun ingredientler listelendi:", 10);

						for (int i = 0; i < sizei; i++) {
							cout << i + 1 << ". " << ingredients[i]->GetName() << " - " << ingredients[i]->GetCapacity() << " qr\n";
						}

						cout << endl;
					}
				}

				else if (select == 2) {
					string name;
					cout << "Ingredient adini daxil edin: ";
					cin >> name;

					int capacity;
					cout << "Ingredient hecmini daxil edin: ";
					cin >> capacity;

					if (capacity <= 0)
						setAlert("Hecm 0-dan az ola bilmez.", 4);

					else {
						Ingredient** temp = new Ingredient * [sizei + 1];

						for (int i = 0; i < sizei; i++) {
							temp[i] = ingredients[i];
						}

						delete[] ingredients;
						temp[sizei] = new Ingredient(name, capacity);
						ingredients = temp;
						temp = nullptr;
						sizei++;

						writeLog("ingredient", "add", name);
						setAlert("Ingredient ugurla elave olundu.", 10);
					}
				}

				else if (select == 3) {
					if (sizei == 0)
						setAlert("Ingredient yoxdur.", 4);

					else {
						string name;
						cout << "Ingredient adini daxil edin: ";
						cin >> name;

						Ingredient** temp = new Ingredient * [sizei + 1];

						for (int i = 0; i < sizei; i++) {
							temp[i] = ingredients[i];
						}

						for (int i = 0; i < sizei; i++) {
							if (ingredients[i]->GetName() == name) {
								delete[] ingredients;
								temp[sizei] = nullptr;
								ingredients = temp;
								temp = nullptr;
								sizei--;

								writeLog("ingredient", "delete", name);
								setAlert("Ingredient ugurla silindi.", 10);
							}
						}
					}
				}

				else if (select == 4) {}

				else
					setAlert("Yanlis secim!", 4);
			}

			else if (select == 2) {
				setColor(15, 0);
				cout << "======================" << endl;
				cout << "1. Yemekleri Goster" << endl;
				cout << "2. Yemek Elave Et" << endl;
				cout << "3. Yemek Sil" << endl;
				cout << "4. Geri" << endl;
				cout << "======================" << endl;
				cout << "SECIM: ";

				int select = 0;
				cin >> select;
				system("cls");

				if (select == 1) {
					if (sizef == 0)
						setAlert("Yemek yoxdur.", 4);

					else {
						for (int i = 0; i < sizef; i++) {
							cout << i + 1 << ". Yemeyin Teferruatlari: \n" << "Ad: " << foods[i]->GetName() << "\nQiymet: " << foods[i]->GetPrice() << "$\nIngredientler: " << foods[i] << "\n\n";
						}
					}
				}

				else if (select == 2) {
					if (sizei == 0)
						setAlert("Evvelce ingredient elave edin, sonra yemeyi elave ede bilerseniz.", 4);

					else {
						bool selectIngPage = true;
						bool ingredientSelected = false;

						string name;
						cout << "Yemeyin adini daxil edin: ";
						cin >> name;

						int price;
						cout << "Yemeyin qiymetini daxil edin: ";
						cin >> price;

						if (price <= 0) {
							setAlert("Qiymet 0-dan az ola bilmez.", 4);
						}

						else {
							while (selectIngPage) {
								cout << "======================" << endl;
								cout << "1. Ingredient Sec" << endl;
								cout << "2. Bitti" << endl;
								cout << "======================" << endl;
								cout << "SECIM: ";

								int select = 0;
								cin >> select;
								system("cls");

								if (select == 1) {
									if (sizei == 0)
										setAlert("Ingredient yoxdur.", 4);

									else {
										cout << "Ingredient ID daxil edin.\n";

										for (int i = 0; i < sizei; i++) {
											cout << i + 1 << ". " << ingredients[i]->GetName() << " - " << ingredients[i]->GetCapacity() << " qr\n";
										}

										cout << "SECIM: ";
										int ingSelect = 0;
										cin >> ingSelect;

										if (ingSelect <= 0)
											setAlert("Bele bir ingredient yoxdur.", 4);

										else {
											if (ingSelect <= sizei) {
												system("cls");
												setColor(10, 0);
												cout << ingSelect << ". " << ingredients[ingSelect - 1]->GetName() << " - " << ingredients[ingSelect - 1]->GetCapacity() << " qr\n";
												setColor(15, 0);

												cout << "Ingredient hecmini daxil edin: ";
												int capacityInput = 0;
												cin >> capacityInput;

												if (ingredients[ingSelect - 1]->GetCapacity() >= capacityInput) {
													ingredients[ingSelect - 1]->GetCapacity() -= capacityInput;
													ingredientSelected = true;
													checkIngredients();
													setAlert("Yemeyin ingredienti ugurla elave edildi.", 10);
												}

												else
													setAlert("Bu sayida hecm yoxdur.", 4);
											}

											else
												setAlert("Bele bir ingredient yoxdur.", 4);
										}
									}
								}

								else if (select == 2) {
									if (ingredientSelected) {
										selectIngPage = 0;

										Food** temp = new Food * [sizef + 1];

										for (int i = 0; i < sizef; i++) {
											temp[i] = foods[i];
										}

										delete[] foods;
										temp[sizef] = new Food(name, price);
										foods = temp;
										temp = nullptr;
										sizef++;

										writeLog("yemek", "add", name);
										setAlert("Yemek ugurla elave olundu.", 10);
									}

									else
										setAlert("Evvelce ingredient secin.", 4);
								}

								else
									setAlert("Yanlis secim!", 4);
							}
						}
					}
				}

				else if (select == 3) {
					if (sizef == 0)
						setAlert("Yemek yoxdur.", 4);

					else {
						string name;
						cout << "Yemeyin adini daxil edin: ";
						cin >> name;

						Food** temp = new Food * [sizef + 1];

						for (int i = 0; i < sizef; i++) {
							temp[i] = foods[i];
						}

						for (int i = 0; i < sizef; i++) {
							if (foods[i]->GetName() == name) {
								delete[] foods;
								temp[sizef] = nullptr;
								foods = temp;
								temp = nullptr;
								sizef--;

								writeLog("yemek", "delete", name);
								setAlert("Yemek ugurla silindi.", 10);
							}
						}
					}
				}

				else if (select == 4) {}

				else
					setAlert("Yanlis secim!", 4);
			}

			else if (select == 3) {
				setColor(15, 0);
				cout << "======================" << endl;
				cout << "1. Menyulari Goster" << endl;
				cout << "2. Menyu Elave Et" << endl;
				cout << "3. Menyu Sil" << endl;
				cout << "4. Geri" << endl;
				cout << "======================" << endl;
				cout << "SECIM: ";

				int select = 0;
				cin >> select;
				system("cls");

				if (select == 1) {
					if (sizem == 0) {
						setAlert("Menu yoxdur.", 4);
					}

					else {
						for (int i = 0; i < sizem; i++) {
							cout << i + 1 << ". Menyunun Teferruatlari: \n";
							cout << "Ad: " << menus[i]->GetName() << "\nQiymet: " << menus[i]->GetPrice() << "$\nYemekler: " << menus[i] << "\n\n";
						}
					}
				}

				else if (select == 2) {
					if (sizei == 0)
						setAlert("Evvelce yemek elave edin, sonra menyuyu elave ede bilerseniz.", 4);

					else {
						bool selectFoodPage = true;
						bool foodSelected = false;

						string name;
						cout << "Menyu adini daxil edin: ";
						cin >> name;

						int price;
						cout << "Menyu qiymetini daxil edin: ";
						cin >> price;

						if (price <= 0) {
							setAlert("Qiymet 0-dan az ola bilmez.", 4);
						}

						else {
							while (selectFoodPage) {
								cout << "======================" << endl;
								cout << "1. Yemek Sec" << endl;
								cout << "2. Bitti" << endl;
								cout << "======================" << endl;
								cout << "SECIM: ";

								int select = 0;
								cin >> select;
								system("cls");

								if (select == 1) {
									cout << "Yemek ID daxil edin.\n";

									for (int i = 0; i < sizef; i++) {
										cout << i + 1 << ". Yemeyin Teferruatlari:\n";
										cout << "Ad: " << foods[i]->GetName() << "\nQiymet: " << foods[i]->GetPrice() << "$\nIngredientler: " << foods[i] << "\n\n";
									}

									cout << "SECIM: ";
									int menuSelect = 0;
									cin >> menuSelect;

									if (menuSelect <= 0)
										setAlert("Bele bir yemek yoxdur.", 4);

									else {
										if (menuSelect <= sizef) {
											foodSelected = true;
											setAlert("Yemek siyahiya ugurla elave olundu.", 10);
										}

										else
											setAlert("Bele bir yemek yoxdur.", 4);
									}
								}

								else if (select == 2) {
									if (foodSelected) {
										selectFoodPage = false;

										Menu** temp = new Menu * [sizem + 1];

										for (int i = 0; i < sizem; i++) {
											temp[i] = menus[i];
										}

										delete[] menus;
										temp[sizem] = new Menu(name, price);
										menus = temp;
										temp = nullptr;
										sizem++;

										writeLog("menyu", "add", name);
										setAlert("Menu ugurla elave olundu.", 10);
									}

									else
										setAlert("Evvelce yemek secin.", 4);
								}

								else
									setAlert("Yanlis secim!", 4);
							}
						}
					}
				}

				else if (select == 3) {
					if (sizem == 0)
						setAlert("Menu yoxdur.", 4);

					else {
						string name;
						cout << "Menu adini daxil edin: ";
						cin >> name;

						Menu** temp = new Menu * [sizem + 1];

						for (int i = 0; i < sizem; i++) {
							temp[i] = menus[i];
						}

						for (int i = 0; i < sizem; i++) {
							if (menus[i]->GetName() == name) {
								delete[] menus;
								temp[sizem] = nullptr;
								menus = temp;
								temp = nullptr;
								sizem--;

								writeLog("menyu", "delete", name);
								setAlert("Menu ugurla silindi.", 10);
							}
						}
					}
				}

				else if (select == 4) {}

				else
					setAlert("Yanlis secim.", 4);
			}

			else if (select == 4) {
				system("cls");
				setColor(10, 0);
				cout << "[!] ";
				setColor(15, 0);
				cout << "Kassada " << cashMoney << "$ miqdar pul var.\n\n";
				cout << "\a";
			}

			else if (select == 5) {
				system("cls");
				loggedin = false;
				start();
			}

			else if (select == 6) {
				system("cls");
				cout << "Elvida, " << username << "!" << endl;
				break;
			}

			else
				setAlert("Yanlis secim!", 4);
		}
	}

	bool Login(string username, string password) {
		if (username == this->username && password == this->password) {
			return true;
		}

		else {
			setAlert("Username veya Sifre yanlisdir!", 4);
			return false;
		}
	}
};

class User {
	string username;
	string password;

public:
	User() {
		username = "";
		password = "";
	}

	User(string username, string password) {
		this->username = username;
		this->password = password;
	}

	void Panel() {
		int total = 0;

		while (true) {
			setColor(15, 0);
			cout << "======================" << endl;
			cout << "1. Yemek Sifaris" << endl;
			cout << "2. Menyu Sifaris" << endl;
			cout << "3. Sebetim" << endl;
			cout << "4. Hesabdan Cixis" << endl;
			cout << "5. Cixis" << endl;
			cout << "======================" << endl;
			cout << "SECIM: ";

			int select = 0;
			cin >> select;
			system("cls");

			if (select == 1) {
				if (sizef <= 0)
					setAlert("Yemek yoxdur.", 4);

				else {
					for (int i = 0; i < sizef; i++) {
						cout << i + 1 << ". Yemeyin Teferruatlari:\n";
						cout << "Ad: " << foods[i]->GetName() << "\nQiymet: " << foods[i]->GetPrice() << "$\nIngredientler: " << foods[i] << "\n\n";
					}

					cout << "SECIM: ";
					int yemekSecim = 0;
					cin >> yemekSecim;

					if (yemekSecim > sizef)
						setAlert("Bele bir yemek yoxdur", 4);

					else {
						system("cls");
						cout << "Miqdar daxil edin: ";
						int miqdar = 0;
						cin >> miqdar;

						if (miqdar <= 0)
							setAlert("Miqdar 0-dan az ola bilmez.", 4);

						else {
							total += (foods[yemekSecim - 1]->GetPrice() * miqdar);
							setAlert("Yemek ugurla sebete elave olundu.", 10);
						}
					}
				}
			}

			else if (select == 2) {
				if (sizem <= 0)
					setAlert("Menyu yoxdur.", 4);

				else {
					for (int i = 0; i < sizem; i++) {
						cout << i + 1 << ". Menyunun Teferruatlari:\n";
						cout << "Ad: " << menus[i]->GetName() << "\nQiymet: " << menus[i]->GetPrice() << "$\nYemekler: " << menus[i] << "\n\n";
					}

					cout << "SECIM: ";
					int menuSecim = 0;
					cin >> menuSecim;

					if (menuSecim > sizem)
						setAlert("Bele bir menyu yoxdur", 4);

					else {
						system("cls");
						cout << "Miqdar daxil edin: ";
						int miqdar = 0;
						cin >> miqdar;

						if (miqdar <= 0)
							setAlert("Miqdar 0-dan az ola bilmez.", 4);

						else {
							total += (menus[menuSecim - 1]->GetPrice() * miqdar);
							setAlert("Menyu ugurla sebete elave olundu.", 10);
						}
					}
				}
			}

			else if (select == 3) {
				if (total <= 0)
					setAlert("Sebet bosdur, ilk once sifaris edin.", 4);

				else {
					system("cls");
					cout << ">> TOPLAM: " << total << "$\n";
					cout << ">> Sebetdekileri almaq isteyirsiz? (1-Beli, 0-Xeyr)\n";

					cout << "SECIM: ";
					int secim = 0;
					cin >> secim;

					if (secim == 0)
						system("cls");

					else if (secim == 1) {
						setAlert("Alisverisiniz ugurla basa catdi, bizi secdiyiniz ucun tesekkurler!", 10);
						cashMoney += total;
						total = 0;
					}

					else
						setAlert("Yanlis secim!", 4);
				}
			}

			else if (select == 4) {
				system("cls");
				loggedin = false;
				start();
			}

			else if (select == 5) {
				system("cls");
				cout << "Elvida, " << username << "!" << endl;
				break;
			}

			else
				setAlert("Yanlis secim!", 4);
		}
	}

	bool Login(string username, string password) {
		if (username == this->username && password == this->password)
			return true;

		else {
			setAlert("Username veya Sifre yanlisdir!", 4);
			return false;
		}
	}

	void Register(string username, string password) {
		this->username = username;
		this->password = password;
		setAlert("Hesabiniz ugurla yaradildi, indi ise login edin.", 10);
	}
};

void start() {
	system("title Restaurant Application");
	Admin admin("admin", "admin123");
	User user;

	while (!loggedin) {
		setColor(15, 0);
		cout << "======================" << endl;
		cout << "1. Admin" << endl;
		cout << "2. User" << endl;
		cout << "======================" << endl;
		cout << "SECIM: ";

		int select = 0;
		cin >> select;
		system("cls");

		if (select == 1) {
			string username;
			cout << "Username daxil edin: ";
			cin >> username;

			string password;
			cout << "Sifre daxil edin: ";
			cin >> password;

			if (admin.Login(username, password)) {
				loggedin = true;
				system("cls");
				admin.Panel();
			}
		}

		else if (select == 2) {
			cout << "======================" << endl;
			cout << "1. Login" << endl;
			cout << "2. Register" << endl;
			cout << "======================" << endl;
			cout << "SECIM: ";

			int select = 0;
			cin >> select;
			system("cls");

			if (select == 1) {
				string username;
				cout << "Username daxil edin: ";
				cin >> username;

				string password;
				cout << "Sifre daxil edin: ";
				cin >> password;

				if (user.Login(username, password)) {
					loggedin = true;
					system("cls");
					user.Panel();
				}
			}

			else if (select == 2) {
				string username;
				cout << "Username daxil edin: ";
				cin >> username;

				string password;
				cout << "Sifre daxil edin: ";
				cin >> password;

				user.Register(username, password);
			}

			else
				setAlert("Yanlis secim!", 4);
		}

		else
			setAlert("Yanlis secim!", 4);
	}
}