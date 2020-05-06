#include<iostream>
#define NAME_LEN 20
using namespace std;
typedef struct
{
	int accID; //계좌번호 
	int balance; //잔액 
	char cusName[NAME_LEN]; //고객이름 
} Account;
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
void main()
{
	//시작하자마자 메뉴 선택창으로 감
	Select();
}