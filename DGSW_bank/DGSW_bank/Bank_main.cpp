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
	Account(int accID, int balance, char* cusName, char* socialSecurityNumber) :accID(accID), socialSecurityNumber(socialSecurityNumber)
	{
		this->balance = balance;
		this->cusName = cusName;
	}

	//���� ����(���������)
	Account(const Account &copy_member) :accID(copy_member.accID)
	{
		cout << "Copy_Constructor" << endl;
		this->balance = copy_member.balance;
		strcpy_s(cusName, NAME_LEN, copy_member.cusName);
		char *social = new char[SOCIALSECURITYNUMBER_LEN];
		strcpy_s(social, SOCIALSECURITYNUMBER_LEN, copy_member.socialSecurityNumber);
		this->socialSecurityNumber = social;
	}

	//�Ҹ���
	~Account()
	{
		if (cusName != nullptr) delete cusName;
		if (socialSecurityNumber != nullptr) delete socialSecurityNumber;
	}

	//�ܼ� �����
	void Console_clear()
	{
		system("cls");
		cout << endl;
	}

	//�Ա�(Ŭ���� �� �޼ҵ�)
	void Deposit(int deposit)
	{
		if (deposit <= 0) {
			Console_clear();
			cout << "�Աݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl;
			return;
		}

		balance += deposit;
		Console_clear();
		cout << endl << cusName << " ������ ���¿� " << deposit << "���� �ԱݵǾ����ϴ�." << endl;
		cout << "�ܾ� : " << balance << "��" << endl;
		return;
	}

	//���(Ŭ���� �� �޼ҵ�)
	void Withdraw(int withdraw)
	{
		if (balance < withdraw) {
			Console_clear();
			cout << "�ܾ��� �����մϴ�." << endl;
			cout << "�ܾ� : " << balance << "��" << endl;
			return;
		}

		if (withdraw <= 0) {
			Console_clear();
			cout << "��ݾ��� �ּ� 1�� �̻��̿��� �մϴ�." << endl;
			return;
		}

		balance -= withdraw;
		Console_clear();
		cout << endl << cusName << " ������ ���¿��� " << withdraw << "���� ��ݵǾ����ϴ�." << endl;
		cout << "�ܾ� : " << balance << "��" << endl;
		return;
	}

	//�������� ���(Ŭ���� �� �޼ҵ�)
	void Print_All()
	{
		cout << endl;
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
		cout << "�ֹι�ȣ: " << socialSecurityNumber << endl;
	}

	//get, set�Լ�(Ŭ���� �� �޼ҵ�)
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
private:
	const int accID;
	int balance;
	char *cusName = nullptr;
	const char *socialSecurityNumber = nullptr;
};
class AccountManager
{
public:
	~AccountManager()
	{
		for (int i = 0; i < MAX_ACCOUNT; i++) {
			if (member[i] != nullptr) delete member[i];
		}
	}

	//�ܼ� �����
	void Console_clear()
	{
		system("cls");
		cout << endl;
	}

	//���� ���� Ȯ��
	bool Have_Account()
	{
		if (member_count == 0) {
			Console_clear();
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
			Console_clear();
			cout << "���࿡ ���Ե� ����� ��� á���ϴ�." << endl;
			return;
		}
		Console_clear();
		cout << "[���°���]" << endl;
		cout << "����ID: ";
		cin >> accID;

		select_ID = Select_AccID(accID);
		if (select_ID >= 0) {
			Console_clear();
			cout << "���¹�ȣ�� �ߺ��˴ϴ�." << endl;
			return;
		}

		cout << "��  ��: ";
		cin >> cusName;

		cout << "�Աݾ�: ";
		cin >> balance;
		if (balance < 10) {
			Console_clear();
			cout << "���°��� �� �ּ� 10�� �̻��� �Աݾ��� �ʿ��մϴ�." << endl;
			return;
		}

		cout << "�ֹι�ȣ: ";
		cin >> socialSecurityNumber;

		select_SocialSecurityNumber = Select_SocialSecurityNumber(socialSecurityNumber);
		if (select_SocialSecurityNumber != -1) {
			Console_clear();
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

		Console_clear();
		cout << "[��    ��]" << endl;
		cout << "����ID: ";
		cin >> accID;

		select_ID = Select_AccID(accID);
		if (select_ID == -1) {
			Console_clear();
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

		Console_clear();
		cout << "[��    ��]" << endl;
		cout << "����ID: ";
		cin >> accID;

		select_ID = Select_AccID(accID);
		if (select_ID == -1) {
			Console_clear();
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
		Console_clear();
		cout << "[�������� ��ü ���]" << endl;
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
AccountManager manager;

void Select();

int main()
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

