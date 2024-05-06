#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void EnterToComtinue();

struct Items
{
    int code;
    string name;
    double price;
    Items *next;
};

struct orderItems
{
    int code, qty;
    string name;
    double price,total = 0;
    orderItems *next;
};

class AdminManage{
    private:
    Items *head = NULL, *tail = NULL;
    Items *sorted = NULL;
    public:
    AdminManage()
    {
        head = new Items;
        double p[] = {12.88,26.99,45.99,55.50,60.5,69.9,60.9,64.88,44.9,39.9};//
        string n[] = {"Donut","Croissant","Ham & Cheese Croissant","Pain au raisin","French Tiramisu","Matcha Cake","Black Forest Cake","Red Velvet Cake","Double Chocolate Cookies","Chocolate Chip Cookies"};
        int c[] = {1001,1002,1003,1004,1005,1006,1007,1008,1009,1010};
        Items *temp = head, *ins;
        head->price = p[0];
        head->code = c[0];
        head->name = n[0];
        head->next = NULL;
        temp = tail = head;
        
        for(int i = 1 ; i < sizeof(c)/sizeof(c[0]); i++)
        {
            ins = new Items;
            ins->price = p[i];
            ins->code = c[i];
            ins->name = n[i];
            ins->next = NULL;
            temp->next = ins;
            temp = temp->next;
            tail = ins;
        } 
    }

    int empty()
    {
        if(head == NULL)
        {return 1;}
        else
        {return 0;}
    }

    int existing(int code){
        Items *temp = head;
        while(temp != NULL)
        {
            if(temp->code == code)
            {
                return 1;
            }
            temp = temp->next;
        }
        return 0;
    }

    Items* search(int code)
    {
        Items *temp = head;
        while(temp->code != code)
        {
            temp = temp->next;
        }
        return temp;
    }

    void swap(Items *node_1, Items *node_2)
    {
        int tempcode = node_1->code;
        string tempname = node_1->name;
        double tempprice = node_1->price;

        node_1->code = node_2 -> code;
        node_2 -> code = tempcode;

        node_1->name = node_2 -> name;
        node_2 ->name = tempname;

        node_1->price = node_2 -> price;
        node_2 -> price = tempprice; 
    }

    void sort(Items *head) //using bubble sort
    {
        int swapped;

        Items *lPtr; // left pointer will always point to the start of the list
        Items *rPrt = NULL; // right pointer will always point to the end of the list

        do
        {	
            swapped = 0;
            lPtr = head;
            while(lPtr->next != rPrt)
            {
                if (lPtr->code > lPtr->next->code) 
                {
                    swap(lPtr, lPtr->next); 
                    swapped = 1; 
                }
                lPtr = lPtr->next;
            }
            //as the largest element is at the end of the list, assign that to rPtr as there is no need to
            //check already sorted list
            rPrt = lPtr;

        }while(swapped);
    }

    void add(){
        Items *temp = head;
        int code;
        if (!empty())
        {   
            cout << "\n";
            cout << "  +---------------------------+" << endl;
            cout << "  |                           |" << endl;
            cout << "  |    Pastry Item Adding     |" << endl;
            cout << "  |                           |" << endl;
            cout << "  +---------------------------+" << endl;
            cout<<"\nEnter code (Input 99 to exit adding mode): ";
            cin>>code;
            cin.sync();
            do
            {
                if(code == 99)
                    {
                        cout<<"Exiting adding process..."<<endl;
                        break;
                    } //break from the loop

                if(!existing(code))
                {
                    string *n = new string;
                    double *p = new double;
                    Items *ins = new Items;
                    cout<<"\nEnter item name: ";
                    getline(cin, *n);
                    cin.sync();
                    cout<<"Enter item price: ";
                    cin>>*p;
                    cin.sync();

                    ins->code = code;
                    ins->name = *n;
                    ins->price = *p;
                    ins->next = NULL;
                    
                    tail->next = ins;
                    tail = ins;

                    cout<<"\n|========================================================|"<<endl;
                    cout<<"|               ITEM SUCCESSFULLY ADDED                  |"<<endl;
                    cout<<"|========================================================|"<<endl;
                    cout<<"  Item Code  : "<<ins->code<<endl;
                    cout<<"  Item Name  : "<<ins->name<<endl;
                    cout<<"  Item Price : "<<ins->price<<endl;
                    cout<<"|========================================================|"<<endl<<endl;

                    EnterToComtinue();

                    break;
                }
                else{
                    cout<<"\nThe code entered is an existing item in the list..."<<endl;
                    cout<<"Please enter another code. (Input 99 to exit adding mode)"<<endl;
                    cout<<"\nEnter code: ";
                    cin>>code;
                    cin.sync();
                }
            }while(true); 
        }
        else{

            cout<<"\n\n========================================"<<endl;
            cout<<"|         Pastry List is Empty.        |"<<endl;
            cout<<"|       Going back to main menu.       |"<<endl;
            cout<<"========================================"<<endl;

            EnterToComtinue();
        }
        
        sort(head);
    }

    void remove(){
        Items *temp = head;
        int code;
        char choice;
        if (!empty())
        {
            cout << "\n";
            cout << "  +---------------------------+" << endl;
            cout << "  |                           |" << endl;
            cout << "  |   Pastry Item Delete      |" << endl;
            cout << "  |                           |" << endl;
            cout << "  +---------------------------+" << endl;
            cout<<"\nPlease enter the item code that you want to remove..."<<endl;
            cout<<"\nEnter code (Input 99 to exit deleting mode): ";
            cin>>code;
            cin.sync();
            do
            {
                if(code == 99)
                {
                    cout<<"Exiting deleting process..."<<endl;
                    break;
                } //break from the loop

                if(existing(code))
                {
                    cout<<"\nAre you sure that you want to remove this item from the Item's list?"<<endl;
                    cout<<"Enter Choice [Y-Yes || N-No] : ";
                    cin>>choice;
                    cin.sync();

                    if(choice == 'Y' || choice == 'y')
                    {
                        Items *prev;
                        while(temp->code != code)
                        {
                            prev = temp;
                            temp = temp->next;
                        }//to find which linked list is the code is located

                        cout<<"\n|========================================================|"<<endl;
                        cout<<"|               ITEM SUCCESSFULLY REMOVED                |"<<endl;
                        cout<<"|========================================================|"<<endl;
                        cout<<"  Item Code  : "<<temp->code<<endl;
                        cout<<"  Item Name  : "<<temp->name<<endl;
                        cout<<"  Item Price : "<<temp->price<<endl;
                        cout<<"|========================================================|"<<endl;//delete successful message

                        if (temp == head) {
                            head = temp->next;
                            delete temp;
                        } else if (temp->next == NULL) {
                            prev->next = NULL;
                            tail = prev;
                            delete temp;
                        } else {
                            prev->next = temp->next;
                            delete temp;
                        }
                        
                        EnterToComtinue();
                        break;
                    }
                    else{
                        cout<<"\n\nItem deletion cancelled..."<<endl;
                        cout<<"Returning to Admin menu."<<endl;
                        EnterToComtinue();
                        break;
                    }
                }
                else{
                    cout<<"\n\nThe code you've entered does not exist in the list...\nPlease enter an existing code."<<endl;
                    cout<<"Enter code (Input 99 to exit deleting mode): ";
                    cin>>code;
                }
            }while(true);
        }
        else{
            cout<<"\n\n========================================"<<endl;
            cout<<"|         Pastry List is Empty.        |"<<endl;
            cout<<"|       Going back to main menu.       |"<<endl;
            cout<<"========================================"<<endl;
        }
    }

    void edit(){
        Items *temp = head;
        bool cont = true;
        int *c = new int, *holdcode = new int;
        string *n = new string, *holdname = new string;
        double *p = new double, *holdprice  = new double;
        int choice;

        if (!empty())
        {
            cout << "  +---------------------------+" << endl;
            cout << "  |                           |" << endl;
            cout << "  |     Pastry Item Edit      |" << endl;
            cout << "  |                           |" << endl;
            cout << "  +---------------------------+" << endl;
            cout<<"\nPlease enter the item code that you want to edit..."<<endl;
            cout<<"\nEnter code (Input 99 to exit editing mode): ";
            cin>>*c;
            cin.sync();
            do
            {
                if(*c == 99)
                {
                    cout<<"Exiting editing process..."<<endl;
                    break;
                } //break from the loop

                if(existing(*c))
                {
                    while(temp->code != *c)
                        {
                            temp = temp->next;
                        }//to find which linked list is the code is located

                    cout<<"\nWhat do you wish to edit?"<<endl;
                    cout<<"---------------"<<endl;
                    cout<<"|1. Item Code |\n|2. Item Name |\n|3. Item Price|\n";
                    cout<<"---------------"<<endl;
                    cout<<"\nEnter choice (Input 99 to cancel): ";
                    cin>>choice;
                    cin.sync();
                    switch (choice)
                    {
                    case 1:
                        cout<<"What would you like to change the code to?\n\nEnter code: ";
                        cin>>*c;
                        cin.sync();
                        
                        do
                        {
                            if(!existing(*c))
                            {
                                *holdcode = temp->code;
                                temp->code = *c;
                                cont = false;
                                cout<<"\n=================================="<<endl;
                                cout<<"| ITEM CODE SUCCESSFULLY EDITED! |"<<endl;
                                cout<<"=================================="<<endl;
                                cout<<*holdcode<<" => "<<temp->code<<endl;
                                break;
                            }
                            else{
                                if(*c == temp->code)
                                {
                                    cout<<"\n\n|========================================================|"<<endl;
                                    cout<<"|              ITEM CODE EDIT UNSUCCESSFUL               |"<<endl;
                                    cout<<"|========================================================|"<<endl;
                                    cout<<"| Reason = Code is the same as the current pastry code.  |"<<endl;
                                    cout<<"|========================================================|"<<endl<<endl;
                                    cont = false;
                                    break;

                                }
                                else{
                                    display();
                                    cout<<"\n\n|========================================================|"<<endl;
                                    cout<<"|                  EXISTING CODE DETECTED                |"<<endl;
                                    cout<<"|========================================================|"<<endl<<endl;
                                    
                                    cout<<"Please enter another code.\n\nEnter Code (Input 99 to cancel): ";
                                    cin>>*c; 
                                }

                                if(*c == 99)
                                {
                                    cout<<"\n\nExiting editing process..."<<endl;
                                    cont = false;
                                    break;
                                } //break from the loop

                            }
                        }while (true);
                        sort(head);
                        cin.sync();
                        
                        EnterToComtinue();
                    break;

                    case 2:
                        cout<<"What would you like to change the pastry name to?\nEnter pastry name: ";
                        getline(cin, *n);
                        cin.sync();
                        if(*n != temp->name)
                        {
                            *holdname = temp->name;
                            temp->name = *n;
                            cont = false;
                            cout<<"\n=================================="<<endl;
                            cout<<"| ITEM NAME SUCCESSFULLY EDITED! |"<<endl;
                            cout<<"=================================="<<endl;
                            cout<<"\t  Item code = "<<temp->code<<endl;
                            cout<<"=================================="<<endl;
                            cout<<*holdname<<" => "<<temp->name<<endl;
                        }
                        else{
                            cont = false;
                            cout<<"\n|========================================================|"<<endl;
                            cout<<"|              ITEM NAME EDIT UNSUCCESSFUL               |"<<endl;
                            cout<<"|========================================================|"<<endl;
                            cout<<"|Reason = New name is the same as the current item name. |"<<endl;
                            cout<<"|========================================================|"<<endl;
                        }
                        EnterToComtinue();
                    break;

                    case 3:
                        cout<<"What would you like to change the price to?\nEnter price: ";
                        cin>>*p;
                        cin.sync();
                        if(*p != temp->price)
                        {
                            *holdprice = temp->price;
                            temp->price = *p;
                            cont = false;
                            cout<<"\n==================================="<<endl;
                            cout<<"| ITEM PRICE SUCCESSFULLY EDITED! |"<<endl;
                            cout<<"==================================="<<endl;
                            cout<<"\t  Item code = "<<temp->code<<endl;
                            cout<<"==================================="<<endl;
                            cout<<" RM "<<*holdprice<<" => "<<"RM "<<temp->price<<endl;
                            cout<<"==================================="<<endl;
                        }
                        else{
                            cont = false;
                            cout<<"\n|=========================================================|"<<endl;
                            cout<<"|              ITEM PRICE EDIT UNSUCCESSFUL               |"<<endl;
                            cout<<"|=========================================================|"<<endl;
                            cout<<"|Reason = New price is the same as the current item price.|"<<endl;
                            cout<<"|=========================================================|"<<endl;
                        }

                        EnterToComtinue();
                    break;

                    case 99:
                        cont = false;
                        cout<<"Cancelling editing...\nReturning to main menu.\n";
                    break;

                    default:
                    cout<<"\n|===============================|"<<endl;
                    cout<<"|Invalid Choice...              |\n|Please enter your choice again.|";
                    cout<<"\n|===============================|"<<endl;
                    break;
                    }
                }
                else{
                    cout<<"\nThe code you've entered does not exist in the list...\nPlease enter an existing code."<<endl;
                    cout<<"\nEnter code (Input 99 to exit editing mode): ";
                    cin>>*c;
                }
            }while(cont);
            
        }
        else{
            cout<<"\n\n========================================"<<endl;
            cout<<"|         Pastry List is Empty.        |"<<endl;
            cout<<"|       Going back to main menu.       |"<<endl;
            cout<<"========================================"<<endl;
        }

        delete c,n,p;
    }

    void display()
    {
        Items *temp = head;
        cout<<"\n\n-------------------------------------------------------"<<endl;
        cout<<left<<setw(8)<<"|Code"<<left<<setw(35)<<"| Pastry Name"<<left<<setw(12)<<"|Price (RM)|"<<endl;
        cout<<"-------------------------------------------------------"<<endl;
        while(temp != NULL)
        {
            cout<<" "<<fixed<<left<<setw(9)<<temp->code<<left<<setw(34)<<temp->name<<left<<setw(13)<<setprecision(2)<<temp->price<<"\n";
            temp = temp->next;
        }
        cout<<"-------------------------------------------------------"<<endl;
    }
    //add done
    //delete done
    //edit done
    //check empty
    //check existing done
    //search and return address done
    //display done
}itemlist; //declare itemlist as global class


class Customer{
    private:
    orderItems *cart = NULL, *tail; //stores itemcode, item name and item price
    
    string PayMethod;
    double price, total, tax;
    int ordernum, qty, x;
    char yes;
    public:
        string name, phone, email;
        bool status = false;
        bool paid = false;
        Customer()
        {
            name = " ";
            phone = " ";
            email = " ";
            PayMethod = " ";
            ordernum = 0;
            qty = 0;
            x = 0;
        }

        void display_entered()
        {
            
            cout << "\n========================================" << endl;
            cout << "|          Customer Information        |" << endl;
            cout << "========================================" << endl;
            cout << "  Name               : " << name << endl;
            cout << "  Phone Number       : " << phone << endl;
            cout << "  Email Address      : " << email << endl;
            cout << "========================================" << endl;

        }

        void getcustomerinfo()
        {
            cout << "\n\n==============================" << endl;
            cout << "|    Customer Information    |" << endl;
            cout << "==============================" << endl;

            cout << "Enter Name          : ";
            getline(cin, name);
            cin.sync();

            cout << "Enter Phone Number  : ";
            getline(cin, phone);
            cin.sync();

            cout << "Enter Email Address : ";
            getline(cin, email);
            cin.sync();
            
            // Display entered information
            system("cls");
            display_entered();
            status = true;
        }
    	void order(){
        cout << "\n";
            cout << "  +---------------------------+" << endl;
            cout << "  |                           |" << endl;
            cout << "  |      Pastry Ordering      |" << endl;
            cout << "  |                           |" << endl;
            cout << "  +---------------------------+" << endl;
    	do{
            bool dupe = false;
	        cout << "\nEnter code (Input 99 to exit ordering mode): ";
	        cin >> ordernum;
	        cin.sync();

	        if (ordernum == 99) {
	            cout << "\nExiting ordering process...\n" << endl;
                break;
	        }

            if(itemlist.existing(ordernum))
            {
                cout<<"\nEnter quantity (1 and Above) : ";
                cin>>qty;
                cin.sync();

                while(qty <= 0)
                {
                    cout<<"\nPlease enter the correct quantity.\nEnter quantity (1 and Above) : ";
                    cin>>qty;
                    cin.sync();
                }

                Items* itemToAdd = itemlist.search(ordernum);

                if (itemexist(ordernum))
                {
                    orderItems *temp = cart;
                    while(temp->code != ordernum)
                    {
                        temp = temp->next;
                    }
                    temp->qty = qty;
                    dupe = true;
                }
                else
                {
                    if(cart == NULL)
                    {
                        cart = new orderItems;
                        cart->code = itemToAdd->code;
                        cart->name = itemToAdd->name;
                        cart->price = itemToAdd->price;
                        cart->qty =  qty;
                        cart->next = NULL;

                        tail = cart;
                    }
                    else{   
                        orderItems *temp = new orderItems;
                        temp->code = itemToAdd->code;
                        temp->name = itemToAdd->name;
                        temp->price = itemToAdd->price;
                        temp->qty =  qty;
                        temp->next = NULL;

                        tail->next = temp;
                        tail = temp;
                    }
                }
                if(dupe) //if got duplicate order print this output
                {
                    cout<<"\n\n=================================="<<endl;
                    cout<<"|       Same code entered.       |"<<endl;
                    cout << "| Code " <<left<<setw(6)<< ordernum << " quantity changed.  |" << endl;
                    cout<<"=================================="<<endl<<endl<<endl;
                    cout<<"Do you want to continue order? [Y-Yes || N-No] : ";
                }
                else{
                    cout<<"\n\n=================================="<<endl;
                    cout << "| Code " <<left<<setw(6)<< ordernum << " added to the cart. |" << endl;
                    cout<<"=================================="<<endl<<endl<<endl;
                    cout<<"Do you want to continue order? [Y-Yes || N-No] : ";
                }
                cin>>yes;
                cin.sync();

                if(yes=='Y'|| yes=='y')
                {    
                    itemlist.display();
                    x++;
                }
                else
                    x = 0;
            }
            else{
                cout << "Code " << ordernum << " does not exist in the item list." << endl;
                x++;
            }
	            

    	}while(x != 0);
    }
    int itemexist(int code)
    {
        orderItems *temp = cart;

        while(temp != NULL)
        {
            if(temp->code == code)
            {
                return 1;
            }
            temp = temp->next;
        }
        return 0;
    }

    int empty()
    {
        if(cart == NULL)
        {return 1;}
        else
        {return 0;}
    }

    void cancel(){
    	orderItems *temp = cart;
        int code;
        char choice;
        
        view();
    
        if (!empty())
        {
            cout << "\n";
            cout << "  +---------------------------+" << endl;
            cout << "  |                           |" << endl;
            cout << "  |    Pastry Cart Delete     |" << endl;
            cout << "  |                           |" << endl;
            cout << "  +---------------------------+" << endl;

            cout<<"\nPlease enter the cart item that you want to remove..."<<endl;
            cout<<"\nEnter code (Input 99 to exit deleting mode): ";
            cin>>code;
            cin.sync();
            do
            {
                if(code == 99)
                {
                    cout<<"Exiting deleting process..."<<endl;
                    break;
                } //break from the loop

                if(itemexist(code))
                {
                    cout<<"\nAre you sure that you want to remove this item from the cart? (Y/N)";
                    cin>>choice;
                    cin.sync();

                    if(choice == 'Y' || choice == 'y')
                    {
                        orderItems *prev;
                        while(temp->code != code)
                        {
                            prev = temp;
                            temp = temp->next;
                        }//to find which linked list is the code is located

                        cout<<"\n|========================================================|"<<endl;
                        cout<<"|           ITEM SUCCESSFULLY REMOVED FROM CART          |"<<endl;
                        cout<<"|========================================================|"<<endl;
                        cout<<"|  Item Code  : "<<left<<setw(39)<<temp->code<<"  |"<<endl;
                        cout<<"|  Item Name  : "<<left<<setw(39)<<temp->name<<"  |"<<endl;
                        cout<<"|  Item Price : "<<left<<setw(3)<<"RM "<<left<<setw(36)<<temp->price<<"  |"<<endl;
                        cout<<"|  Item Qty   : "<<left<<setw(39)<<temp->qty<<"  |"<<endl;
                        cout<<"|========================================================|"<<endl<<endl;//delete successful message

                        if (temp == cart) {
                            cart = temp->next;
                            delete temp;
                        } else if (temp->next == NULL) {
                            prev->next = NULL;
                            tail = prev;
                            delete temp;
                        } else {
                            prev->next = temp->next;
                            delete temp;
                        }

                        break;
                    }
                    else{
                        cout<<"\n\nItem deletion cancelled..."<<endl;
                        cout<<"Returning to User menu."<<endl;
                        break;
                    }
                }
                else{
                    cout<<"\nThe code you've entered does not exist in the cart...\nPlease enter a code from the cart."<<endl;
                    cout<<"\nEnter code (Input 99 to exit deleting mode): ";
                    cin>>code;
                }
            }while(true);
        }
	}
	
    void view(){
        orderItems *temp = cart;

        if(!empty())
        {
            cout << "\n ===============================================================\n";
            cout << " |                         Your Cart                           |\n";
            cout << " ===============================================================\n";
            cout<<" | "<<left<<setw(7)<<"Code"<<left<<setw(33)<<"|Name"<<left<<setw(14)<<"|Price (RM)"<<left<<setw(5)<<"|Qty"<<" |"<<endl;
            cout << " |-------------------------------------------------------------|\n";
            while(temp != NULL)
            {
                cout<<" | "<<left<<setw(8)<<temp->code<<left<<setw(33)<<temp->name<<left<<setw(14)<<temp->price<<left<<setw(4)<<temp->qty<<" |"<<endl;
                temp = temp->next;
            }
            cout << " ===============================================================\n";
        }
        else{
            cout << "\n=====================================\n";
            cout << "|          Cart is Empty!           |\n";
            cout << "=====================================\n";
            cout << "|                                   |\n";
            cout << "|  Your shopping cart is currently  |\n";
            cout << "|        empty. Start adding        |\n";
            cout << "|        items to your cart!        |\n";
            cout << "|                                   |\n";
            cout << "=====================================\n";
        }
    }
	
	void calculateTotal() 
	{
	    orderItems *temp = cart;
	    total = 0;
	    while (temp != NULL) 
		{
	        temp->total += (temp->price * temp->qty);
            total += temp->total;
	        temp = temp->next;
	    }
	
	    tax = total * 0.06; 
	    total += tax;
	}
	
void printReceipt() 
	{
	    system("cls");
	    cout << "+------------------------------------------------------------------------------+  " << endl;
	    cout << "|               _  _  ____  ____    ____    _    _  _______ ______   __        |" << endl;
	    cout << "|              | || |/ ___|| __ )  | __ )  / \\  | |/ / ____|  _ \\ \\ / /        | " << endl;
	    cout << "|              | || |\\___ \\|  _ \\  |  _ \\ / _ \\ | ' /|  _| | |_) \\ V /         | " << endl;
	    cout << "|              |__   _|__) | |_) | | |_) / ___ \\| . \\| |___|  _ < | |          | " << endl;
	    cout << "|                 |_||____/|____/  |____/_/   \\_\\_|\\_\\_____|_| \\_\\|_|          | " << endl;
	    cout << "|                                                                              | " << endl;
	    cout << "|                                                                              | " << endl;
	    cout << "|                         Multimedia University Sdn.Bhd                        | " << endl;
	    cout << "|                                                                              | " << endl;
	    cout << "|                             Persiaran Multimedia                             | " << endl;
	    cout << "|                                63100 Cyberjaya                               | " << endl;
	    cout << "|                                   Selangor.                                  | " << endl;
	    cout << "|                                 1-300-80-0668                                | " << endl;
	    cout << "|                                www.mmu.edu.my                                | " << endl;
	    cout << "|                                                                              | " << endl;
	    cout << "|==============================================================================| " << endl;
	    cout << "|                                                                              | " << endl;
	    cout << "|                                    RECEIPT                                   | " << endl;
	    cout << "|                                                                              | " << endl;
	    cout << "|==============================================================================| " << endl;
	    cout << "|                                                                              | " << endl;
	    cout << "|  Customer Name  : " <<left<<setw(59)<< name<< "| " << endl;
	    cout << "|  Phone Number   : " <<left<<setw(59)<<phone<< "| " << endl;
	    cout << "|  Email Address  : " <<left<<setw(59)<<email<< "| " << endl;
	    cout << "|                                                                              | " << endl;
	    cout << "|==============================================================================| " << endl;
	    cout << "|                                                                              | " << endl;
	    cout << "|                                Items Purchased                               | " << endl;
	    cout << "|                                                                              | " << endl;
	    cout << "|==============================================================================| " << endl;
	    orderItems *temp = cart;
        int i = 1;
		    while (temp != NULL) 
			{
		        cout <<"|  "<<right<<setw(3)<<i++<<". "<<left<<setw(46)<<temp->name<< "x " <<left<<setw(7)<< temp->qty<<right<<setw(3)<<"RM " <<right<<setw(9)<< temp->price * temp->qty << "    |"<<endl;
		        temp = temp->next;
		    }
	    cout<<"|                                                                              | "<< endl; 
        cout<<"|                                                                              | "<< endl; 
        cout<<"|"<<setw(62)<< "Tax (6%) : " << left << setw(3) << "RM " << right << setw(9)<< fixed << setprecision(2)<< tax<<"    |"<<endl;
	    cout<<"|"<<setw(62)<< "Grand Total : " << left << setw(3) << "RM " << right << setw(9)<< fixed << setprecision(2)<<total<<"    |"<<endl;
        cout<<"|"<<setw(62)<< "Payment Method : " << right << setw(12) << PayMethod<<"    |"<<endl;
        cout<<"|                                                                              | "<<endl; 
	    cout<<"|------------------------------------------------------------------------------| "<<endl;
	    cout<<"|                                                                              | "<<endl;
	    cout<<"|                     Thanks for choosing our 4SB BAKERY!                      | "<<endl;
	    cout<<"|                                                                              | "<<endl;
	    cout<<"|                        We hope you enjoy your meal!                          | "<<endl;
	    cout<<"|                                                                              | "<<endl;
	    cout<<"|                                                                              | "<<endl;
	    cout<<"|           _____ _   _    _    _   _ _  __ __   _____  _   _   _ _            | "<<endl;     
	    cout<<"|          |_   _| | | |  / \\  | \\ | | |/ / \\ \\ / / _ \\| | | | | | |           | "<<endl;   
	    cout<<"|            | | | |_| | / _ \\ |  \\| | ' /   \\ V / | | | | | | | | |           | "<<endl;   
	    cout<<"|            | | |  _  |/ ___ \\| |\\  | . \\    | || |_| | |_| | |_|_|           | "<<endl;  
	    cout<<"|            |_| |_| |_/_/   \\_\\_| \\_|_|\\_\\   |_| \\___/ \\___/  (_|_)           | "<<endl; 
	    cout<<"|                                                                              | "<<endl;
	    cout<<"|                                                                              | "<<endl;
	    cout<<"|                                                                              | "<<endl;
	    cout<<"+------------------------------------------------------------------------------+"<<endl;
		}
	
	void payment() 
	{
	    if (!empty()) {
	        calculateTotal();
	        cout << "\n\n";
	        cout << "==========================================" << endl;
	        cout << "|          PAYMENT PROCESSING            |" << endl;
	        cout << "==========================================" << endl;
	        cout << "|          Choose Payment Method         |" << endl;
            cout << "|          ---------------------         |" << endl;
	        cout << "| 1. Credit Card                         |" << endl;
	        cout << "| 2. Debit Card                          |" << endl;
            cout << "| 3. E-Wallet                            |" << endl;
	        cout << "| 4. Cash                                |" << endl;
	        cout << "==========================================" << endl;
	        cout << "Enter payment method (1-4): ";
	        
	        int paymentMethod;
	        cin >> paymentMethod;
	        cin.sync();
            while(paymentMethod < 1 || paymentMethod > 4)
            {
                cout<<"\n\nInvalid Choice...\nPlease enter payment method again.\n\nEnter payment method (1-4): ";
                cin >> paymentMethod;
	            cin.sync();
            }

            switch (paymentMethod)
            {
            case 1: PayMethod = "Credit Card";
                break;
            case 2: PayMethod = "Debit Card";
                break;
            case 3: PayMethod = "E-Wallet";
                break;
            case 4: PayMethod = "Cash";
                break;
            default:
                break;
            }
            printReceipt();
            paid = true;
			 
	    } else {
            cout << "\n=====================================\n";
            cout << "|          Cart is Empty!           |\n";
            cout << "=====================================\n";
            cout << "|                                   |\n";
            cout << "|  Your shopping cart is currently  |\n";
            cout << "|      empty. Please add items      |\n";
            cout << "|       before making payment!      |\n";
            cout << "|                                   |\n";
            cout << "=====================================\n";

	    }
	}	
    //add order done
    //delete item/ordered item done
    //view cart
    //make payment and print receipt
    
	/*void salesreport()
	{
        cout << "------------------------------------------------------------------------------------" << endl;
		cout << "Customer Name: " << name << endl;
	    cout << "Phone Number: " << phone << endl;
	    cout << "Email Address: " << email << endl;
	    cout << "------------------------------------------------------------------------------------" << endl;
	    cout<<"================="<<endl;
        cout << "|Items Purchased|" << endl;
        cout<<"================="<<endl;
	    orderItems *temp = cart;
	    while (temp != NULL) 
		{
	        cout << "\t" <<left<<setw(48)<< temp->name <<left<<setw(2)<< "x " <<left<<setw(6)<< temp->qty << "RM " << temp->price * temp->qty << endl;
	        temp = temp->next;
	    }
        cout << "------------------------------------------------------------------------------------" << endl;
        cout <<right<<setw(70)<<"Payment Method : "<<right<<setw(14)<<PayMethod<< endl;
        cout <<right<<setw(70)<<"Tax (6%) : "<<left<<setw(3)<<"RM "<<right<<setw(11)<<fixed<<setprecision(2)<<tax<< endl;
        cout <<right<<setw(70)<<"Grand Total : "<<left<<setw(3)<<"RM "<<right<<setw(11)<<fixed<<setprecision(2)<<total<< endl;
        cout << "------------------------------------------------------------------------------------" << endl;
	}*/

    void salesreport(ofstream& outfile) {
        // Replace cout with outfile from previous version^^
        outfile<<"------------------------------------------------------------------------------------"<<endl;
        outfile<<"Customer Name: "<<name<<endl;
        outfile<<"Phone Number: "<<phone<<endl;
        outfile<<"Email Address: "<<email<<endl;
        outfile<<"------------------------------------------------------------------------------------"<<endl;
        outfile<<"================="<<endl;
        outfile<<"|Items Purchased|"<<endl;
        outfile<<"================="<<endl;
        orderItems* temp = cart;
        while (temp != NULL) {
            outfile << "\t" << left << setw(48) << temp->name << left << setw(2) << "x " << left << setw(6)
                    << temp->qty << "RM " << temp->price * temp->qty << endl;
            temp = temp->next;
        }
        outfile << "------------------------------------------------------------------------------------" << endl;
        outfile << right << setw(70) << "Payment Method : " << right << setw(14) << PayMethod << endl;
        outfile << right << setw(70) << "Tax (6%) : " << left << setw(3) << "RM " << right << setw(11)<< fixed << setprecision(2) << tax << endl;
        outfile << right << setw(70) << "Grand Total : " << left << setw(3) << "RM " << right << setw(11)<< fixed << setprecision(2) << total << endl;
        outfile << "------------------------------------------------------------------------------------" << endl;
    }

    
};

int main()
{
    int choice, Uchoice, i=0;
    bool cont;
    Customer a[5]; //array
    cout<<"\n\n============================="<<endl;
    cout<<"| +-WELCOME TO 4SB BAKERY-+ |"<<endl;
    cout<<"============================="<<endl;
    cout<<"|  1. User (New Order)      |\n|  2. Admin                 |\n|  3. Exit Program          |\n";
    cout<<"=============================\n";
    cout<<"\nEnter choice: ";
    cin>>choice;
    cin.sync();
    while(choice != 3)
    {
        if(choice == 1)
        {
            if(!a[i].status)
            {
                a[i].getcustomerinfo();
            }
            else{
                system("cls");
                cout << "\n ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !" << endl;
                cout << "========================================" << endl;
                cout << "|             CONTINUED AS             |";
                a[i].display_entered();
            }
        	do{
                cont = true;
	            cout << "\n\n";
                cout << "========================================\n";
                cout << "|              MENU OPTIONS            |\n";
                cout << "========================================\n";
                cout << "| 1. Add Order                         |\n";
                cout << "| 2. Delete Order                      |\n";
                cout << "| 3. View Cart                         |\n";
                cout << "| 4. Make Payment & Print Receipt      |\n";
                cout << "| 5. Exit Ordering                     |\n";
                cout << "========================================\n\n";
                cout<<"\nEnter Choice: ";
	            cin>>Uchoice;
	            cin.sync();
	            switch(Uchoice)
	            {
	            	case 1:
	            		itemlist.display();
	            		a[i].order();
	            		break;
	            	case 2:
	            		//itemlist.display();
	            		a[i].cancel();
                        EnterToComtinue();
	            		break;
	            	case 3:
	            		a[i].view();
                        EnterToComtinue();
	            		break;
	            	case 4:
	            		a[i].payment();
                        if(a[i].paid)
                        {
                            cont = false;
                            i++;
                        }
                        EnterToComtinue();
	            		break;
	            	case 5:
	            		if(!a[i].paid && !a[i].empty())
                        {
                            cout<<"=============================================="<<endl;
                            cout<<"|      Thank you for using our service.      |"<<endl;
                            cout<<"|  Before exiting, please make a payment to  |"<<endl;
                            cout<<"|         complete your transaction.         |"<<endl;
                            cout<<"=============================================="<<endl;
                            cout<<"|          Please proceed to payment.        |"<<endl;
                            cout<<"=============================================="<<endl<<endl;
                            EnterToComtinue();
                        }
                        else{
                            cont = false;
                        }
	                    break;
	                default:
	                    cout<<"\nThe choice you've entered is not valid."<<endl;
	                    cout<<"Please enter the choice again.";
				}
			}while(cont);
        }
        else if(choice == 2)
        {
            do{
                cont = true;
                cout << "\n\n=============================\n";
                cout << "|        ADMIN MENU         |\n";
                cout << "=============================\n";
                cout << "| 1. Add Items              |\n";
                cout << "| 2. Delete Items           |\n";
                cout << "| 3. Edit Items             |\n";
                cout << "| 4. Display Item List      |\n";
                cout << "| 5. Exit Admin Mode        |\n";
                cout << "=============================\n";
                cout << "\nEnter choice: ";
                cin>>Uchoice;
                cin.sync();
                switch(Uchoice)
                {
                    case 1:
                    itemlist.display();
                    itemlist.add();
                    break;  
                    case 2:
                    itemlist.display();
                    itemlist.remove();
                    break;
                    case 3:
                    itemlist.display();
                    itemlist.edit();
                    break;
                    case 4:
                    itemlist.display();
                    EnterToComtinue();
                    break;
                    case 5:
                    cout<<"\nExiting admin mode..."<<endl;
                    EnterToComtinue();
                    cont = false;
                    break;
                    default:
                    cout<<"\n\nThe choice you've entered is not valid."<<endl;
                    cout<<"Please enter the choice again."<<endl<<endl;
                    EnterToComtinue();
                }
            }while(cont);
        }
        cout<<"\n\n============================="<<endl;
        if(choice > 3)
        {
            cout<<"|       INVALID CHOICE      |"<<endl;
        }
        else{
            cout<<"| +-WELCOME TO 4SB BAKERY-+ |"<<endl;
        }
        cout<<"============================="<<endl;
        cout<<"|  1. User (New Order)      |\n|  2. Admin                 |\n|  3. Exit Program          |\n";        cout<<"=============================\n";
        cout<<"\nEnter choice: ";
        cin>>choice;
        cin.sync();
        
    }
    if(a[0].paid)
    {
        ofstream outFile("sales_report.txt");
            if (outFile.is_open()) {
                
                cout<<"=============================================="<<endl;
                cout<<"|            SALES REPORT GENERATED          |"<<endl;
                cout<<"|       (LOCATED IN THE SAME DIRECTORY)      |"<<endl;
                cout<<"=============================================="<<endl;
                cout<<"|        Exiting Program... Thank you!       |"<<endl;
                cout<<"=============================================="<<endl<<endl;

                outFile<<"===================================================================================="<<endl;
                outFile<< "|                             CUSTOMER DETAILS & PURCHASE                          |"<<endl;

                // Assuming 'a' is an array of Customer objects and 'i' is its size
                for (int j = 0; j < i; j++) {
                    outFile <<"===================================================================================="<<endl;
                    outFile <<"Customer #"<< j + 1 <<endl;
                    if (a[j].paid) {
                        a[j].salesreport(outFile);
                    }
                }

                // Close the file
                outFile.close();
                
                system("sales_report.txt");
            }
            else{
                cout<<"SALES REPORT GENERATE ERROR." <<endl;
                return 1;
            }
    }
    else{
        cout<<"\n\n=========================================="<<endl;
        cout<<"|      NO PURCHASES HAVE BEEN MADE       |"<<endl;
        cout<<"|           EXITING PROGRAM...           |"<<endl;
        cout<<"=========================================="<<endl<<endl;
    }
   
    return 0;
}

void EnterToComtinue()
{
    char *a = new char;
    cout<<"\n[PRESS ENTER TO CONTINUE]";
    *a = getchar();
    delete a;
} 