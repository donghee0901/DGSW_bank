#include<iostream>
#define NAME_LEN 20
using namespace std;
typedef struct
{
	int accID; //���¹�ȣ 
	int balance; //�ܾ� 
	char cusName[NAME_LEN]; //���̸� 
} Account;
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
			//���°���
			break;
		case 2:
			//�Ա�
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
	}
}
void main()
{
	//�������ڸ��� �޴� ����â���� ��
	Select();
}