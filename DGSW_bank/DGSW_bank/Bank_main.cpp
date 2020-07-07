#include<iostream>
#include<cstring>
#define _CRTDBG_MAP_ALLOC
#include<cstdlib>
#include<crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new(_NORMAL_BLOCK, _FILE_, _LINE_)
#else
#define DBG_NEW new
#endif

#define NAME_LEN 20
#define SOCIALSECURITYNUMBER_LEN 15
#define MAX_ACCOUNT 100
using namespace std;
class Account
{
public:
	//계좌 개설(생성자)
	Account(int input_accID, int input_balance, char* input_cusName, char* input_socialSecurityNumber) :accID(input_accID), socialSecurityNumber(input_socialSecurityNumber)
	{
		this->balance = input_balance;
		this->cusName = input_cusName;
	}

	//예금 계좌 개설(생성자 오버로딩)
	Account(int input_accID, char* input_cusName, const char* input_socialSecurityNumber) : accID(input_accID)
	{
		this->balance = 0;
		cusName = new char[NAME_LEN];
		strcpy_s(cusName, NAME_LEN, input_cusName);
		char *social = new char[SOCIALSECURITYNUMBER_LEN];
		strcpy_s(social, SOCIALSECURITYNUMBER_LEN, input_socialSecurityNumber);
		this->socialSecurityNumber = social;
	}

	//복사생성자
	Account(const Account &copy_member) :accID(copy_member.accID)
	{
		cout << "Copy_Constructor" << endl;
		this->balance = copy_member.balance;
		cusName = new char[NAME_LEN];
		strcpy_s(cusName, NAME_LEN, copy_member.cusName);
		char *social = new char[SOCIALSECURITYNUMBER_LEN];
		strcpy_s(social, SOCIALSECURITYNUMBER_LEN, copy_member.socialSecurityNumber);
		this->socialSecurityNumber = social;
	}

	//소멸자
	virtual ~Account()
	{
		cout << "Account" << endl;
		if (cusName != nullptr) delete cusName;
		if (socialSecurityNumber != nullptr) delete socialSecurityNumber;
	}

	//콘솔 지우기
	void Console_clear()
	{
		//system("cls");
		//cout << endl;
	}

	//이자 계산
	virtual int Calculate_Interest(int amount)
	{
		return (int)((float)amount * 0.01);
	}

	//입금(클래스 내 메소드)
	void Deposit(int deposit)
	{
		if (deposit <= 0) {
			Console_clear();
			cout << "입금액은 최소 1원 이상이여야 합니다." << endl;
			return;
		}

		balance += deposit;

		int interest = Calculate_Interest(balance);
		balance += interest;

		Console_clear();
		cout << endl << cusName << " 고객님의 계좌에 " << deposit << "원이 입금되었습니다." << endl;
		cout << endl << "이자 " << interest << "원이 추가되었습니다." << endl;
		cout << "잔액 : " << balance << "원" << endl;
		return;
	}

	//출금(클래스 내 메소드)
	void Withdraw(int withdraw)
	{
		if (balance < withdraw) {
			Console_clear();
			cout << "잔액이 부족합니다." << endl;
			cout << "잔액 : " << balance << "원" << endl;
			return;
		}
		if (withdraw <= 0) {
			Console_clear();
			cout << "출금액은 최소 1원 이상이여야 합니다." << endl;
			return;
		}

		balance -= withdraw;
		Console_clear();
		cout << endl << cusName << " 고객님의 계좌에서 " << withdraw << "원이 출금되었습니다." << endl;
		cout << "잔액 : " << balance << "원" << endl;
		return;
	}

	//계좌정보 출력(클래스 내 메소드)
	virtual void Print_All()
	{
		cout << endl;
		cout << "계좌 종류: 보통 계좌" << endl;
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
		cout << "주민번호: " << socialSecurityNumber << endl;
	}

	//get, set함수(클래스 내 메소드)
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
	const char* getsocialSecurityNumber()
	{
		return socialSecurityNumber;
	}
protected:
	const int accID;
	int balance;
	char *cusName = nullptr;
	const char *socialSecurityNumber = nullptr;
};
class DepositAccount : public Account
{
public:
	//오버로딩된 부모 생성자를 이용하여 예금계좌 생성
	DepositAccount(Account &copy_member, int input_accID) : Account(input_accID, copy_member.getcusName(), copy_member.getsocialSecurityNumber())
	{
		
	}

	~DepositAccount()
	{
		cout << "DepositAccount" << endl;
		
	}

	//이자 계산(재정의)
	virtual int Calculate_Interest(int amount)
	{
		return (int)((float)amount * 0.02);
	}

	//계좌정보 출력(재정의)
	virtual void Print_All()
	{
		cout << endl;
		cout << "계좌 종류: 예금 계좌" << endl;
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
		cout << "주민번호: " << socialSecurityNumber << endl;
	}
};
class AccountManager
{
public:
	~AccountManager()
	{
		cout << "AccountManager" << endl;
		for (int i = 0; i < member_count; i++) {
			if (member[i] != nullptr) delete[] member[i];
		}
	}

	//예금계좌 여부 입력받기
	bool CinDepositWhether()
	{
		char scan;
		cout << "계좌의 종류를 선택해주세요." << endl;
		cout << "1. 보통계좌" << endl;
		cout << "2. 예금계좌" << endl;
		cin >> scan;
		if (scan == '1')return false;
		else if(scan == '2') return true;
		else {
			cout << "잘못된 입력" << endl << endl;
			return CinDepositWhether();
		}
	}

	//콘솔 지우기
	void Console_clear()
	{
		//system("cls");
		//cout << endl;
	}

	//계좌 여부 확인
	bool Have_Account()
	{
		if (member_count == 0) {
			Console_clear();
			cout << "현재 등록된 계좌가 없습니다." << endl;
			return false;
		}
		return true;
	}

	//accID 중복 확인
	int Select_AccID(int accID)
	{
		for (int i = 0; i < member_count; i++) {
			if (member[i]->getaccID() == accID) {
				return i;
			}
		}
		return -1;
	}

	//주민번호 중복 확인
	int Select_SocialSecurityNumber(char* socialSecurityNumber)
	{
		for (int i = 0; i < member_count; i++) {
			if (strcmp(socialSecurityNumber, member[i]->getsocialSecurityNumber()) == 0) {
				return i;
			}
		}
		return -1;
	}
	//계좌 개설
	void Make_Account()
	{
		
		if (member_count >= MAX_ACCOUNT) {
			Console_clear();
			cout << "은행에 가입된 사람이 모두 찼습니다." << endl;
			return;
		}
		Console_clear();
		cout << "[계좌개설]" << endl;
		if (CinDepositWhether() == false){
			Make_Ordinary_Account();
		}
		else {
			Make_Deposit_Account();
		}
	}

	//보통계좌 개설
	void Make_Ordinary_Account()
	{
		int select_ID;
		int select_SocialSecurityNumber;

		int accID;
		int balance;
		char *cusName = new char[NAME_LEN];
		char *socialSecurityNumber = new char[SOCIALSECURITYNUMBER_LEN];

		cout << "계좌ID: ";
		cin >> accID;

		select_ID = Select_AccID(accID);
		if (select_ID >= 0) {
			Console_clear();
			cout << "계좌번호가 중복됩니다." << endl;
			return;
		}

		cout << "이  름: ";
		cin >> cusName;

		cout << "입금액: ";
		cin >> balance;
		if (balance < 10) {
			Console_clear();
			cout << "계좌개설 시 최소 10원 이상의 입금액이 필요합니다." << endl;
			return;
		}

		cout << "주민번호: ";
		cin >> socialSecurityNumber;

		select_SocialSecurityNumber = Select_SocialSecurityNumber(socialSecurityNumber);
		if (select_SocialSecurityNumber != -1) {
			Console_clear();
			cout << "주민번호가 중복됩니다." << endl;
			return;
		}

		member[member_count] = new Account(accID, balance, cusName, socialSecurityNumber);

		member_count++;
	}

	//예금계좌 개설
	void Make_Deposit_Account()
	{
		int select_ID;
		int select_Original_accID;
		int Original_accID;
		int accID;

		cout << "원본 계좌ID: ";
		cin >> Original_accID;
		select_Original_accID = Select_AccID(Original_accID);
		
		if (select_Original_accID == -1) {
			Console_clear();
			cout << "원본 계좌가 존재하지 않습니다." << endl;
			return;
		}

		cout << "계좌ID: ";
		cin >> accID;
		select_ID = Select_AccID(accID);

		if (select_ID >= 0) {
			Console_clear();
			cout << "계좌번호가 중복됩니다." << endl;
			return;
		}

		member[member_count] = new DepositAccount(*member[select_Original_accID], accID);

		member_count++;
	}

	//입    금
	void Deposit()
	{
		if (Have_Account() == false) {
			return;
		}
		int accID;
		int deposit;
		int select_ID;

		Console_clear();
		cout << "[입    금]" << endl;
		cout << "계좌ID: ";
		cin >> accID;

		select_ID = Select_AccID(accID);
		if (select_ID == -1) {
			Console_clear();
			cout << "유효하지 않은 ID입니다." << endl;
			return;
		}
		cout << "입금액: ";
		cin >> deposit;

		member[select_ID]->Deposit(deposit);
	}

	//출    금
	void Withdraw()
	{
		if (Have_Account() == false) {
			return;
		}
		int accID;
		int withdraw;
		int select_ID;

		Console_clear();
		cout << "[출    금]" << endl;
		cout << "계좌ID: ";
		cin >> accID;

		select_ID = Select_AccID(accID);
		if (select_ID == -1) {
			Console_clear();
			cout << "유효하지 않은 ID입니다." << endl;
			return;
		}
		cout << "출금액: ";
		cin >> withdraw;

		member[select_ID]->Withdraw(withdraw);
	}

	//계좌정보 전체 출력
	void Print_All()
	{
		Console_clear();
		cout << "[계좌정보 전체 출력]" << endl;
		if (Have_Account() == false) {
			return;
		}
		for (int i = 0; i < member_count; i++) {
			member[i]->Print_All();
		}
	}
private:
	Account *member[MAX_ACCOUNT];
	int member_count = 0;
};


void Select(AccountManager &manager);

int main()
{
	AccountManager manager;
	//시작하자마자 메뉴 선택창으로 감
	Select(manager);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_CRT_DF);
}
//메뉴 선택
void Select(AccountManager &manager)
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
			manager.Make_Account();
			break;
		case 2:
			manager.Deposit();
			break;
		case 3:
			manager.Withdraw();
			break;
		case 4:
			manager.Print_All();
			break;
		case 5:
			return;
		}
		cout << endl << endl;
	}
}

