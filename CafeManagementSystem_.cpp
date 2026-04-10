#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// COLOR CODES 
#define RESET       "\033[0m"
#define BACKGROUND  "\033[48;5;17m"   
#define BLUEBERRY   "\033[38;5;135m"  
#define LAVENDER    "\033[38;5;183m"  
#define MINT        "\033[38;5;51m"   
#define CREAM       "\033[38;5;250m"  
#define PINK        "\033[38;5;218m"  

//MENU DATA 
const int TOTAL_ITEMS = 16;
string categories[4] = {"Coffee", "Juices", "Desserts", "Extras"};

int itemID[TOTAL_ITEMS] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

string itemName[TOTAL_ITEMS] = 
{
    "Depresso espresso","Caramel cascade","Caffeinated Latte","Dirty Matcha",
    "Morning drew","Lime yous","Appletini","Pineapple Fizz",
    "Bento Cake","Ice Cream","Pistacho cheese cake","Marshmallow croissant",
    "Fries","Pesto Chicken Sandwich","Achyls tacos","Chipotle mac & Cheese"
};

float itemPrice[TOTAL_ITEMS] =
 {
    270,320,300,350,
    230,260,240,260,
    450,300,250,380,
    330,370,270,480
};

int itemStock[TOTAL_ITEMS] = 
{
    10,10,10,10,
    15,15,15,15,
    12,12,12,12,
    20,20,20,20
};

int orderID[100];
int orderQty[100];
float orderTotal[100];
string orderName[100];
int orderCount = 0;

// SEARCH ITEM 
void searchItem() 
{
    cin.ignore();
    string key;
    cout<<BLUEBERRY "\nEnter item name to search:" RESET;
    getline(cin,key);

    cout<<PINK "\n--- Search Results ---\n" RESET;
    bool found=false;

    for(int i=0;i<TOTAL_ITEMS;i++)
    {
        if(itemName[i].find(key)!=string::npos){
            cout << LAVENDER
          << "ID: "<<itemID[i]<<" | "<< itemName[i]<<" | Rs: "
          << MINT << itemPrice[i]<< LAVENDER <<"|Stock: "
          << CREAM << itemStock[i]
          << RESET << endl;
            found=true;
        }
    }

    if(!found) cout << PINK "No matching item found.\n" RESET;
} 

void showCombos() {
    cout << PINK "\n=========== COMBO OFFERS ===========\n" RESET;
    cout << LAVENDER "1.Caffeinated Latte + Pistacho cheese cake       = " << MINT << "Rs. 520\n" RESET;
    cout << LAVENDER "2. Dirty Matcha + The brownienator       = " << MINT << "Rs. 650\n" RESET;
    cout << LAVENDER "3. Morning drew + Fries    = " << MINT << "Rs. 380\n" RESET;
}

void orderCombo() {
    int combo;
    cout << BLUEBERRY "\nEnter Combo Number (1-3): " RESET;
    cin >> combo;

    if(combo==1)
    {
        if(itemStock[2]>0 && itemStock[10]>0)
        {
            itemStock[2]--; itemStock[10]--;
            orderName[orderCount]="Combo:  Caffeinated Latte + Pistacho cheese cake";
            orderTotal[orderCount]=520; 
            orderQty[orderCount]=1; 
            orderCount++;
            cout << LAVENDER " Combo 1 added!\n" RESET;
        } else cout << PINK "Not enough stock!\n" RESET;
    }
    else if(combo==2){
        if(itemStock[3]>0 && itemStock[11]>0)
        {
            itemStock[3]--; itemStock[11]--;
            orderName[orderCount]="Combo: Dirty Matcha + The brownienator";
            orderTotal[orderCount]=650; 
            orderQty[orderCount]=1;
             orderCount++;
            cout << LAVENDER " Combo 2 added!\n" RESET;
        } else cout << PINK "Not enough stock!\n" RESET;
    }
    else if(combo==3)
    {
        if(itemStock[4]>0 && itemStock[12]>0)
        {
            itemStock[4]--; itemStock[12]--;
            orderName[orderCount]="Combo: Morning drew + Fries";
            orderTotal[orderCount]=380;
             orderQty[orderCount]=1;
             orderCount++;
            cout << LAVENDER "Combo 3 added!\n" RESET;
        } else cout << PINK "Not enough stock!\n" RESET;
    } else cout << PINK "Invalid combo option!\n" RESET;
}

void showMenu() {
    cout << PINK "\n============== CAFE MENU ==============\n" RESET;

    int index=0;
    for(int c=0;c<4;c++){
        cout << BLUEBERRY "\n--- "<<categories[c]<<" ---\n" RESET;
        cout << "ID   Item Name                     Price   Stock\n";
        cout << "------------------------------------------------------\n";

        for(int i=0;i<4;i++){
            cout << CREAM << itemID[index] << RESET << "   ";
            cout << LAVENDER << itemName[index] << RESET;
            
            int columnWidth = 30; 
            int spaceCount=columnWidth-itemName[index].length();
            if(spaceCount < 1) 
            spaceCount = 1;
            if(itemName[index]=="Bento Cake") 
            spaceCount += 1;
            for(int s=0;s<spaceCount;s++) 
            cout<<" ";
            cout << MINT << itemPrice[index] << RESET << "      ";
            cout << CREAM << itemStock[index] << RESET << endl;
            index++;
        }
    }
    cout << PINK "======================================\n" RESET;
}

void takeOrder()
{
    int id,qty; char choice;
    do
    {
        cout << BLUEBERRY "\nEnter 99 to order Combo Offers\n" RESET;
        showMenu();
        cout << BLUEBERRY "\nEnter Item ID to order: " RESET;
        cin >> id;

        if(id==99)
        {
             showCombos(); 
             orderCombo(); 
            }
        else if(id>=1 && id<=TOTAL_ITEMS)
        {
            cout << BLUEBERRY "Enter Quantity: " RESET; 
            cin>>qty;
            int index=id-1;
            if(itemStock[index]>=qty)
            {
                orderName[orderCount]=itemName[index];
                orderQty[orderCount]=qty;
                orderTotal[orderCount]=itemPrice[index]*qty;
                itemStock[index]-=qty; orderCount++;
                cout<<LAVENDER "Item added successfully!\n" RESET;
            } else 
            cout<<PINK "Not enough stock!\n" RESET;
        }
        else cout<<PINK "Invalid ID!\n" RESET;

        cout << BLUEBERRY "Add more items?(y/n): " RESET;
        cin >>choice;
    }while(choice=='y'||choice=='Y');
}

string paymentMethod(){
    int method;
    cout <<BLUEBERRY "\nSelect Payment Method:\n" RESET;
    cout <<"1. Cash\n2. Card\nEnter choice: ";
    cin>>method;
    if(method==1) 
    return "Cash";
    if(method==2)
    return "Card";
    return "Unknown";
}

float calculateSubtotal()
{ float subtotal=0; 
    for(int i=0;i<orderCount;i++) 
    subtotal+=orderTotal[i];
    return subtotal;
}
float applyDiscount(float subtotal)
{ 
    if(subtotal>2000)
     return subtotal*0.10; 
     return 0;
}
float calculateTax(float amount)
{ 
    return amount*0.05;
}
void resetOrder()
{
    orderCount=0;
}

void generateBill(){
    if(orderCount==0){
         cout << PINK "No orders yet!\n" RESET; 
         return;
         }
    float subtotal=calculateSubtotal();
    float discount=applyDiscount(subtotal);
    float afterDiscount=subtotal-discount;
    float tax=calculateTax(afterDiscount);
    float finalTotal=afterDiscount+tax;
    string pay=paymentMethod();

    cout << PINK "\n========= BILL RECEIPT =========\n" RESET;
    cout << "Item\t\tQty\tTotal\n--------------------------------\n";
    for(int i=0;i<orderCount;i++)
        cout << LAVENDER << orderName[i] << RESET << "\t"
             << CREAM << orderQty[i] << RESET << "\t"
             << MINT << orderTotal[i] << RESET << endl;

    cout << "--------------------------------\n";
    cout << MINT << "Subtotal:\t" << subtotal<< RESET << endl;
    cout << PINK << "Discount:\t-" << discount<< RESET << endl;
    cout << MINT << "Tax (5%):\t" << tax<< RESET << endl;
    cout << MINT << "Payment:\t" << pay<< RESET << endl;
    cout << PINK << "Final Total:\t" << finalTotal << RESET << endl;
    cout << PINK "================================\n" RESET;

    ofstream file("sales.txt", ios::app);
    file << "Sale: " << finalTotal << " Rs | Method: " << pay << endl;
    file.close();

    resetOrder();
}

void viewSales(){
    ifstream file("sales.txt");
     string line;
    cout << PINK "\n========= DAILY SALES RECORD =========\n" RESET;
    if(!file)
    { 
        cout << PINK "No sales record found.\n" RESET; 
        return; 
    }
    while(getline(file,line)) 
    cout << LAVENDER << line << RESET << endl;
    file.close();
}

void feedback(){
    cin.ignore(); 
    string name,fb;
    cout<< BLUEBERRY "\nEnter your name: " RESET;
     getline(cin,name);
    cout<< BLUEBERRY "Write your feedback: " RESET;
     getline(cin,fb);

    ofstream file("feedback.txt", ios::app);
    if(!file)
    { 
        cout << PINK "Error saving feedback!\n" RESET;
         return;
    }
    file << "Name: " << name << " | Feedback: " << fb << endl;
    file.close();
    cout << LAVENDER "\nThank you for your feedback!\n" RESET;
}

void viewFeedback()
{
    ifstream file("feedback.txt"); 
    string line;
    cout << PINK "\n======= CUSTOMER FEEDBACK =======\n" RESET;
    if(!file)
    {
         cout << PINK "No feedback found!\n" RESET; 
        return; 
    }
    while(getline(file,line)) cout << LAVENDER << line << RESET << endl;
    file.close();
}

int main()
{
    int choice;
    do{
        cout << PINK "\n===== CAFE MANAGEMENT SYSTEM =====\n" RESET;
        cout << "1. Show Menu\n2. Take Order\n3. Generate Bill\n4. View Daily Sales\n5. Search Item\n6. Show Combos\n7. Give Feedback\n8. Exit\n";
        cout << BLUEBERRY "Enter your choice: " RESET; cin>>choice;

        switch(choice)
        {
            case 1: showMenu(); break;
            case 2: takeOrder(); break;
            case 3: generateBill(); break;
            case 4: viewSales(); break;
            case 5: searchItem(); break;
            case 6: showCombos(); break;
            case 7: feedback(); break;
            case 8: cout << LAVENDER "Thank you!\n" RESET; break;
            default: cout << PINK "Invalid choice!\n" RESET;
        }
    } while(choice!=8);
    return 0;
}