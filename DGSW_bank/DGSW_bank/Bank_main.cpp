#include<iostream>
#include<cstring>
#define NAME_LEN 20
#define SOCIALSECURITYNUMBER_LEN 15
#define MAX_ACCOUNT 100
using namespace std;

class Account
{
public:
	//���� ����(������)
	Account(int accID, int balance, char* cusName, char* socialSecurityNumber)
	{
		this->accID = accID;
		this->balance = balance;
		this->cusName = cusName;
		this->socialSecurityNumber = socialSecurityNumber;
	}

	~Account()
	{
		if (cusName != nullptr) delete cusName;
		if (socialSecurityNumber != nullptr) delete socialSecurityNumber;
	}

	void Deposit(int deposit)
	{
		if (deposit <= 0) {
			cout << "�Աݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl;
			return;
		}

		balance += deposit;
		cout << endl << cusName << " ������ ���¿� " << deposit << "���� �ԱݵǾ����ϴ�." << endl;
		cout << "�ܾ� : " << balance << "��" << endl;
		return;
	}
	
	void Withdraw(int withdraw)
	{
		if (balance < withdraw) {
			cout << "�ܾ��� �����մϴ�." << endl;
			cout << "�ܾ� : " << balance << "��" << endl;
			return;
		}

		if (withdraw <= 0) {
			cout << "��ݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl;
			return;
		}

		balance -= withdraw;
		cout << endl << cusName << " ������ ���¿��� " << withdraw << "���� ��ݵǾ����ϴ�." << endl;
		cout << "�ܾ� : " << balance << "��" << endl;
		return;
	}

	void Print_All()
	{
		cout << endl;
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
		cout << "�ֹι�ȣ: " << socialSecurityNumber << endl;
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

Account *member[MAX_ACCOUNT];
int member_count = 0;

bool Have_Account();
int Select_AccID(int accID);
int Select_SocialSecurityNumber(char* socialSecurityNumber);
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

//���� ���� Ȯ��
bool Have_Account()
{
	if (member_count == 0) {
		cout << "���� ��ϵ� ���°� �����ϴ�." << endl;
		return false;
	}
	return true;
}

//accID �ߺ� Ȯ��
int Select_AccID(int accID)
{
	for (int i = 0; i < member_count; i++) {
		if (member[i]->getaccID() == accID) {
			return i;
		}
	}
	return -1;
}

//�ֹι�ȣ �ߺ� Ȯ��
int Select_SocialSecurityNumber(char* socialSecurityNumber)
{
	for (int i = 0; i < member_count; i++) {
		if (strcmp(socialSecurityNumber, member[i]->getsocialSecurityNumber()) == 0) {
			return i;
		}
	}
	return -1;
}

//���� ����
void Make_Account()
{
	int select_ID;
	int select_SocialSecurityNumber;

	int accID;
	int balance;
	char *cusName = new char[NAME_LEN];
	char *socialSecurityNumber = new char[SOCIALSECURITYNUMBER_LEN];

	if (member_count >= MAX_ACCOUNT) {
		cout << "���࿡ ���Ե� ����� ��� á���ϴ�." << endl;
		return;
	}
	cout << "[���°���]" << endl;
	cout << "����ID: ";
	cin >> accID;

	select_ID = Select_AccID(accID);
	if (select_ID >= 0) {
		cout << "���¹�ȣ�� �ߺ��˴ϴ�." << endl;
		return;
	}

	cout << "��  ��: ";
	cin >> cusName;

	cout << "�Աݾ�: ";
	cin >> balance;
	if (balance < 10) {
		cout << "���°��� �� �ּ� 10�� �̻��� �Աݾ��� �ʿ��մϴ�." << endl;
		return;
	}

	cout << "�ֹι�ȣ: ";
	cin >> socialSecurityNumber;
	
	select_SocialSecurityNumber = Select_SocialSecurityNumber(socialSecurityNumber);
	if (select_SocialSecurityNumber != -1) {
		cout << "�ֹι�ȣ�� �ߺ��˴ϴ�." << endl;
		return;
	}

	member[member_count] = new Account(accID, balance, cusName, socialSecurityNumber);

	member_count++;
}

//��    ��
void Deposit()
{
	if (Have_Account() == false) {
		return;
	}
	int accID;
	int deposit;
	int select_ID;

	cout << "[��    ��]" << endl;
	cout << "����ID: ";
	cin >> accID;

	select_ID = Select_AccID(accID);
	if (select_ID == -1) {
		cout << "��ȿ���� ���� ID�Դϴ�." << endl;
		return;
	}
	cout << "�Աݾ�: ";
	cin >> deposit;

	member[select_ID]->Deposit(deposit);
}

//��    ��
void Withdraw()
{
	if (Have_Account() == false) {
		return;
	}
	int accID;
	int withdraw;
	int select_ID;

	cout << "[��    ��]" << endl;
	cout << "����ID: ";
	cin >> accID;

	select_ID = Select_AccID(accID);
	if (select_ID == -1) {
		cout << "��ȿ���� ���� ID�Դϴ�." << endl;
		return;
	}
	cout << "��ݾ�: ";
	cin >> withdraw;

	member[select_ID]->Withdraw(withdraw);
}

//�������� ��ü ���
void Print_All()
{
	if (Have_Account() == false) {
		return;
	}
	for (int i = 0; i < member_count; i++) {
		member[i]->Print_All();
	}
}