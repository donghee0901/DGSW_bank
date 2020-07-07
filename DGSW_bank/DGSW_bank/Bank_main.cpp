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
	//���� ����(������)
	Account(int input_accID, int input_balance, char* input_cusName, char* input_socialSecurityNumber) :accID(input_accID), socialSecurityNumber(input_socialSecurityNumber)
	{
		this->balance = input_balance;
		this->cusName = input_cusName;
	}

	//���� ���� ����(������ �����ε�)
	Account(int input_accID, char* input_cusName, const char* input_socialSecurityNumber) : accID(input_accID)
	{
		this->balance = 0;
		cusName = new char[NAME_LEN];
		strcpy_s(cusName, NAME_LEN, input_cusName);
		char *social = new char[SOCIALSECURITYNUMBER_LEN];
		strcpy_s(social, SOCIALSECURITYNUMBER_LEN, input_socialSecurityNumber);
		this->socialSecurityNumber = social;
	}

	//���������
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

	//�Ҹ���
	virtual ~Account()
	{
		cout << "Account" << endl;
		if (cusName != nullptr) delete cusName;
		if (socialSecurityNumber != nullptr) delete socialSecurityNumber;
	}

	//�ܼ� �����
	void Console_clear()
	{
		//system("cls");
		//cout << endl;
	}

	//���� ���
	virtual int Calculate_Interest(int amount)
	{
		return (int)((float)amount * 0.01);
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

		int interest = Calculate_Interest(balance);
		balance += interest;

		Console_clear();
		cout << endl << cusName << " ������ ���¿� " << deposit << "���� �ԱݵǾ����ϴ�." << endl;
		cout << endl << "���� " << interest << "���� �߰��Ǿ����ϴ�." << endl;
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
	virtual void Print_All()
	{
		cout << endl;
		cout << "���� ����: ���� ����" << endl;
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
protected:
	const int accID;
	int balance;
	char *cusName = nullptr;
	const char *socialSecurityNumber = nullptr;
};
class DepositAccount : public Account
{
public:
	//�����ε��� �θ� �����ڸ� �̿��Ͽ� ���ݰ��� ����
	DepositAccount(Account &copy_member, int input_accID) : Account(input_accID, copy_member.getcusName(), copy_member.getsocialSecurityNumber())
	{
		
	}

	~DepositAccount()
	{
		cout << "DepositAccount" << endl;
		
	}

	//���� ���(������)
	virtual int Calculate_Interest(int amount)
	{
		return (int)((float)amount * 0.02);
	}

	//�������� ���(������)
	virtual void Print_All()
	{
		cout << endl;
		cout << "���� ����: ���� ����" << endl;
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
		cout << "�ֹι�ȣ: " << socialSecurityNumber << endl;
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

	//���ݰ��� ���� �Է¹ޱ�
	bool CinDepositWhether()
	{
		char scan;
		cout << "������ ������ �������ּ���." << endl;
		cout << "1. �������" << endl;
		cout << "2. ���ݰ���" << endl;
		cin >> scan;
		if (scan == '1')return false;
		else if(scan == '2') return true;
		else {
			cout << "�߸��� �Է�" << endl << endl;
			return CinDepositWhether();
		}
	}

	//�ܼ� �����
	void Console_clear()
	{
		//system("cls");
		//cout << endl;
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
		
		if (member_count >= MAX_ACCOUNT) {
			Console_clear();
			cout << "���࿡ ���Ե� ����� ��� á���ϴ�." << endl;
			return;
		}
		Console_clear();
		cout << "[���°���]" << endl;
		if (CinDepositWhether() == false){
			Make_Ordinary_Account();
		}
		else {
			Make_Deposit_Account();
		}
	}

	//������� ����
	void Make_Ordinary_Account()
	{
		int select_ID;
		int select_SocialSecurityNumber;

		int accID;
		int balance;
		char *cusName = new char[NAME_LEN];
		char *socialSecurityNumber = new char[SOCIALSECURITYNUMBER_LEN];

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

	//���ݰ��� ����
	void Make_Deposit_Account()
	{
		int select_ID;
		int select_Original_accID;
		int Original_accID;
		int accID;

		cout << "���� ����ID: ";
		cin >> Original_accID;
		select_Original_accID = Select_AccID(Original_accID);
		
		if (select_Original_accID == -1) {
			Console_clear();
			cout << "���� ���°� �������� �ʽ��ϴ�." << endl;
			return;
		}

		cout << "����ID: ";
		cin >> accID;
		select_ID = Select_AccID(accID);

		if (select_ID >= 0) {
			Console_clear();
			cout << "���¹�ȣ�� �ߺ��˴ϴ�." << endl;
			return;
		}

		member[member_count] = new DepositAccount(*member[select_Original_accID], accID);

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


void Select(AccountManager &manager);

int main()
{
	AccountManager manager;
	//�������ڸ��� �޴� ����â���� ��
	Select(manager);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_CRT_DF);
}
//�޴� ����
void Select(AccountManager &manager)
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

