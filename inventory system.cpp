#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <limits>
#include <queue>
using namespace std;

struct Productnode
{
    string name;
    int quantity;
    float price;
    Productnode* adrs;
    Productnode* left;  
    Productnode* right;
    Productnode() : left(nullptr), right(nullptr), adrs(nullptr) {}
};

class Bstree
{
private:
    Productnode* root;  

public:
    Bstree() : root(nullptr) {}

    void treefromll(Productnode* s)
    {
        while (s)
        {
            Productnode* newNode = new Productnode;
            newNode->name = s->name;
            newNode->quantity = s->quantity;
            newNode->price = s->price;
            newNode->left = nullptr;
            newNode->right = nullptr;

            insert(root, newNode);  
            s = s->adrs;  
        }
    }

    void insert(Productnode*& root, Productnode* newNode)
    {
        if (root == nullptr)
        {
            root = newNode;
        }
        else if (newNode->price < root->price)  
        {
            insert(root->left, newNode);
        }
        else
        {
            insert(root->right, newNode);
        }
    }

    void lowtohigh(Productnode* c)
    {
        if (c != nullptr)
        {
            lowtohigh(c->left);  
            cout<< "    " << c->name << " - Price: " << c->price << endl;
            lowtohigh(c->right); 
        }
    }

    void hightolow(Productnode* node)
    {
        if (node != nullptr)
        {
            hightolow(node->right);  
            cout << "    "<<node->name << " - Price: " << node->price << endl;
            hightolow(node->left);
        }
    }

    void lowtohigh() { lowtohigh(root); }
    void hightolow() { hightolow(root); }

};



class Inventory
{
private:
   
    Productnode* s, * c, * n;

public:

    Inventory()
    {
        s = nullptr;
    }

    void addProduct()
    {
        Productnode* n = new Productnode;
        cout << "   Enter Product Name: ";
        cin >> n->name;


        while (true) 
        {
            cout << "   Enter Quantity: ";
            if (cin >> n->quantity && n->quantity > 0)
            {
                break;
            }
            else
            {
                cout << "   Invalid input! Please enter a numeric value for quantity." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        while (true)
        {
            cout << "   Enter Price: ";
            if (cin >> n->price && n->price > 0) 
            {
                break;
            }
            else 
            {
                cout << "   Invalid input! Please enter a numeric value for price." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        n->adrs = nullptr;

        if (!s) 
        {
            s = n;
        }
        else
        {
            c = s;
            while (c->adrs)
                c = c->adrs;
            c->adrs = n;
        }

        cout << endl << "  Product added successfully! " << endl << endl;
    }

    void viewProducts()
    {
        if (!s)
        {
            cout << endl << " No products available ";
            return;
        }

        c = s;
        cout << endl << "   Available Products are: " << endl << endl;
        cout << left << setw(15) << "   Name" << setw(10) << "Quantity" << setw(10) << "     Price" << endl;
        cout << "-----------------------------------------------" << endl;

        while (c)
        {
            cout << left << setw(20) << c->name
                << setw(10) << c->quantity
                << " PKR " << setw(10) << c->price << endl;
            c = c->adrs;
        }
    }



    void viewProductsForCustomer()
    {
        if (!s)
        {
            cout << endl << " No products available ";
            return;
        }

        c = s;
        cout << endl << "   Available Products are: " << endl;
        cout << endl << left << setw(15) << " Name" << setw(10) << " Price";
        cout << endl << "----------------------------------- ";

        while (c)
        {
            cout << endl << left << setw(15) << c->name
                << "PKR " << c->price << " -/." << endl;
            c = c->adrs;
        }
    }

    bool searchProduct(string& name, int& availableQuantity, float& price)
    {
        c = s;
        while (c)
        {
            if (c->name == name)
            {
                availableQuantity = c->quantity;
                price = c->price;
                return true;
            }
            c = c->adrs;
        }
        return false;
    }

    void deductQuantity(string& name, int quantity)
    {
        c = s;
        while (c)
        {
            if (c->name == name)
            {
                c->quantity -= quantity;
                return;
            }
            c = c->adrs;
        }
    }
    void removeProduct(string& name)
    {
        c = s;
        Productnode* temp = nullptr;

        while (c && c->name != name)
        {
            temp = c;
            c = c->adrs;
        }

        if (!c)
        {
            cout << endl << "   Product not found. ";
            return;
        }

        if (!temp)
        {
            s = s->adrs;
        }
        else
        {
            temp->adrs = c->adrs;
        }

        delete c;
        cout << endl << "  Product has been removed from inventory.";
    }
    void modifyProduct(string& name, string& newName, int newQuantity, float newPrice)
    {
        c = s;
        while (c)
        {
            if (c->name == name)
            {
                c->name = newName;
                c->quantity = newQuantity;
                c->price = newPrice;
                cout << endl << "   Product had been modified successfully. ";
                return;
            }
            c = c->adrs;
        }
        cout << endl << "   Product not found. ";
    }

    void findProduct(string& name)
    {
        c = s;
        while (c)
        {
            if (c->name == name)
            {
                cout << endl << "  Product Found: ";
                cout << endl << "  Name: " << c->name << endl << "  Quantity: " << c->quantity << endl << "  Price: PKR. " << c->price << endl;
                return;
            }
            c = c->adrs;
        }
        cout << endl << "  Product not found. ";
    }
    
    void saveToFile()
    {
        ofstream file("inventory.txt");
        if (!file)
        {
            cout << endl << "   Error saving to file.";
            return;
        }

        Productnode* temp = s;
        while (temp)
        {
            file << temp->name << "," << temp->quantity << "," << temp->price << endl;
            temp = temp->adrs;
        }

        file.close();
        cout << endl << "   Inventory saved to file.";
    }

    void loadFromFile()
    {
        ifstream file("inventory.txt");
        if (!file)
        {
            cout << endl << "   Error loading from file.";
            return;
        }

        string name;
        int quantity;
        float price;
        char delimiter;

        while (file >> name >> delimiter >> quantity >> delimiter >> price)
        {
            Productnode* newNode = new Productnode;
            newNode->name = name;
            newNode->quantity = quantity;
            newNode->price = price;
            newNode->adrs = nullptr;

            if (!s)
                s = newNode;
            else
            {
                Productnode* temp = s;
                while (temp->adrs)
                    temp = temp->adrs;
                temp->adrs = newNode;
            }
        }

        file.close();
        cout << endl << "   Inventory loaded from file.";
    }
    void checkforRestock()
    {   
        bool restock = false;
        if (!s)
        {
            cout << "No products in inventory to check." << endl;
            return;
        }
        queue<Productnode*> productq; 
         c = s;

        while (c)
        {
            productq.push(c);
            c = c->adrs;
        }

        while (!productq.empty())
        {
            Productnode* product = productq.front();
            productq.pop();

            if (product->quantity < 5)
            {      
                restock = true;
                cout<<endl<< "   Product: " << product->name
                    << "  has low stock."<<endl<<"   Current Quantity : " << product->quantity
                    <<endl<<"   Please restock." << endl;
            }
                        
        } 
        if (!restock)
        {
            cout << endl << "   No Product to be Restocked ";
            return;
        }
       
    }
    void filterProducts() 
    {
      if (!s)
    {
        cout << endl << "   No products available to filter.";
        return;
    }

    Bstree bst;
    bst.treefromll(s);

        int fchoice;
        cout<<endl << "   Choose a filter: "<<endl;
        cout<<endl << "    1. Filter by low to high price ";
        cout<<endl << "    2. Filter by high to low price "<<endl;
        cin >> fchoice;

        switch (fchoice) 
        {
        case 1:
            cout << endl << "   Products sorted by low to high price:  " << endl;
            bst.lowtohigh();   
            break;

        case 2:
            cout<<endl << "   Products sorted by high to low price:  "<<endl; 
            bst.hightolow();   
            break;

        default:
            cout<<endl << "  Invalid choice!  ";
        }
    }

};      
      

class Cart
{
private:
    Productnode* s, * c, * n;

public:
    Cart()
    {
        s = nullptr;
    }

    void addToCart(string& name, int quantity, float price)
    {
        n = new Productnode;
        n->name = name;
        n->quantity = quantity;
        n->price = price;
        n->adrs = nullptr;

        if (!s)
        {
            s = n;
        }
        else
        {
            c = s;
            while (c->adrs)
            {
                if (c->name == name)
                {
                    c->quantity += quantity;
                    delete n;
                    cout << endl << "  Product quantity updated in cart.";
                    return;
                }
                c = c->adrs;
            }
            c->adrs = n;
        }

        cout << endl << endl << "  Product added to the cart. ";
    }

    void viewCart()
    {
        if (!s)
        {
            cout << endl << "  The cart is empty. ";
            return;
        }

        c = s;
        float total = 0;
        cout << left << setw(15) << "  Name " << setw(10) << "  Quantity " << setw(10) << "  Price " << setw(10) << "  Total " << endl;
        cout << endl << "-----------------------------------------------" << endl;

        while (c)
        {
            float subtotal = c->quantity * c->price;
            cout << left << setw(15) << c->name
                << setw(10) << c->quantity
                << " PKR " << setw(9) << c->price
                << " PKR " << subtotal << endl;
            total += subtotal;
            c = c->adrs;
        }
        cout << "  Total Cart Value: PKR " << total << " -/." << endl;

    }

    void modifyCart(string& name, int newQuantity)
    {
        c = s;
        while (c)
        {
            if (c->name == name)
            {
                if (newQuantity == 0)
                {
                    removeFromCart(name);
                    cout << endl << "  Product has been removed from the cart.";
                }
                else
                {
                    c->quantity = newQuantity;
                    cout << endl << "  Cart updated.";
                }
                return;
            }
            c = c->adrs;
        }

        cout << endl << "  Product not found in the cart.";
    }

    void removeFromCart(string& name)
    {
        c = s;
        Productnode* temp = nullptr;

        while (c && c->name != name)
        {
            temp = c;
            c = c->adrs;
        }

        if (!c) return;

        if (!temp)
        {
            s = s->adrs;
        }
        else
        {
            temp->adrs = c->adrs;
        }

        delete c;
    }

    void clearCart()
    {
        while (s)
        {
            Productnode* temp = s;
            s = s->adrs;
            delete temp;
        }
        cout << endl << "  Cart cleared.";
    }

    void confirmOrder(Inventory& inventory)
    {
        if (!s)
        {
            cout << endl << "  Your cart is empty. ";
            return;
        }

        c = s;
        while (c)
        {
            inventory.deductQuantity(c->name, c->quantity);
            c = c->adrs;
        }

        clearCart();
        cout << endl << endl << " Your Order has confirmed! Thank you for shopping.";
    }
};


int main()
{
    Inventory inventory;
    Cart cart;
    int choice;
    string ch;
    int count;
    Bstree bst;
    
    cout << endl << " Press any button to begin!           " << endl;
    cin >> ch;
                
    system("CLS");
    while (true)
    {

        cout << endl << "                     ====================================================================" << endl;
        cout << endl << "                     ------------------- INVENTORY MANAGEMENT SYSTEM ------------------- " << endl;
        cout << endl << "                     ====================================================================" << endl;
        cout << endl << "    Please Authenticate your role:" << endl;
        cout << endl << "     1. Customer ";
        cout << endl << "     2. Manager ";
        cout << endl << "     3. Exit " << endl;
        cin >> choice;

        if (choice == 1)
        {
            system("CLS");
            cout << endl << "                     ====================================================================" << endl;
            cout << endl << " \t\t\t   ---------------- WELCOME TO NODE MART ----------------        " << endl;
            cout << endl << "                     ====================================================================" << endl;
            int customerChoice;
            do 
            {
                cout << endl << "             MAIN MENU            " << endl;
                cout << endl << "     1. View Products ";
                cout << endl << "     2. Add Product to Cart ";
                cout << endl << "     3. Filter Products by Price  ";
                cout << endl << "     4. View Cart ";
                cout << endl << "     5. Modify Cart ";
                cout << endl << "     6. Clear Cart ";
                cout << endl << "     7. Confirm Order ";
                cout << endl << "     8. Exit " << endl;
                cout << endl << "   Enter your choice: ";
                cin >> customerChoice;

                switch (customerChoice)
                {
                case 1:
                    system("CLS");
                    cout << endl;
                    inventory.viewProductsForCustomer();
                    break;
                case 2:
                {
                    system("CLS");
                    cout << endl;
                    string productName;
                    int quantity, availableQuantity;
                    float price;
                    inventory.viewProductsForCustomer();
                    cout << endl << "   Enter no. of products to add to cart: ";
                    cin >> count;


                    cout << "  Enter Product Name to add to Cart: ";
                    cin >> productName;

                    if (inventory.searchProduct(productName, availableQuantity, price))
                    {
                        cout << "  Enter Quantity to Add: ";
                        cin >> quantity;

                        if (quantity > availableQuantity)
                        {
                            cout << endl << "  Insufficient stock available.";
                        }
                        else
                        {
                            for (int i = 0;i < count;i++)
                                cart.addToCart(productName, quantity, price);
                        }
                    }
                    else
                    {
                        cout << endl << "  Product not available.";
                    }
                    break;
                }
                case 3:
                {              
                    
                    system("CLS");
                    cout << endl;
                    inventory.filterProducts();
                    break;
                }

                case 4:
                {
                    system("CLS");
                    cout << endl;
                    cout << endl << "    Your Cart:   " << endl;
                    cart.viewCart();
                    break;
                }
                case 5:
                {
                    system("CLS");
                    cout << endl;
                    string productName;
                    int newQuantity;

                    cout << "  Enter Product Name to Modify: ";
                    cin >> productName;
                    cout << "  Enter New Quantity (0 to remove): ";
                    cin >> newQuantity;

                    cart.modifyCart(productName, newQuantity);
                    break;
                }
                case 6:
                {
                    system("CLS");
                    cout << endl;
                    cart.clearCart();
                    break;
                }
                case 7:
                {
                        system("CLS");
                    cout << endl;
                    cart.confirmOrder(inventory);
                    break;
                }
                case 8:
                {
                    system("CLS");
                    cout << endl;
                    cout << "   Exiting Menu";
                    break;
                }
                default:
                    cout << endl << "  Invalid choice! Try again. ";
                }
            } while (customerChoice != 8);
            cout << endl << "\t\t\t\t---------------- THANKS FOR VISTING ---------------- ";
            system("CLS");
        }
    }
    return 0;
}