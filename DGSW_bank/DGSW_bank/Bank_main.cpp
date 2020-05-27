#include<iostream>
#define NAME_LEN 20
#define SOCIALSECURITYNUMBER_LEN 15
using namespace std;

class Account
{
public:
	//계좌 개설(생성자)
	Account(int accID, int balance, char cusName[NAME_LEN], char socialSecurityNumber[SOCIALSECURITYNUMBER_LEN])
	{
		this->accID = accID;
		this->balance = balance;
		this->cusName = cusName;
		this->socialSecurityNumber = socialSecurityNumber;
	}

	~Account()
	{
		delete socialSecurityNumber;
		delete cusName;
	}

	bool Deposit(int deposit)
	{
		balance += deposit;
		cout << endl << cusName << " 고객님의 계좌에 " << deposit << "원이 입금되었습니다." << endl;
		cout << "잔액 : " << balance << "원" << endl;
		return true;
	}
	
	bool Withdraw(int withdraw)
	{
		if (balance < withdraw) {
			cout << "잔액이 부족합니다." << endl;
			cout << "잔액 : " << balance << "원" << endl;
			return false;
		}
		balance += withdraw;
		cout << endl << cusName << " 고객님의 계좌에 " << withdraw << "원이 입금되었습니다." << endl;
		cout << "잔액 : " << balance << "원" << endl;
		return true;
	}

	void Print_All()
	{
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl << endl;
		cout << "주민번호: " << socialSecurityNumber << endl << endl;
	}

	int getaccID()
	{
		return accID;
	}
	int getbalance()
	{
		return balance;
	}
	char* getcusName()
	{
		return cusName;
	}
	char* getsocialSecurityNumber()
	{
		return socialSecurityNumber;
	}
private:
	int accID;
	int balance;
	char *cusName;
	char *socialSecurityNumber;
};

Account *member[100];
int member_count = 0;

void Select();
void Make_Account();
void Deposit();
void Withdraw();
void Print_All();

void main()
{
	//시작하자마자 메뉴 선택창으로 감
	Select();
}

//메뉴 선택
void Select()
{
	int select;
	//종료되지 않을 때 계속 돌림
	while (1) {
		//메뉴 출력
		cout << "-----Menu------" << endl;
		cout << "1. 계좌개설" << endl;
		cout << "2. 입    금" << endl;
		cout << "3. 출    금" << endl;
		cout << "4. 계좌정보 전체 출력" << endl;
		cout << "5. 프로그램 종료" << endl;
		cout << "선택: ";

		//메뉴 선택
		cin >> select;

		switch (select)
		{
		case 1:
			Make_Account();
			break;
		case 2:
			Deposit();
			break;
		case 3:
			Withdraw();
			break;
		case 4:
			Print_All();
			break;
		case 5:
			if(member != NULL) delete[] member;
			return;
		}
		cout << endl << endl;
	}
}

//계좌 개설
void Make_Account()
{
	int accID;
	int balance;
	char cusName[NAME_LEN];
	char socialSecurityNumber[SOCIALSECURITYNUMBER_LEN];
	if (member_count >= 100) {
		cout << "은행에 가입된 사람이 모두 찼습니다." << endl;
		return;
	}
	cout << "[계좌개설]" << endl;
	cout << "계좌ID: ";
	cin >> accID;
	for (int i = 0; i < member_count; i++) {
		if (member[i]->getaccID == member[member_count]->getaccID) {
			cout << "계좌번호가 중복됩니다." << endl;
			return;
		}
	}
	cout << "이  름: ";
	cin >> cusName;
	cout << "입금액: ";
	cin >> balance;
	if (balance < 10) {
		cout << "계좌개설 시 최소 10원 이상의 입금액이 필요합니다." << endl;
		return;
	}

	member_count++;
}

//입    금
void Deposit()
{
	if (member_count == 0) {
		cout << "현재 등록된 계좌가 없습니다." << endl;
		return;
	}
	int ID;
	int deposit;

	cout << "[입    금]" << endl;
	cout << "계좌ID: ";
	cin >> ID;
	for (int i = 0; i < member_count; i++) {
		if (member[i]->getaccID == ID) {
			cout << "입금액: ";
			cin >> deposit;
			if (deposit <= 0) {
				cout << "입금액은 최소 1원 이상이여야 합니다." << endl;
				return;
			}
			member[i]->getbalance += deposit;

			cout << endl << member[i]->getcusName << " 고객님의 계좌에 " << deposit << "원이 입금되었습니다." << endl;
			cout << "잔액 : " << member[i]->getbalance << "원" << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID입니다." << endl;

}

//출    금
void Withdraw()
{
	if (member_count == 0) {
		cout << "현재 등록된 계좌가 없습니다." << endl;
		return;
	}
	int ID;
	int withdraw;

	cout << "[출    금]" << endl;
	cout << "계좌ID: ";
	cin >> ID;
	for (int i = 0; i < member_count; i++) {
		if (member[i]->getaccID == ID) {
			cout << "출금액: ";
			cin >> withdraw;
			if (withdraw <= 0) {
				cout << "출금액은 최소 1원 이상이여야 합니다." << endl;
				return;
			}
			if (member[i]->getbalance < withdraw) {
				cout << "잔액이 부족합니다." << endl;
				cout << "잔액 : " << member[i]->getbalance << "원" << endl;
				return;
			}
			member[i]->getbalance -= withdraw;

			cout << endl << member[i]->getcusName << " 고객님의 계좌에서 " << withdraw << "원이 출금되었습니다." << endl;
			cout << "잔액 : " << member[i]->getbalance << "원" << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID입니다." << endl;

}

//계좌정보 전체 출력
void Print_All()
{
	if (member_count == 0) {
		cout << "현재 등록된 계좌가 없습니다." << endl;
		return;
	}
	for (int i = 0; i < member_count; i++) {
		member[i]->Print_All;
	}
}