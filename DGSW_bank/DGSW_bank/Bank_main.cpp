#include<iostream>
#define NAME_LEN 20
#define SOCIALSECURITYNUMBER_LEN 15
using namespace std;

class Account
{
public:
	//���� ����(������)
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
		cout << endl << cusName << " ������ ���¿� " << deposit << "���� �ԱݵǾ����ϴ�." << endl;
		cout << "�ܾ� : " << balance << "��" << endl;
		return true;
	}
	
	bool Withdraw(int withdraw)
	{
		if (balance < withdraw) {
			cout << "�ܾ��� �����մϴ�." << endl;
			cout << "�ܾ� : " << balance << "��" << endl;
			return false;
		}
		balance += withdraw;
		cout << endl << cusName << " ������ ���¿� " << withdraw << "���� �ԱݵǾ����ϴ�." << endl;
		cout << "�ܾ� : " << balance << "��" << endl;
		return true;
	}

	void Print_All()
	{
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl << endl;
		cout << "�ֹι�ȣ: " << socialSecurityNumber << endl << endl;
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
			if(member != NULL) delete[] member;
			return;
		}
		cout << endl << endl;
	}
}

//���� ����
void Make_Account()
{
	int accID;
	int balance;
	char cusName[NAME_LEN];
	char socialSecurityNumber[SOCIALSECURITYNUMBER_LEN];
	if (member_count >= 100) {
		cout << "���࿡ ���Ե� ����� ��� á���ϴ�." << endl;
		return;
	}
	cout << "[���°���]" << endl;
	cout << "����ID: ";
	cin >> accID;
	for (int i = 0; i < member_count; i++) {
		if (member[i]->getaccID == member[member_count]->getaccID) {
			cout << "���¹�ȣ�� �ߺ��˴ϴ�." << endl;
			return;
		}
	}
	cout << "��  ��: ";
	cin >> cusName;
	cout << "�Աݾ�: ";
	cin >> balance;
	if (balance < 10) {
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
		if (member[i]->getaccID == ID) {
			cout << "�Աݾ�: ";
			cin >> deposit;
			if (deposit <= 0) {
				cout << "�Աݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl;
				return;
			}
			member[i]->getbalance += deposit;

			cout << endl << member[i]->getcusName << " ������ ���¿� " << deposit << "���� �ԱݵǾ����ϴ�." << endl;
			cout << "�ܾ� : " << member[i]->getbalance << "��" << endl;
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
		if (member[i]->getaccID == ID) {
			cout << "��ݾ�: ";
			cin >> withdraw;
			if (withdraw <= 0) {
				cout << "��ݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl;
				return;
			}
			if (member[i]->getbalance < withdraw) {
				cout << "�ܾ��� �����մϴ�." << endl;
				cout << "�ܾ� : " << member[i]->getbalance << "��" << endl;
				return;
			}
			member[i]->getbalance -= withdraw;

			cout << endl << member[i]->getcusName << " ������ ���¿��� " << withdraw << "���� ��ݵǾ����ϴ�." << endl;
			cout << "�ܾ� : " << member[i]->getbalance << "��" << endl;
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
		member[i]->Print_All;
	}
}