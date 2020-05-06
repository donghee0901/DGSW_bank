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

void Make_Account();
void Deposit();


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
			//���
			break;
		case 4:
			//�������� ��ü ���
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
void main()
{
	//�������ڸ��� �޴� ����â���� ��
	Select();
}