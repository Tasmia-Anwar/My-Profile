#include <iostream>
#include <conio.h>
#include <fstream>
#include <limits>
#include <string>
#include <queue>
using namespace std;

struct book 
{
    int bookno;
    string title;
    string author;
    int edition;
    bool isBorrowed;
    book *left, *right;
};

struct student
{
    int id;
    string name;
    string contact;
    student *adrs;
};

struct node
{  
    string data;  
	node* next;
	node(const string& name)
	{
	    data=name;
	    next=nullptr; 
	}
};

class Queue 
{  
private:  
    node* front;  
    node* rear;  

public: 
    Queue() 
	{
	    front = rear = nullptr;
	}

    void enqueue(const string& username)
	{  
        node *n = new node(username);  
        if(rear!=nullptr)
		{  
            rear->next=n;  
        }  
        else
        {  
            front=n;  
        }  
        rear=n; 
    }   

    string dequeue() 
	{  
        if(front==nullptr) 
		{  
		    cout<<"Queue is empty!"<<endl;  
            return "";    
        }  
        string username=front->data ;  
	    node* temp=front;  
        front=front->next;  
        if(front==nullptr) 
		{  
            rear=nullptr;   
        }  
        delete temp;   
        return username;  
    }   
       
    bool isEmpty() const
	{  
        return front==nullptr;  
    }  
	  
    ~Queue() 
	{  
        while(!isEmpty())
		{  
            dequeue();  
        }  
    }  
};  

class librarybooks
{
private:
    book *root;
	Queue waitingQueue; 
     
public:
    librarybooks()
	{
        root = nullptr;
        loadBooksFromFile();
    }
    
    ~librarybooks()
	{
    	saveBooksToFile();
	}
	
    book* getRoot()
    {
        return root;
    }

    void addbooks()
	{
        cout << "\n\t\t------ BOOK ENTERING ------\n";
        book* newBook=new book;
        while (true) 
        {
        	cout<<"\n\tEnter Book No: ";
            if(cin>>newBook->bookno&&newBook->bookno>0)
            {
                break;
            }
            else
            {
                cout<<"\n\tInvalid input! Please enter a numeric value for book no." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        cin.ignore();
        cout<<"\n\tEnter Book Name: ";
        getline(cin,newBook->title);
        cout<<"\n\tEnter Author Name: ";
        getline(cin, newBook->author);
        cout<<"\n\tEnter Edition: ";
        cin>>newBook->edition;
        newBook->isBorrowed=false;
        newBook->left=newBook->right=nullptr;

        if(root==nullptr)
		{
            root=newBook;
        } 
		else
		{
            insertBook(root, newBook);
        }
        cout<<"\n\tBook Added Successfully.\n";
        saveBooksToFile();
    }

    void insertBook(book* current, book* newBook) 
	{
        if (newBook->bookno<current->bookno)
		{
            if (current->left==nullptr)
			{
                current->left=newBook;
            } 
			else
			{
                insertBook(current->left, newBook);
            }
        }
		else
		{
            if(current->right==nullptr) 
			{
                current->right=newBook;
            } 
			else 
			{
                insertBook(current->right, newBook);
            }
        }
    }
    
    void inOrderTraversal(book* current)
	{
        if (current!=nullptr) 
		{
            inOrderTraversal(current->left);
            cout<<"\n";
            cout<<"\n\tBook No: "<<current->bookno;
            cout<<"\n\tBook Name: "<<current->title;
            cout<<"\n\tBook Author: "<<current->author;
            cout<<"\n\tBook Edition: "<<current->edition;
            inOrderTraversal(current->right);
        }
    }

    void displaybooks()
	{
        if(root==nullptr) 
		{
            cout<<"\n\tNo books available.\n";
            return;
        }
        inOrderTraversal(root);
    }
    
    book* searchBook(book* root, int bookno)
	{  
        book* current=root; 
        while (current != nullptr)
		{  
            if(current->bookno==bookno)
			{  
                return current;  
            } 
			else if(bookno<current->bookno) 
			{    
                current=current->left;  
            }
	    	else
	      	{  
                current=current->right;  
            }  
        }  
        return nullptr; 
    }

    void updatebooks()
	{
        int bookno;
        while (true)
		{
            cout<<"\n\tEnter Book No: ";
            if(cin>>bookno&&bookno>0)
            {
                break;
            }
            else
            {
                cout<<"\n\tInvalid input!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        book* current=root;
        while (current!=nullptr)
	    {  
            if (current->bookno==bookno)
		    {  
                cin.ignore(); 
                cout<< "\n\tEnter New Book Name: ";  
                getline(cin,current->title);  
                cout<<"\n\tEnter New Author Name: ";  
                getline(cin,current->author);  
                cout<<"\n\tEnter New Book Edition: ";  
                cin>>current->edition;  
                cout<<"\n\tBook Updated Successfully.\n";  
                return;
            }
		    else if (bookno < current->bookno) 
			{    
                current=current->left;  
            }
	    	else
	      	{  
                current=current->right;  
            }  
        }  
        cout<<"\n\tBook not found.\n";
    }
    
    book* deleteBook(book* current, int bookno) 
	{
        if (current == nullptr) 
		{
            cout<<"\n\tBook not found.\n";
            return current;
        }
        if (bookno<current->bookno) 
		{
            current->left=deleteBook(current->left,bookno);
        } 
		else if (bookno>current->bookno)
		{
            current->right=deleteBook(current->right,bookno);
        }
		else
		{
            if (current->left==nullptr)
			{
                book* temp=current->right;
                delete current;
                return temp;
            }
			else if (current->right==nullptr) 
			{
                book* temp = current->left;
                delete current;
                return temp;
            }
			else
			{
                book* temp = minValueNode(current->right);
                current->bookno = temp->bookno;
                current->title = temp->title;
                current->author = temp->author;
                current->edition = temp->edition;
                current->right = deleteBook(current->right, temp->bookno);
            }
        }
        return current;
    }

    book* minValueNode(book* current)
	{
        book* currentNode = current;
        while (currentNode && currentNode->left != nullptr)
		{
            currentNode = currentNode->left;
        }
        return currentNode;
    }

    void deletebooks() 
	{
        int bookno;
        while (true)
		{
            cout<<"\n\tEnter Book no to Delete: ";
            if(cin>>bookno&&bookno>0)
            {
                break;
            }
            else
            {
                cout<<"\n\tInvalid input!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        root=deleteBook(root,bookno);
    }

    void borrowbooks()
	{
        int bookno;
        string username;
        while (true)
		{
            cout<<"\n\tEnter Book No to borrow: ";
            if(cin>>bookno&&bookno>0)
            {
                break;
            }
            else
            {
                cout<<"\n\tInvalid input!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        cin.ignore();
        cout<<"\n\tEnter your name: ";
        getline(cin,username);

        book* Borrowbook=searchBook(root,bookno);
        if (Borrowbook!=nullptr) 
		{
            if (!Borrowbook->isBorrowed)
			{
                Borrowbook->isBorrowed=true;
                cout<<"\n\tBook Borrowed Successfully by "<<username<<".\n";
            } 
			else 
			{
                cout<<"\n\tBook is already borrowed. Adding "<<username<<" to the waiting list.\n";
                waitingQueue.enqueue(username);
            }
        } 
		else 
		{
            cout<<"\n\tBook not found.\n";
        }
    }
    
    void inOrderBorrowed(book* current,bool &found)
	{
        if (current!=nullptr)
		{
            inOrderBorrowed(current->left,found);
            if(current->isBorrowed)
			{
                found = true;
                cout<<endl;
                cout<<"\n\tBook No: "<<current->bookno;
                cout<<"\n\tBook Name: "<<current->title;
                cout<<"\n\tBook Author: "<<current->author;
                cout<<"\n\tBook Edition: "<<current->edition;
            }
            inOrderBorrowed(current->right,found);
        }
    }
 
    void borrowrecord()
	{
        cout<<"\n\t\t------ Borrowed Books ------\n";
        bool found=false;
        inOrderBorrowed(root,found);
        if(!found)
	    {
            cout<<"\n\tNo books are currently borrowed.\n";
        }
    }

    void returnbooks(){
        int bookno;
        while (true) 
        {
        	cout<<"\n\tEnter Book no to return: ";
            if(cin>>bookno&&bookno>0)
            {
                break;
            }
            else
            {
                cout<<"\n\tInvalid input!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        
        book* returnbook=searchBook(root,bookno);
        if (returnbook!=nullptr) 
		{
            if (returnbook->isBorrowed)
			{
                returnbook->isBorrowed=false;

                if (!waitingQueue.isEmpty())
				{
                    string nextUser=waitingQueue.dequeue();
                    returnbook->isBorrowed=true; 
                    cout<<"\n\tBook returned successfully. Borrowed by "<<nextUser<<".\n";
                } 
				else 
				{
                    cout<<"\n\tBook returned successfully.\n";
                }
            }
			else
			{
                cout<<"\n\tThis book was not borrowed.\n";
            }
        }
		else
		{
            cout<<"\n\tBook not found.\n";
        }
    }
    
    void saveBooksToFile()
	{
        ofstream file("Book.txt");
        saveBooksToFileHelper(root,file);
        file.close();
    }

    void saveBooksToFileHelper(book* current,ofstream &file)
	{
        if (current!=nullptr) 
		{
            file<<current->bookno<<endl 
			    <<current->title<<endl 
			    <<current->author<<endl 
			    <<current->edition<<endl 
			    <<current->isBorrowed<<endl;
            saveBooksToFileHelper(current->left,file);
            saveBooksToFileHelper(current->right,file);
        }
    }

    void loadBooksFromFile()
	{
        ifstream file("Book.txt");
        if (!file)
		{
            cout<<"\n\tNo previous book records found.\n";
            return;
        }
        while (true)
		{
            book* newBook=new book;
            file>>newBook->bookno;
            if (file.fail())
			  break;
            file.ignore();
            getline(file,newBook->title);
            getline(file,newBook->author);
            file>>newBook->edition>>newBook->isBorrowed;
            newBook->left=newBook->right=nullptr;
            if (root==nullptr)
			{
                root=newBook;
            }
			else
			{
                insertBook(root,newBook);
            }
        }
    file.close();
    }
};

class librarystudents{
private:
    student *ss,*sc,*sn; 

public:
    librarystudents()
	{
        ss = sc = sn= nullptr; 
        loadStudentsFromFile();
    }

    ~librarystudents()
	{
        saveStudentsToFile();
    }

    void addstudents()
	{
        cout<<"\n\t\t----- STUDENTS ENTRY -----\n";
        student *sn=new student;
        while (true) 
        {
        	cout<<"\n\tEnter Student Id: ";
            if(cin>>sn->id&&sn->id>0)
            {
                break;
            }
            else
            {
                cout<<"\n\tInvalid input!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        cin.ignore();
        cout<<"\n\tEnter Student Name: ";
        getline(cin, sn->name);
        cout<<"\n\tEnter Student Contact: ";
        getline(cin, sn->contact);
        sn->adrs=nullptr;

        if (ss==nullptr)
		{
            ss=sn;
        }
		else 
		{
            student *sc=ss;
            while (sc->adrs!=nullptr)
			{
                sc=sc->adrs;
            }
            sc->adrs=sn; 
        }
        cout<<"\n\tStudent Added Successfully.\n";
        saveStudentsToFile();
    }

    void displaystudents()
	{
        if (ss==nullptr)
	    {
            cout<<"\n\tNo Student Available.\n";
            return;
        }
        student *sc=ss;
        while (sc!=nullptr)
		{
        	cout<<"\n";
            cout<<"\n\tStudent Id: "<<sc->id;
            cout<<"\n\tStudent Name: "<<sc->name;
            cout<<"\n\tStudent Contact: "<<sc->contact;
            sc=sc->adrs;
        }
    }
    
	void searchstudents()
	{
		if(ss==nullptr)
		{
            cout<<"\n\tNo Student available.\n ";
		    return;
        }
		int id;
		while (true)
		{
            cout<<"\n\tEnter Student ID to Search: ";
            if(cin>>id&&id>0)
            {
                break;
            }
            else
            {
                cout<<"\n\tInvalid input!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        student *sc=ss;
	    while(sc!=nullptr)
	    {
		    if(sc->id==id)
			{
		        cout<<"\n\tStudent Searched.\n ";
		        cout<<"\n\tStudent Id: "<<sc->id;
		   	    cout<<"\n\tStudent Name: "<<sc->name;
		        cout<<"\n\tStudent Contact: "<<sc->contact;
		   	    return;
     	    }
	    sc=sc->adrs;
		}
		cout<<"\n\tStudent Not Found.\n";
	}    	

    void updatestudents()
	{
        if (ss==nullptr)
		{
            cout<<"\n\tNo Student Available.\n";
            return;
        }
        int id;
        while (true)
		{
            cout<<"\n\tEnter Student ID to Update: ";
            if(cin>>id&&id>0)
            {
                break;
            }
            else
            {
                cout<<"\n\tInvalid input!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        cin.ignore();
        student *sc=ss;
        while (sc!=nullptr)
		{
            if (sc->id==id)
			{
			    cout<<"\n";
                cout<<"\n\tEnter New Student Name: ";
                getline(cin,sc->name);
                cout<<"\n\tEnter New Student Contact: ";
                getline(cin,sc->contact);
                cout<<"\n\tStudent Updated Successfully.\n";
                saveStudentsToFile();
                return;
            }
            sc=sc->adrs;
        }
        cout<<"\n\tStudent Not Found.\n";
    }

    void deletestudents()
	{
        if (ss==nullptr) 
		{
            cout<<"\n\tNo Student Available.\n";
            return;
        }
        int id;
        while (true)
		{
            cout<<"\n\tEnter Student ID to Delete: ";
            if(cin>>id&&id>0)
            {
                break;
            }
            else
            {
                cout<<"\n\tInvalid input!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        student *prev = nullptr;
        student *current=ss;
        while (current!=nullptr)
		{
            if (current->id==id)
			{
                if (prev==nullptr)
                    ss=current->adrs; 
				else
                    prev->adrs=current->adrs;
                delete current;
                cout<<"\n\tStudent Deleted Successfully.\n";
                saveStudentsToFile();
                return;
            }
            prev=current;
            current=current->adrs;
        }
        cout<<"\n\tStudent Not Found.\n";
    }

    void saveStudentsToFile() {
        ofstream file("Student.txt");
        if (!file)
		{
            cout<<"\n\tError saving students to file.\n";
            return;
        }
        student *sc=ss;
        while (sc!=nullptr)
		{
            file<<sc->id<<"\n"
                <<sc->name<<"\n"
                <<sc->contact<<"\n";
            sc=sc->adrs;
        }
        file.close();
    }

    void loadStudentsFromFile() {
        ifstream file("Student.txt");
        if (!file) {
            cout << "\n\tNo Previous Student Records Found.\n";
            return;
        }
        while (true)
		{
            student *sn=new student;
            file>>sn->id;
            if (file.fail())
			{
                delete sn; 
                break;
            }
            file.ignore();
            getline(file,sn->name);
            getline(file,sn->contact);
            sn->adrs=nullptr;

            if (ss==nullptr)
			{
                ss=sn;
            }
			else 
			{
                student *sc=ss;
                while (sc->adrs!=nullptr) 
				{
                    sc=sc->adrs;
                }
                sc->adrs=sn;
            }
        }
        file.close();
    }
};


int main()
{
	librarybooks l1;
	librarystudents s1;
	int ch,ch1,ch2;
	string adminName = "admin"; 
    string adminPassword = "12345";
    string name, password;
        cout<<"\n\n\n";
        cout<<"\t\t\t\t\t================================================\n";
        cout<<"\t\t\t\t\t------------------- PROJECT --------------------\n";
        cout<<"\t\t\t\t\t--------- LIBRARY MANAGEMENT SYSTEM-------------\n";
        cout<<"\t\t\t\t\tSUBMITTED BY:\n";
        cout<<"\t\t\t\t\t\tSania fiaz\t(23021519-024)\n";
        cout<<"\t\t\t\t\t\tTasmia Anwar\t(23021519-131)\n";
        cout<<"\t\t\t\t\tSUBMITTED TO:\n";
		cout<<"\t\t\t\t\t\tMAM AYESHA\n";
        cout<<"\t\t\t\t\tCOURSE CODE:\n";
		cout<<"\t\t\t\t\t\tCS203\n";
        cout<<"\t\t\t\t\t------------UNIVERSITY OF GUJRAT-----------------\n";
        cout<<"\t\t\t\t\t=================================================\n";
	do
	{
	cout<<"\n\n";
	cout<<"\t\t\t\t\t=================================================\n";
	cout<<"\t\t\t\t\t------------------ WELCOME TO -------------------\n";
	cout<<"\t\t\t\t\t---------- LIBRARY MANAGEMENT SYSTEM ------------\n ";
	cout<<"\t\t\t\t\t=================================================\n\n";
	cout<<"\t1. Admin \n\n";
	cout<<"\t2. Student \n\n";
	cout<<"\t3. Close Application \n\n";
	cout<<"\t4. Exit \n\n";
	
	    while (true) 
        {
        	cout<<"\n\tEnter your Choice. ";
            if(cin>>ch&&ch>0)
            {
                break;
            }
            else
            {
                cout<<"\n\tInvalid input!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        
	switch(ch)
	{
    case 1:
    	cout<<"\n\tEnter Admin Username: ";
        cin>>name;
        cout<<"\n\tEnter Admin Password: ";
        password.clear();
        while (true)
        {
        ch = _getwch();
        if (ch == '\r')
           break;
        if (ch == '\b')
        {
           if (!password.empty())
		   {
               password.pop_back();
               cout << "\b \b";
           }
        }
        else 
	       {
               password += ch;
               cout << '*';
           }
        }
    	if(name==adminName&&password==adminPassword)
        {
           system("cls");
	       cout<<"\n\t\n\t\t------------- Login Successful ------------\n";
    	do
		{	
    	cout<<"\n\n";
		cout<<"\t\t===========================================\n";
	    cout<<"\t\t---------- WELCOME TO ADMIN MENU ----------\n";
        cout<<"\t\t===========================================\n\n";
        cout<<"\t1. Add Books \n\n";
    	cout<<"\t2. Update Books \n\n";
	    cout<<"\t3. Delete specific Book \n\n";
	    cout<<"\t4. Diplay all Books \n\n";
	    cout<<"\t5. Add Students \n\n";
	    cout<<"\t6. Search Students \n\n";
	    cout<<"\t7. Update Students \n\n";
	    cout<<"\t8. Delete specific Student \n\n";
	    cout<<"\t9. Display all Students \n\n";
	    cout<<"\t10. Display Borrow Record \n\n";
	    cout<<"\t11. Back to Main Menu \n\n";

	    while (true) 
        {
        	cout<<"\n\tEnter your choice: ";
            if(cin>>ch1&&ch1>0)
            {
                break;
            }
            else
            {
                cout<<"\n\tInvalid input!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
	    system("cls");
			if(ch1==1)
			{
			   int choice;
			   while (true) 
               {
        	        cout<<"\n\tHow many Books you want to Add: ";
                    if(cin>>choice&&choice>0)
                    {
                       break;
                    }
                    else
                    {
                        cout<<"\n\tInvalid input!"<<endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    }   
                } 
			   for(int i=1;i<=choice;i++)
		           l1.addbooks();
		    }
		    else if(ch1==2)
			   l1.updatebooks();
			else if(ch1==3)
			   l1.deletebooks();
			else if(ch1==4)
			   l1.displaybooks();
			else if(ch1==5)
			{
			   int choice;
			   while (true) 
               {
        	        cout<<"\n\tHow many Students you want to Add: ";
                    if(cin>>choice&&choice>0)
                    {
                       break;
                    }
                    else
                    {
                        cout<<"\n\tInvalid input!"<<endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    }   
                }      
			    for(int i=1;i<=choice;i++)
			       s1.addstudents();
			} 
			else if(ch1==6)
			   s1.searchstudents();
			else if(ch1==7)   
			   s1.updatestudents();  
			else if(ch1==8)   
			   s1.deletestudents();
		    else if(ch1==9)
			   s1.displaystudents();
			else if(ch1==10)
			   l1.borrowrecord();
			else if(ch1==11)
			   cout<<"\n\n\tReturn to Main Menu\n";
			else
			   cout<<"\tInvalid choice. Try Again!\n";
        	}
	    while(ch1!=11);
    	}
    	else
        {
            cout<<"\n\n\tInvalid Admin Username or Password.\n";
        }
	    break;
	    
    case 2:
    	system("cls");
        do
		{
        cout<<"\n\n";
		cout<<"\t\t=============================================\n";
	    cout<<"\t\t---------- WELCOME TO STUDENT MENU ----------\n";
	    cout<<"\t\t=============================================\n\n";
	    cout<<"\t1. View Books \n\n";
	    cout<<"\t2. Search Book \n\n";
	    cout<<"\t3. Borrow Book \n\n";
	    cout<<"\t4. Return Book \n\n";
	    cout<<"\t5. Back to Main Menu\n\n";
	
    	while (true) 
        {
        	cout<<"\n\tEnter your Choice. ";
            if(cin>>ch2&&ch2>0)
            {
                break;
            }
            else
            {
                cout<<"\n\tInvalid input!"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        
    	system("cls");
		    if(ch2==1)
		       l1.displaybooks();
		    else if(ch2==2)
		    {
		        int bookno;
		        while (true) 
                {
        	        cout<<"\n\tEnter Book No to search: ";
                    if(cin>>bookno&&bookno>0)
                    {
                        break;
                    }
                    else
                    {
                        cout<<"\n\tInvalid input!"<<endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    }
                }
                book* foundBook=l1.searchBook(l1.getRoot(), bookno); 
                if(foundBook!=nullptr)
				{
                    cout<<"\n\tBook Searched\n";
                    cout<<"\n\tBook No: "<<foundBook->bookno;
                    cout<<"\n\tBook Name: " <<foundBook->title;
                    cout<<"\n\tBook Author: "<<foundBook->author;
                    cout<<"\n\tBook Edition: " <<foundBook->edition;
                } 
				else
				{
                    cout<<"\n\tBook not found.\n";
                }	 
		    }
		    else if(ch2==3)   
			   l1.borrowbooks();
			else if(ch2==4)
			    l1.returnbooks();
		    else if(ch2==5)  
			   cout<<"\n\n\tReturn to Main Menu\n";
			else
			   cout<<"\tInvalid choice. Try Again!\n";
    	} 
		while(ch2!=5);
		break; 
		
	case 3:
		system("cls");
	    cout<<"\n\n\n\n\n\n\t\t Save data and close the Application.... \n\n\n\n\n\n\n";
	    l1.saveBooksToFile();
	    s1.saveStudentsToFile();
	    exit(0);
            
	case 4:
	    system("cls");
	    cout<<"\n\n\n\n\n";
		cout<<"\t\t===============================================\n";
	    cout<<"\t\t---------- EXITING SYSTEM. GOODBYE! -----------\n";
	    cout<<"\t\t===============================================\n";
		cout<<"\n\n\n\n\n\n";
        break;
            
    default:
	    cout<<"Invalid Choice. Try Again!\n";
		}
	}
    while(ch!=4);
    return 0;  
}
