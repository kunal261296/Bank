#include<fstream>
#include<cctype>
#include<stdlib.h>
#include<ctime>
#include<windows.h>
#include<iostream>
using namespace std;
class account               //CLASS ACOUNT DECLARATION
{
	int amount;
    char name[30];
    int accno;
    public: virtual void getdetails();
    		virtual void showdetails();
    		void deposit(int);
       		void withdraw(int);
       		int getacno() const;
       		void report() const;
       		int retamount();
       		void getamount();
       		void modify();
};
void account::getdetails()
{
	srand(time(NULL));
    accno=rand()%10000;
    srand(time(NULL));
    cout<<"YOUR ACCOUNT NUMBER:"<<accno;
    cout<<"\n\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name,50);
}

void account::getamount()
 {
 	cout<<"\nenter the Initial amount : ";
 	cin>>amount;
 }
void account::showdetails()
{
	cout<<"\nAccount No. : "<<accno;
    cout<<"\nAccount Holder Name :"<<name;
    cout<<"\nBalance amount : "<<amount;
}
void account::modify()
{
    cout<<"\nAccount No. : "<<accno;
    cout<<"\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name,50);


    cout<<"\nModify Balance amount : ";
    cin>>amount;
}
void account::deposit(int x)
{
    amount+=x;
}
void account::withdraw(int x)
{
    amount=amount-x;
}
int account::getacno() const
{
	return accno;
}
int account::retamount()
{
	return amount;
}
void account::report() const
{

    cout<<accno<<" \t\t"<<name<<"\t\t"<<amount<<endl<<endl;
}

class current:public account
{
    	int amt;
		account ac;
		ofstream outFile;
		ifstream inFile;
		fstream File;

		public:void getdetails()
			{
				outFile.open("current.txt",ios::app);
               ac.getdetails();
               do{
               	ac.getamount();
               	try{
               		if(ac.retamount()<1000)
               		throw 1;

               		MessageBox(NULL, "ACCOUNT CREATED SUCCESSFULLY", "SUCCESSFUL", MB_OK);
               		outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
                	outFile.close();
				   }
				   catch(int i){
				   	 MessageBox(NULL, "DEPOSIT CANT BE LESS THAN 1000", "WARNING", MB_OK);
				   }
			   }while(ac.retamount()<1000);
				}
			void deposit_withdraw(int n, int option)
    		{

	        bool found=false;
	        File.open("current.txt", ios::in|ios::out);
	        if(!File)
	        {
	            cout<<"File could not be open !! Press any Key...";
	            return;
	        }
	        while(!File.eof() && found==false)
	        {
	            File.read(reinterpret_cast<char *> (&ac), sizeof(account));
	            if(ac.getacno()==n)
	            {
	                ac.showdetails();
	                if(option==1)
	                {
	                    cout<<"\n\n\tTO DEPOSITE AMOUNT ";
	                    cout<<"\n\nEnter The amount to be deposited:-";
	                    cin>>amt;
	                    ac.deposit(amt);
	                }
	                if(option==2)
	                {
	                    cout<<"\n\n\tTO WITHDRAW AMOUNT ";
	                    cout<<"\n\nEnter The amount to be withdraw:-";
	                    cin>>amt;
	                    ac.withdraw(amt);

	            }
	                int pos=(-1)*static_cast<int>(sizeof(ac));
	                File.seekp(pos,ios::cur);
	                File.write(reinterpret_cast<char *> (&ac), sizeof(account));
	                cout<<"\n\n\t Record Updated";
	                found=true;
	               }
	             }
	        File.close();
	        if(found==false)
	        cout<<"\n\n Record Not Found ";
  		  }


  		  void delete_account(int n)
    {
        inFile.open("current.txt");
        if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        outFile.open("Temp.txt");
        inFile.seekg(0,ios::beg);
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
        {
            if(ac.getacno()!=n)
            {
                outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
            }
        }
        inFile.close();
        outFile.close();
        remove("current.txt");
        rename("Temp.txt","current.txt");
        cout<<"\n\n\tRecord Deleted ..";
    }
     void display_all()
    {

        inFile.open("current.txt");
        if(!inFile)
        {
            cout<<"\nFile could not be open !! Press any Key...";
            return;
        }
        cout<<"\n\n\t\tCURRENT ACCOUNT HOLDER LIST\n\n";
        cout<<"A/c no." <<"\t\t" <<" NAME"<<"\t\t"<< "Balance\n";
        cout<<"------------------------------------------------------\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
        {
            ac.report();
        }
        inFile.close();
    }
    void display_sp(int n)
            {
                bool flag=false;
                inFile.open("current.txt");
                if(!inFile)
                {
                    cout<<"\nFile could not be open. Press any Key...";
                    return;
                }
                cout<<"\nBALANCE DETAILS\n";

                    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
                    {
                        if(ac.getacno()==n)
                        {
                            ac.showdetails();
                            cout<<"\n";
                            flag=true;
                        }
                    }
                inFile.close();
                if(flag==false)
                cout<<"\n\nINVALID ACCOUNT NUMBER";
            }
             void modify_account(int n)
    {
        bool found=false;
        File.open("current.txt",ios::in|ios::out);
        if(!File)
        {
            cout<<"\nFile could not be open !! Press any Key...";
            return;
        }
        while(!File.eof() && found==false)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(account));
            if(ac.getacno()==n)
            {
                ac.showdetails();
                cout<<"\nEnter The New Details of account"<<endl;
                ac.modify();
                int pos=(-1)*static_cast<int>(sizeof(account));
                File.seekp(pos,ios::cur);
                File.write(reinterpret_cast<char *> (&ac), sizeof(account));
                cout<<"\n Details Updated";
                found=true;
              }
        }
        File.close();
        if(found==false)
        cout<<"\n\n Record Not Found ";
    }
};
class saving:public account
{		int amt;
		account ac;
		ofstream outFile;
		ifstream inFile;
		fstream File;
		public:void getdetails()
			{
				outFile.open("saving.txt",ios::app);
                ac.getdetails();
                do{
               	ac.getamount();
               	try{
               		if(ac.retamount()<2000)
               		throw 1;
               		MessageBox(NULL, "ACCOUNT CREATED SUCCESSFULLY", "SUCCESSFUL", MB_OK);
               		outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
                	outFile.close();
				   }
				   catch(int i){
				   	 MessageBox(NULL, "DEPOSIT CANT BE LESS THAN 2000", "WARNING", MB_OK);
				   }
			   }while(ac.retamount()<2000);

			}

			void deposit_withdraw(int n, int option)
    		{

	        bool found=false;

	        File.open("saving.txt", ios::in|ios::out);
	        if(!File)
	        {
	            cout<<"\nFile could not be open !! Press any Key...";
	            return;
	        }
	        while(!File.eof() && found==false)
	        {
	            File.read(reinterpret_cast<char *> (&ac), sizeof(account));
	            if(ac.getacno()==n)
	            {
	                ac.showdetails();
	                if(option==1)
	                {
	                    cout<<"\n\n\tTO DEPOSITE AMOUNT ";
	                    cout<<"\n\nEnter The amount to be deposited:-";
	                    cin>>amt;
	                    ac.deposit(amt);
	                }
	                if(option==2)
	                {
	                    cout<<"\n\n\tTO WITHDRAW AMOUNT ";
	                    cout<<"\n\nEnter The amount to be withdraw:-";
	                    cin>>amt;
	                    ac.withdraw(amt);
	                }
	                int pos=(-1)*static_cast<int>(sizeof(ac));
	                File.seekp(pos,ios::cur);
	                File.write(reinterpret_cast<char *> (&ac), sizeof(account));
	                cout<<"\n\n\t Record Updated\n";
	                found=true;
	               }
	             }
	        File.close();
	        if(found==false)
	        cout<<"\n\n Record Not Found \n";
  		  }
  		   void modify_account(int n)
    {
        bool found=false;
        File.open("saving.txt",ios::in|ios::out);
        if(!File)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        while(!File.eof() && found==false)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(account));
            if(ac.getacno()==n)
            {
                ac.showdetails();
                cout<<"\nEnter The New Details of account"<<endl;
                ac.modify();
                int pos=(-1)*static_cast<int>(sizeof(account));
                File.seekp(pos,ios::cur);
                File.write(reinterpret_cast<char *> (&ac), sizeof(account));
                cout<<"\n Details Updated";
                found=true;
              }
        }
        File.close();
        if(found==false)
        cout<<"\n\n Record Not Found ";
    }
  	  void delete_account(int n)
    {
        inFile.open("saving.txt");
        if(!inFile)
        {
            cout<<"\nFile could not be open !! Press any Key...";
            return;
        }
        outFile.open("Temp.txt");
        inFile.seekg(0,ios::beg);
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
        {
            if(ac.getacno()!=n)
            {
                outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
            }
        }
        inFile.close();
        outFile.close();
        remove("saving.txt");
        rename("Temp.txt","saving.txt");
        cout<<"\n\n\tRecord Deleted ..\n";
    }
     void display_all()
    {

        inFile.open("saving.txt");
        if(!inFile)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        cout<<"\n\n\t\tSAVING ACCOUNT HOLDER LIST\n\n";
        cout<<"A/c no." <<"\t\t" <<" NAME"<<"\t\t"<< "Balance\n";
        cout<<"------------------------------------------------------\n";
        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
        {
            ac.report();
        }
        inFile.close();
    }
     void display_sp(int n)
            {
                bool flag=false;
                inFile.open("saving.txt");
                if(!inFile)
                {
                    cout<<"\nFile could not be open. Press any Key...";
                    return;
                }
                cout<<"\nBALANCE DETAILS\n";

                    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
                    {
                        if(ac.getacno()==n)
                        {
                            ac.showdetails();
                            cout<<"\n";
                            flag=true;
                        }
                    }
                inFile.close();
                if(flag==false)
                cout<<"\n\nINVALID ACCOUNT NUMBER\n";
        }
};
int main()
{
	int type,n;
	int ch;
	current c;
	saving s;
	system("color fc");
	do{
	cout<<"\n\t\tWELCOME TO BMS BANK";
	cout<<"\n\n1.CURRENT \n\n2.SAVING \n\n3.EXIT\n";
	cout<<"\n\nChoose the type of account:";
	cin>>type;
	switch(type)
	{
		case 1:system("cls");
				do{
				cout<<"\nCURRENT ACCOUNT";

				cout<<"\nRate of Interest\t\t4%";
				cout<<"\n\n1. CREATE A NEW ACCOUNT";
		        cout<<"\n\n2. DEPOSIT AMOUNT";
		        cout<<"\n\n3. WITHDRAW AMOUNT";
		        cout<<"\n\n4. BALANCE ENQUIRY";
		        cout<<"\n\n5. LIST OF ACCOUNTS";
		        cout<<"\n\n6. CLOSE AN ACCOUNT";
		        cout<<"\n\n7. MODIFY AN ACCOUNT";
		        cout<<"\n\n8. BACK TO MAIN MENU";
		        cout<<"\n\nEnter the choice:";
		        cin>>ch;
		        switch(ch)
		        {
		        	case 1:system("cls");
							c.getdetails();
		        			break;
		        	case 2:system("cls");
							cout<<"\nEnter The account No. : ";
							cin>>n;
               				 c.deposit_withdraw(n, 1);
               				 break;
               		case 3:system("cls");
					   		cout<<"\nEnter The account No. : ";
					   		 cin>>n;
               				 c.deposit_withdraw(n, 2);
               				 break;
               		case 4:system("cls");
					   		cout<<"\nEnter The account No. : ";
					   		cin>>n;
               			 c.display_sp(n);
               			 break;
               		case 5:	system("cls");
					   		c.display_all();
                            system("pause");
                            system("cls");
               				break;
               		case 6:system("cls");
					   		cout<<"\nEnter The account No. : ";
					   		cin>>n;
                			c.delete_account(n);
               			 break;
               		case 7:system("cls");
				   			cout<<"\nEnter The account No. : ";
					   		cin>>n;
               			 c.modify_account(n);
               			 break;
				}
				system("pasue");
				system("cls");
				cin.ignore();
				cin.get();
			}while(ch!=8);
				break;

		case 2:system("cls");
				do{

				cout<<"\n\nSAVING ACCOUNT";

				cout<<"\nRate of Interest\t7%";
				cout<<"\n\n1. CREATE A NEW ACCOUNT";
		        cout<<"\n\n2. DEPOSIT AMOUNT";
		        cout<<"\n\n3. WITHDRAW AMOUNT";
		        cout<<"\n\n4. BALANCE ENQUIRY";
		        cout<<"\n\n5. LIST OF ACCOUNTS";
		        cout<<"\n\n6. CLOSE AN ACCOUNT";
		        cout<<"\n\n7. MODIFY AN ACCOUNT";
		        cout<<"\n\n8.BACK TO MAIN MENU";
		        cout<<"\n\nEnter the choice:";
		        cin>>ch;
		        switch(ch)
		        {
		        	case 1:system("cls");

							s.getdetails();

		        			break;
		        	case 2:system("cls");
							cout<<"\nEnter The account No. : ";
							cin>>n;
               				 s.deposit_withdraw(n, 1);
               				 break;
               		case 3:system("cls");
					   		cout<<"\nEnter The account No. : ";
					   		 cin>>n;
               				 s.deposit_withdraw(n, 2);
               				 break;
               		case 4:system("cls");
					   cout<<"\nEnter The account No. : ";
					   		cin>>n;
               			 s.display_sp(n);
               			 break;
               		case 5:system("cls");
					   		s.display_all();


               				break;
               		case 6:system("cls");
					   		cout<<"\nEnter The account No. : ";
					   		cin>>n;
                		s.delete_account(n);
               			 break;
            case 7:system("cls");
					cout<<"\nEnter The account No. : ";
					   		cin>>n;
               			 s.modify_account(n);
               			 break;
				}
				system("pause");
				system("cls");
				cin.ignore();
				cin.get();
			}while(ch!=8);

				break;
		case 3:exit(0);
	}
		}while(type!=3);
}




