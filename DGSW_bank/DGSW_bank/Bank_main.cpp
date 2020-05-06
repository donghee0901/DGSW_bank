#include<iostream>
#define NAME_LEN 20
using namespace std;
typedef struct
{
	int accID; //계좌번호 
	int balance; //잔액 
	char cusName[NAME_LEN]; //고객이름 
} Account;
Account *member = new Account[100];
int member_count = 0;

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
			//계좌개설
			break;
		case 2:
			//입금
			break;
		case 3:
			//출금
			break;
		case 4:
			//계좌정보 전체 출력
			break;
		case 5:
			return;
		}
	}
}

//계좌 개설
void Make_Account()
{
	cout << "[입    금]" << endl;
	cout << "계좌ID: ";
	cin >> member[member_count].accID;
	for (int i = 0; i < member_count; i++) {
		if (member[i].accID == member[member_count].accID) {
			cout << "계좌번호가 중복됩니다." << endl;
			return;
		}
	}
	cout << "이  름: ";
	cin >> member[member_count].cusName;
	cout << "입금액: ";
	cin >> member[member_count].balance;
	if (member[member_count].balance < 10) {
		cout << "계좌개설 시 10원 이상의 입금액이 필요합니다." << endl;
		return;
	}
	
	member_count++;
}
void main()
{
	//시작하자마자 메뉴 선택창으로 감
	Select();
}