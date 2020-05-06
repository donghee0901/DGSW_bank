#include<iostream>
#define NAME_LEN 20
using namespace std;
typedef struct
{
	int accID; //���¹�ȣ 
	int balance; //�ܾ� 
	char cusName[NAME_LEN]; //���̸� 
} Account;

Account *member = new Account[100];
int member_count = 0;

void Select();
void Make_Account();
void Deposit();
void Withdraw();
void Print_All();

void main()
{
	//�������ڸ��� �޴� ����â���� ��
	Select();
}

//�޴� ����
void Select()
{
	int select;
	//������� ���� �� ��� ����
	while (1) {
		//�޴� ���
		cout << "-----Menu------" << endl;
		cout << "1. ���°���" << endl;
		cout << "2. ��    ��" << endl;
		cout << "3. ��    ��" << endl;
		cout << "4. �������� ��ü ���" << endl;
		cout << "5. ���α׷� ����" << endl;
		cout << "����: ";

		//�޴� ����
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
			return;
		}
		cout << endl << endl;
	}
}

//���� ����
void Make_Account()
{
	if (member_count >= 100) {
		cout << "���࿡ ���Ե� ����� ��� á���ϴ�." << endl;
		return;
	}
	cout << "[���°���]" << endl;
	cout << "����ID: ";
	cin >> member[member_count].accID;
	for (int i = 0; i < member_count; i++) {
		if (member[i].accID == member[member_count].accID) {
			cout << "���¹�ȣ�� �ߺ��˴ϴ�." << endl;
			return;
		}
	}
	cout << "��  ��: ";
	cin >> member[member_count].cusName;
	cout << "�Աݾ�: ";
	cin >> member[member_count].balance;
	if (member[member_count].balance < 10) {
		cout << "���°��� �� �ּ� 10�� �̻��� �Աݾ��� �ʿ��մϴ�." << endl;
		return;
	}

	member_count++;
}

//��    ��
void Deposit()
{
	if (member_count == 0) {
		cout << "���� ��ϵ� ���°� �����ϴ�." << endl;
		return;
	}
	int ID;
	int deposit;

	cout << "[��    ��]" << endl;
	cout << "����ID: ";
	cin >> ID;
	for (int i = 0; i < member_count; i++) {
		if (member[i].accID == ID) {
			cout << "�Աݾ�: ";
			cin >> deposit;
			if (deposit <= 0) {
				cout << "�Աݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl;
				return;
			}
			member[i].balance += deposit;

			cout << endl << member[i].cusName << " ������ ���¿� " << deposit << "���� �ԱݵǾ����ϴ�." << endl;
			cout << "�ܾ� : " << member[i].balance << "��" << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID�Դϴ�." << endl;

}

//��    ��
void Withdraw()
{
	if (member_count == 0) {
		cout << "���� ��ϵ� ���°� �����ϴ�." << endl;
		return;
	}
	int ID;
	int withdraw;

	cout << "[��    ��]" << endl;
	cout << "����ID: ";
	cin >> ID;
	for (int i = 0; i < member_count; i++) {
		if (member[i].accID == ID) {
			cout << "��ݾ�: ";
			cin >> withdraw;
			if (withdraw <= 0) {
				cout << "��ݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl;
				return;
			}
			if (member[i].balance < withdraw) {
				cout << "�ܾ��� �����մϴ�." << endl;
				cout << "�ܾ� : " << member[i].balance << "��" << endl;
				return;
			}
			member[i].balance -= withdraw;

			cout << endl << member[i].cusName << " ������ ���¿��� " << withdraw << "���� ��ݵǾ����ϴ�." << endl;
			cout << "�ܾ� : " << member[i].balance << "��" << endl;
			return;
		}
	}
	cout << "��ȿ���� ���� ID�Դϴ�." << endl;

}

//�������� ��ü ���
void Print_All()
{
	if (member_count == 0) {
		cout << "���� ��ϵ� ���°� �����ϴ�." << endl;
		return;
	}
	for (int i = 0; i < member_count; i++) {
		cout << "����ID: " << member[i].accID << endl;
		cout << "��  ��: " << member[i].cusName << endl;
		cout << "��  ��: " << member[i].balance << endl << endl;
	}
}