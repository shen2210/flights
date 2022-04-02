#include<iostream>
#include<string>
#include<iomanip>
#define MAX 100
using namespace std;

struct INFO_FLIGHT {
	string code;
	string fullname;
	string date;
	string time;
	string departure;
	string destination;
};

typedef INFO_FLIGHT flight;

void menu();
void Title();
void Press();
void setInfoFlight(flight&);
void setInfoListFlights(flight*&,int);
void showInfoFlight(flight);
void showInfoListFlights(flight*,int);
void deleteAFlight(flight*,int&,string);
void deleteByPosition(flight*,int&,int);
void addAFlight(flight*,int&);
int getYear(string);
int getMonth(string);
int getDay(string);
void swap(flight&, flight&);
void sortFlightsByYear(flight*, int);
void searchFlightsByDate(flight*, int , string);
void searchFlightsByCode(flight*, int , string);
void searchFlightsInTimePeriod(flight*, int , string, string);
void searchFightsByChar(flight*, int , string);

int main() {
	flight* inf;
	inf = new INFO_FLIGHT[MAX];
	int choice, amount = 0;
	string id, day, start, end, str;
	
	while (1) {
		menu();
		cout << "Enter your choice: "; cin >> choice;
		switch (choice) {
			case 1 :
				cout << "Enter the number of flights: "; cin >> amount;
				setInfoListFlights(inf,amount);
				Press();
				break;
			case 2:
				cout << "\n" << setw(70) << "THE LIST OF FLIGHTS\n";
				Title();
				showInfoListFlights(inf,amount);
				Press();
				break;
			case 3:
				cin.ignore();
				cout << "Enter the flight code to delete : "; getline(cin, id);
				deleteAFlight(inf,amount,id);
				Press();
				break;
			case 4:
				cin.ignore();
				addAFlight(inf,amount);
				Press();
				break;
			case 5:
				sortFlightsByYear(inf, amount);
				Press();
				cout << "\n" << setw(70) << "THE LIST OF FLIGHTS IS SORTED\n";
				Title();
				showInfoListFlights(inf, amount);
				Press();
				break;
			case 6:
				cin.ignore();
				cout << "Enter the flight date to search: "; getline(cin,day);
				searchFlightsByDate(inf, amount, day);
				Press();
				break;
			case 7:
				cin.ignore();
				cout << "Enter the flight code to search : "; getline(cin, id);
				searchFlightsByCode(inf, amount, id);
				Press();
				break;
			case 8:
				cin.ignore();
				cout << "Enter from : "; getline(cin, start);
				cout << "Enter to : "; getline(cin, end);
				searchFlightsInTimePeriod(inf, amount, start, end);
				Press();
				break;
			case 9:
				cin.ignore();
				cout << "Enter the string you want to search : "; getline(cin, str);
				searchFightsByChar(inf, amount, str);
				Press();
				break;
			case 0:
				delete[] inf;
				return 0;
		}
	}
}

void menu() {
	cout << "\t" << "--------------------------------MENU--------------------------------\n";
	cout << "\t" << "| 1. Nhap danh sach thong tin cac chuyen bay\n";
	cout << "\t" << "| 2. Xuat danh sach thong tin cac chuyen bay\n";
	cout << "\t" << "| 3. Xoa chuyen bay co ma chuyen bay bat ky\n";
	cout << "\t" << "| 4. Them chuyen bay moi vao danh sach\n";
	cout << "\t" << "| 5. Sap xep danh sach chuyen bay tang dan theo nam ba\n";
	cout << "\t" << "| 6. Tim kiem cac chuyen bay co ngay bat ky\n";
	cout << "\t" << "| 7. Tim kiem cac chuyen bay co ma chuyen bay bat ky\n";
	cout << "\t" << "| 8. Tim kiem cac chuyen bay trong khoang thoi gian (X,Y) cho truoc\n";
	cout << "\t" << "| 9. Tim kiem thong tin chuyen bay co ho ten hanh khach co chu cai \n";
	cout<< "\t" <<"| trong ho ten trung vs xau x can tim kiem\n";
	cout << "\t" << "| 0. Thoat chuong trinh\n";
	cout << "\t" << "--------------------------------------------------------------------\n";
}

void Title() {
	cout << setw(10) << "CODE" << setw(30) << "CUSTOMER'S NAME" << setw(20)
		<< "DATE" << setw(15) << "TIME" << setw(15) << "DEPARTURE" << setw(20) << "DESTINATION" << endl;
}

//Nhập thông tin 1 chuyến bay
void setInfoFlight(flight& info) {
	while (1) {
		cout << "Enter flight code : "; getline(cin, info.code);
		if (info.code.size() > 5) {
			cout << "Flight code contains up to 5 characters\n";
		}
		else break;
	}

	while (1) {
		cout << "Enter customer name : "; getline(cin, info.fullname);
		if (info.fullname.size() > 30) {
			cout << "Customer name contains up to 30 characters\n";
		}
		else break;
	}

	int c = 0;
	do {
		c = 0;
		cout << "Enter flight date : "; getline(cin, info.date);
		if (getDay(info.date) < 0 || getDay(info.date) > 31) c++;
		if (getMonth(info.date) < 0 || getMonth(info.date) > 12) c++;
		if (getYear(info.date) < 0) c++;
	} while (c!=0);

	cout << "Enter flight time : "; getline(cin, info.time);

	while (1) {
		cout << "Enter place departure : "; getline(cin, info.departure);
		if (info.departure.size() > 20) {
			cout << "Place departure contains up to 20 characters\n";
		}
		else break;
	}

	while (1) {
		cout << "Enter destination : "; getline(cin, info.destination);
		
		if (info.destination.size() > 20) {
			cout << "Destination contains up to 20 characters\n";
		}
		else break;
	}
}

//Nhập danh sách thông tin các chuyến bay
void setInfoListFlights(flight* &infList, int n) {
	cin.ignore();
	for (int i = 0; i < n; i++) {
		cout << "-----Enter infomation flight " << i + 1 << " :" << endl;
		setInfoFlight(infList[i]);
		cout << endl;
	}
}

//Xuất thông tin 1 chuyến bay
void showInfoFlight(flight info) {
	cout << setw(10) << info.code << setw(30) << info.fullname << setw(20)
		<< info.date << setw(15) << info.time << setw(15) << info.departure << setw(20) << info.destination;
}

//Xuất danh sách thông tin các chuyến bay
void showInfoListFlights(flight* infList, int n) {
	for (int i = 0; i < n; i++) {
		showInfoFlight(infList[i]);
		cout<<endl;
	}
}

void Press() {
	system("pause");
	system("cls");
}

//Xóa chuyến bay có mã chuyến bay bất kỳ
void deleteAFlight(flight* infList, int& n, string id) {
	for (int i = 0; i < n; i++) {
		if (infList[i].code == id) {
			deleteByPosition(infList, n, i);
			cout << "-----Successful delete !\n";
			return;
		}
	}
	cout << "-----Code Not Found !\n";
}

////xóa theo vị trí
void deleteByPosition(flight* infList, int& n, int pos){
	for (int i = pos + 1; i < n; i++) {
		infList[i - 1] = infList[i];
	}
	n--;
}

//Thêm chuyến bay mới vào danh sách
void addAFlight(flight* infList,int &n) {
	n++;
	int c = 0;
	do {
		cout << "-----Enter information for a new flight:\n";
		setInfoFlight(infList[n-1]);
		for (int i = 0; i < n - 1; i++) {
			if (infList[n - 1].code == infList[i].code) {
				cout << "\nError: Flight code can't match! Please re-enter!\n";
				c++;
			}
		}
	} while (c != 0);
}

// lấy năm từ ngày bay
int getYear(string date) {
	string s;
	for (int i = date.length()-1; i >= 0; i--) {
		if (date[i] != '/') {
			s.insert(s.begin() + 0, date[i]);
		}
		else break;
	}
	int year = atoi(s.c_str());
	return year;
}

// lấy ngay từ ngày bay
int getDay(string date) {
	string s; int j = 0;
	for (int i = 0; i < date.length(); i++) {
		if (date[i] != '/') {
			s.insert(s.begin() + j, date[i]);
			j++;
		}
		else break;
	}
	int day = atoi(s.c_str());
	return day;
}

// lấy thang từ ngày bay
int getMonth(string date) {
	string s; int j = 0;
	for (int i = 3; i < date.length(); i++) {
		if (date[i] != '/') {
			s.insert(s.begin() + j, date[i]);
			j++;
		}
		else break;
	}
	int month = atoi(s.c_str());
	return month;
}

// hoan doi vi tri
void swap(flight& a, flight& b) {
	flight tmp;
	tmp = a;
	a = b;
	b = tmp;
}

// Sắp xếp danh sách chuyến bay tăng dần theo năm bay
void sortFlightsByYear(flight* infList, int n) {
	for (int i = 0; i < n-1; i++) {
		for (int j = i+1; j < n; j++) {
			if (getYear(infList[i].date) > getYear(infList[j].date)) swap(infList[i], infList[j]);
		}
	}
	cout << "-----Successful sort !\n";
}

//Tìm kiếm các chuyến bay có ngày bất kỳ
void searchFlightsByDate(flight* infList, int n, string date) {
	int c = 0;
	for (int i = 0; i < n; i++) {
		if (infList[i].date == date) {
			c++;
			showInfoFlight(infList[i]);
			cout << endl;
		}
	}
	if (c == 0) {
		cout << "\n-----Date Not Found !\n";
	}
}

//Tìm kiếm các chuyến bay có ma chuyen bay bất kỳ
void searchFlightsByCode(flight* infList, int n, string id) {
	int c = 0;
	for (int i = 0; i < n; i++) {
		if (infList[i].code == id) {
			c++;
			showInfoFlight(infList[i]);
			cout << endl;
		}
	}
	if (c == 0) {
		cout << "\n-----Code Not Found !\n";
	}
}

//Tìm kiếm các chuyến bay trong khoảng thời gian (X,Y) cho trước
void searchFlightsInTimePeriod(flight* infList, int n, string from, string to) {
	int day1, day2, month1, month2, year1, year2, c = 0;
	day1 = getDay(from);
	day2 = getDay(to);
	month1 = getMonth(from);
	month2 = getMonth(to);
	year1 = getYear(from);
	year2 = getYear(to);

	for (int i = 0; i < n; i++) {
		if (getYear(infList[i].date) == year1 && getYear(infList[i].date) == year2) {
			if (getMonth(infList[i].date) > month1 && getMonth(infList[i].date) < month2) {
				showInfoFlight(infList[i]); cout << endl;
				c++;
			}
			else if (getMonth(infList[i].date) == month1 && getMonth(infList[i].date) == month2) {
				if (getDay(infList[i].date) > day1 && getDay(infList[i].date) < day2) {
					showInfoFlight(infList[i]); cout << endl;
					c++;
				}
			}
		}
		else if (getYear(infList[i].date) > year1 && getYear(infList[i].date) < year2) {
			showInfoFlight(infList[i]); cout << endl;
			c++;
		}
	}
	if (c == 0) {
		cout << "\n-----Date Not Found !\n";
	}
}

// kiểm tra xâu kí tự có trùng với tên khách hàng không 
bool checkChar(flight infList, string s) {
	int i = 0, j = 0;
	int flag = 0;

	while (infList.fullname[i] != 0)
	{
		if (infList.fullname[i] == s[j])
		{
			j++;
			if (s[j] == 0)
			{
				flag = 1;
				break;
			}
		}
		else
			j = 0;

		i++;
	}

	if (flag) return true;
	return false;
}

//Tìm kiếm thông tin chuyến bay có họ tên hành khách có chữ cái trong họ tên trùng với sâu x cần tìm kiếm
void searchFightsByChar(flight* infList, int n, string s) {
	int c = 0;
	for (int i = 0; i < n; i++) {
		if (checkChar(infList[i], s) == true) {
			showInfoFlight(infList[i]); cout << endl;
			c++;
		}
	}
	if (c == 0) {
		cout << "\n-----Customer's Name Not Found !\n";
	}
}

