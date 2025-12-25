#include <iostream>
#include <windows.h>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <conio.h>

using namespace std;

//--------------------------------------
// FUNCTION TO CHANGE TEXT COLOR
//--------------------------------------
void setcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//--------------------------------------
// STRUCTURES
//--------------------------------------
struct item {
    string itemname;
    int itemprice;
};

struct admin {
    string adminname;
    int adminpin;
};

// NEW: Structure for Audit Report (Non-File based)
struct Transaction {
    int orderID;
    string date;
    float amount;
};

//--------------------------------------
// MAIN MENU FUNCTION
//--------------------------------------
int menu() {
    // --- CART & SYSTEM VARIABLES ---
    const int max_items = 50;
    item cart[max_items];
    int cartsize = 0;

    // --- AUDIT HISTORY VARIABLES ---
    Transaction salesHistory[100]; // Stores up to 100 orders
    int totalSalesCount = 0;       // Keeps track of how many orders placed

    // --- ADMIN CREDENTIALS ---
    admin admininfo[4] = {
        {"aman", 1122},
        {"saad", 6789},
        {"dheeraj", 4955},
        {"mir", 1999}
    };

    // --- INPUT VARIABLES ---
    int menuchoice = 0;
    int starterinput = 0;
    int choice = 0;
    float total = 0;
    char ans;
    
    // --- BILLING VARIABLES (Declared top to avoid goto errors) ---
    float subtotal = 0, tax = 0, service = 0, grosstotal = 0, discount = 0, finalamount = 0;
    time_t now;
    tm* Itm;
    char date[20], timestr[20];
    int currentOrderID = 0;

mainmenu:
    system("cls");
    setcolor(14);
    cout << "======================================\n";
    cout << "          ROYAL RESTAURANT   \n";
    cout << "======================================\n";
    setcolor(11);
    cout << "\n[1] Place Your Order\n";
    cout << "[2] Admin Login\n";
    cout << "[3] Exit\n";
    setcolor(7);
    cout << "\nYour Choice: ";
    cin >> menuchoice;
    
    // Input validation check
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        setcolor(12);
        cout << "Invalid Input. Enter numbers only!\n";
        Sleep(1000);
        goto mainmenu;
    }
    
    system("cls");

    //==================== CUSTOMER PANEL ====================
    if (menuchoice == 1) {

    backtomenu:
        setcolor(14);
        cout << "==============| MENU |==============\n";
        setcolor(11);
        cout << "\n1- STARTERS\n2- MAIN COURSE\n3- DESSERT\n4- DRINKS & BEVERAGES\n";
        cout << "5- BACK\n\n";
        setcolor(14);
        cout << "==============| BILLING & CART |==============\n";
        setcolor(4);
        cout << "\n6- View Cart\n7- Proceed to Checkout\n";
        setcolor(7);
        cout << "\nInput (1-7) For Selected Choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            choice = 0; // Force default case
        }
        
        system("cls");

        switch (choice) {
        case 1: goto starters;
        case 2: goto maincourse;
        case 3: goto dessert;
        case 4: goto drinks;
        case 5: goto mainmenu;
        case 6: goto cart;
        case 7: goto cart;
        default:
            setcolor(12);
            cout << "Invalid Input. Please Try Again!\n";
            Beep(750, 1500);
            Sleep(800);
            system("cls");
            goto backtomenu;
        }
    }

    //==================== ADMIN PANEL ====================
    else if (menuchoice == 2) {
    adminpagehold:
        string adminn;
        int pinn;

        system("cls");
        setcolor(14);
        cout << "========| ADMIN LOGIN PANEL |=========\n\n";
        setcolor(7);
        cout << "\nENTER USERNAME: ";
        cin >> adminn;
        cout << "ENTER PIN CODE: ";
        cin >> pinn;

        // Check Input validity
        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            setcolor(12); system("cls"); cout << "Invalid Pin Format.\n"; Beep(1000, 1500); ;Sleep(1000); goto adminpagehold;
        }

        for (int i = 0; i < 4; i++) {
            if (adminn == admininfo[i].adminname && pinn == admininfo[i].adminpin) {
                setcolor(10);
                cout << "\nAccess Granted! Welcome " << admininfo[i].adminname;
                Sleep(2000);
                system("cls");
                goto stayadminpanel;
            }
        }

        // If loop finishes without finding admin
        setcolor(12);
        cout << "\nInvalid Credentials. Try Again!\n";
        Beep(750,1000);
        Sleep(100);
        system("cls");
        goto adminpagehold;

    stayadminpanel:
        int adminpanelchoice;
        setcolor(14);
        cout << "========| ADMIN PANEL |=========\n";
        setcolor(11);
        cout << "\n1- View Menu";
        cout << "\n2- Generate Weekly Audit Report";
        cout << "\n3- Exit / Logout";
        
        setcolor(7);
        cout << "\n\nYour Choice: ";
        cin >> adminpanelchoice;

        if (cin.fail()) {
             cin.clear(); cin.ignore(1000, '\n');
             adminpanelchoice = 0;
        }

        switch (adminpanelchoice) {
        case 1:
            system("cls");
            setcolor(7);
            cout << "========| Full Menu |=========\n\n\n";
                    setcolor(14);
                    cout << "========| STARTERS |=========\n";
			        setcolor(11);
			        cout << "\n1- FINGER FISH :::: 600RS";
			        cout << "\n2- CORN SOUP   :::: 600RS";
			        cout << "\n3- FRIES       :::: 400RS";
			        cout << "\n4- CHICKEN POPCORN ::: 700RS";
			        setcolor(14);
			        cout << "\n\n========| MAIN COURSE |=========\n";
			        setcolor(11);
			        cout << "\n1- ZINGER BURGER :::: 500RS";
			        cout << "\n2- PIZZA :::: 999RS";
			        cout << "\n3- BROAST :::: 400RS";
			        cout << "\n4- FRIED CHICKEN WITH RICE ::: 850RS";
			        cout << "\n5- CHICKEN ROLL :::: 300RS";
			        setcolor(14);
			        cout << "\n\n========| DESSERT |=========\n";
			        setcolor(11);
			        cout << "\n1- ICE CREAM (SINGLE SCOOP) :::: 100RS";
			        cout << "\n2- ICE CREAM (DOUBLE SCOOP) :::: 200RS";
			        cout << "\n3- LAVA CAKE :::: 600RS";
			        cout << "\n4- OREO DESSERT ::: 600RS";
			        cout << "\n5- PANCAKE :::: 500RS";
			        setcolor(14);
			        cout << "\n\n========| DRINKS |=========\n";
			        setcolor(11);
			        cout << "\n1- CHOCOLATE SHAKE :::: 500RS";
			        cout << "\n2- VANILLA SHAKE :::: 400RS";
			        cout << "\n3- PEPSI :::: 99RS";
			        cout << "\n4- SPRITE ::: 99RS";
			        cout << "\n5- WATER :::: 70RS";
            cout << "\nPress any key to return...";
            getch();
            system("cls");
            goto stayadminpanel;
            
        case 2:
            // --- AUDIT REPORT IMPLEMENTATION ---
            system("cls");
            setcolor(14);
            cout << "========| WEEKLY AUDIT REPORT |=========\n\n";
            
            if(totalSalesCount == 0) {
                setcolor(12);
                cout << "No sales recorded in this session yet.\n";
            } else {
                setcolor(11);
                cout << left << setw(15) << "ORDER ID" << setw(15) << "DATE" << setw(15) << "AMOUNT (Rs)" << endl;
                cout << "---------------------------------------------\n";
                setcolor(7);
                float totalRev = 0;
                for(int i=0; i<totalSalesCount; i++) {
                    cout << left << setw(15) << salesHistory[i].orderID 
                         << setw(15) << salesHistory[i].date 
                         << setw(15) << salesHistory[i].amount << endl;
                    totalRev += salesHistory[i].amount;
                }
                setcolor(14);
                cout << "---------------------------------------------\n";
                cout << "TOTAL REVENUE: " << totalRev << " Rs\n";
            }
            cout << "\nPress any key to return...";
            getch();
            system("cls");
            goto stayadminpanel;

        case 3:
            system("cls");
            goto mainmenu;
            
        default:
            setcolor(12);
            cout << "Invalid Choice.\n";
            Sleep(800);
            system("cls");
            goto stayadminpanel;
        }
    }

    else if (menuchoice == 3) {
        setcolor(13);
        cout << "------ THANK YOU FOR VISITING ROYAL RESTAURANT -----\n";
        setcolor(7);
        cout << "\nClosing Application...";
        Sleep(1500);
        return 0;
    }

    else {
        setcolor(12);
        cout << "Invalid Input. Please Try Again!";
        Beep(1000, 1500);
        Sleep(800);
        goto mainmenu;
    }

    //==================== STARTERS ====================
starters:
    do {
    staystarters:
        setcolor(14);
        cout << "========| STARTERS |=========\n\n";
        cout << "   ITEMS                PRICE " << endl;
        setcolor(11);
        cout << "\n1- FINGER FISH :::: 600RS";
        cout << "\n2- CORN SOUP   :::: 600RS";
        cout << "\n3- FRIES       :::: 400RS";
        cout << "\n4- CHICKEN POPCORN ::: 700RS";
        cout << "\n\n5- BACK";
        setcolor(7);
        cout << "\n\nSelected Choice: ";
        cin >> starterinput;

        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            setcolor(12); cout << "Invalid Input!\n"; Sleep(800); system("cls"); goto staystarters;
        }

        switch (starterinput) {
        case 1:
            setcolor(10);
            cout << "\nFinger Fish Has Been Added To Your Cart!\n\n";
            Beep(3000, 100);
            cart[cartsize++] = {"Finger Fish", 600};
            Sleep(1000); system("cls"); goto staystarters;
        case 2:
            setcolor(10);
            cout << "\nCorn Soup Has Been Added To Your Cart!\n\n";
            Beep(3000, 100);
            cart[cartsize++] = {"Corn Soup", 600};
            Sleep(1000); system("cls"); goto staystarters;
        case 3:
            setcolor(10);
            cout << "\nFries Has Been Added To Your Cart!\n\n";
            Beep(3000, 100);
            cart[cartsize++] = {"Fries", 400};
            Sleep(1000); system("cls"); goto staystarters;
        case 4:
            setcolor(10);
            cout << "\nChicken Popcorn Has Been Added To Your Cart!\n\n";
            Beep(3000, 100);
            cart[cartsize++] = {"Chicken Popcorn", 700};
            Sleep(1000); system("cls"); goto staystarters;
        case 5:
            system("cls"); goto backtomenu;
        default:
            setcolor(12);
            cout << "Invalid Input. Please Try Again!\n";
            Beep(1000, 1500); Sleep(800); system("cls"); goto staystarters;
        }
    } while (starterinput != 5);

    //==================== MAIN COURSE ====================
maincourse:
    do {
        int maincourseinput = 0;
    staymaincourse:
        setcolor(14);
        cout << "========| MAIN COURSE |=========\n\n";
        cout << "   ITEMS                        PRICE " << endl;
        setcolor(11);
        cout << "\n1- ZINGER BURGER :::: 500RS";
        cout << "\n2- PIZZA :::: 999RS";
        cout << "\n3- BROAST :::: 400RS";
        cout << "\n4- FRIED CHICKEN WITH RICE ::: 850RS";
        cout << "\n5- CHICKEN ROLL :::: 300RS";
        cout << "\n6- BACK";
        setcolor(7);
        cout << "\n\nSelected Choice: ";
        cin >> maincourseinput;

        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            setcolor(12); cout << "Invalid Input!\n"; Sleep(800); system("cls"); goto staymaincourse;
        }

        switch (maincourseinput) {
        case 1: cart[cartsize++] = {"Zinger Burger", 500}; break;
        case 2: cart[cartsize++] = {"Pizza", 999}; break;
        case 3: cart[cartsize++] = {"Broast", 400}; break;
        case 4: cart[cartsize++] = {"Fried Chicken With Rice", 850}; break;
        case 5: cart[cartsize++] = {"Chicken Roll", 300}; break;
        case 6: system("cls"); goto backtomenu;
        default:
            setcolor(12);
            cout << "Invalid Input. Please Try Again!\n";
            Beep(750, 1500); Sleep(800); system("cls"); goto staymaincourse;
        }
        setcolor(10);
        cout << "\nItem Added To Cart Successfully!\n";
        Beep(3000, 100);
        Sleep(1000); system("cls"); goto staymaincourse;
    } while (true);

    //==================== DESSERT ====================
dessert:
    do {
        int dessertinput = 0;
    staydessert:
        setcolor(14);
        cout << "========| DESSERT |=========\n\n";
        cout << "   ITEMS                         PRICE " << endl;
        setcolor(11);
         cout << "\n1- ICE CREAM (SINGLE SCOOP) :::: 100RS";
        cout << "\n2- ICE CREAM (DOUBLE SCOOP) :::: 200RS";
        cout << "\n3- LAVA CAKE :::: 600RS";
        cout << "\n4- OREO DESSERT ::: 600RS";
        cout << "\n5- PANCAKE :::: 500RS";
        cout << "\n6- BACK";
        cout << "\n\nSelected Choice: ";
        cin >> dessertinput;

        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            setcolor(12); cout << "Invalid Input!\n"; Sleep(800); system("cls"); goto staydessert;
        }

        switch (dessertinput) {
        case 1: cart[cartsize++] = {"Ice Cream (Single)", 100}; break;
        case 2: cart[cartsize++] = {"Ice Cream (Double)", 200}; break;
        case 3: cart[cartsize++] = {"Lava Cake", 600}; break;
        case 4: cart[cartsize++] = {"Oreo Dessert", 600}; break;
        case 5: cart[cartsize++] = {"Pancake", 500}; break;
        case 6: system("cls"); goto backtomenu;
        default:
            setcolor(12);
            cout << "Invalid Input. Please Try Again!\n";
            Beep(750, 1500); Sleep(800); system("cls"); goto staydessert;
        }
        setcolor(10);
        cout << "\nItem Added To Cart Successfully!\n";
        Beep(3000, 100);
        Sleep(1000); system("cls"); goto staydessert;
    } while (true);

    //==================== DRINKS ====================
drinks:
    do {
        int drinksinput = 0;
    staydrinks:
        setcolor(14);
        cout << "========| DRINKS |=========\n\n";
        cout << "  ITEMS                PRICE " << endl;
        setcolor(11);
        cout << "\n1- CHOCOLATE SHAKE :::: 500RS";
        cout << "\n2- VANILLA SHAKE :::: 400RS";
        cout << "\n3- PEPSI :::: 99RS";
        cout << "\n4- SPRITE ::: 99RS";
        cout << "\n5- WATER :::: 70RS";
        cout << "\n6- BACK";
        setcolor(7);
        cout << "\n\nSelected Choice: ";
        cin >> drinksinput;

        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            setcolor(12); cout << "Invalid Input!\n"; Sleep(800); system("cls"); goto staydrinks;
        }

        switch (drinksinput) {
        case 1: cart[cartsize++] = {"Chocolate Shake", 500}; break;
        case 2: cart[cartsize++] = {"Vanilla Shake", 400}; break;
        case 3: cart[cartsize++] = {"Pepsi", 99}; break;
        case 4: cart[cartsize++] = {"Sprite", 99}; break;
        case 5: cart[cartsize++] = {"Water", 70}; break;
        case 6: system("cls"); goto backtomenu;
        default:
            setcolor(12);
            cout << "Invalid Input. Please Try Again!\n";
            Beep(750, 1500); Sleep(800); system("cls"); goto staydrinks;
        }
        setcolor(10);
        cout << "\nItem Added To Cart Successfully!\n";
        Beep(3000, 100);
        Sleep(1000); system("cls"); goto staydrinks;
    } while (true);

    //==================== CART ====================
cart:
    total = 0;
    if (cartsize == 0) {
        setcolor(12);
        cout << "===== Cart is Empty =====\n";
        Beep(750, 1500);
        setcolor(7);
        cout << "\nReturning To Menu...";
        Sleep(1000);
        system("cls");
        goto backtomenu;
    }
carthold:
    setcolor(14);
    cout << "==========| CART |==========\n\n";
    setcolor(11);
    for (int i = 0; i < cartsize; i++) {
        cout << "ITEM " << i + 1 << ": " << cart[i].itemname << endl;
        cout << "PRICE: " << cart[i].itemprice << "RS\n\n";
        total += cart[i].itemprice;
    }
    setcolor(14);
    cout << "--------------------------------\n";
    setcolor(12);
    cout << "TOTAL BILL: " << total << "Rs\n";
    setcolor(14);
    cout << "--------------------------------\n";
    setcolor(11);
    cout << "\nDo You Wish To Proceed To Billing? :  (Y/N)\n";
    cin >> ans;

    if (ans == 'Y' || ans == 'y') {
        setcolor(11);
        cout << "\n\nGenerating Your Bill. Please Wait...";
        Sleep(1500);
        system("cls");
        goto generatebill;
    } else if (ans == 'N' || ans == 'n') {
        system("cls");
        goto backtomenu;
    } else {
        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
        }
        setcolor(12);
        cout << "Invalid Input. Please Try Again!\n";
        Beep(750, 1500);
        Sleep(800);
        system("cls");
        goto carthold;
    }
    return 0;

    //==================== BILL GENERATION ====================
generatebill:
    subtotal = 0; // Reset calculations
    for (int i = 0; i < cartsize; i++) subtotal += cart[i].itemprice;
    
    tax = subtotal * 0.05;
    service = subtotal * 0.02;
    grosstotal = subtotal + service + tax;
    discount = grosstotal * 0.15;
    finalamount = grosstotal - discount;

    now = time(0);
    Itm = localtime(&now);
    strftime(date, sizeof(date), "%d-%b-%Y", Itm);
    strftime(timestr, sizeof(timestr), "%I:%M %p", Itm);
    
    currentOrderID = rand() % 9000 + 1000;

    // --- SAVE TO ARRAY (AUDIT LOGIC) ---
    if(totalSalesCount < 100) {
        salesHistory[totalSalesCount].orderID = currentOrderID;
        salesHistory[totalSalesCount].date = date;
        salesHistory[totalSalesCount].amount = finalamount;
        totalSalesCount++;
    }
    // -----------------------------------

    setcolor(6);
    cout << "========================================\n";
    setcolor(6);
    cout << "             |ROYAL RESTURANT|\n";
    setcolor(11);
    cout << "          Official Bill Summary\n";
    setcolor(6);
    cout << "========================================\n";
    setcolor(11);
    cout << "Order No. : #" << currentOrderID << endl;
    cout << "Date      : " << date << endl;
    cout << "Time      : " << timestr << endl;
    setcolor(6);
    cout << "----------------------------------------\n";
    setcolor(11);
    cout << "Items Ordered: \n";
    setcolor(6);
    cout << "----------------------------------------\n";
    for (int i = 0; i < cartsize; i++) {
        setcolor(11);
        cout << setw(3) << i + 1 << ". ";
        setcolor(7);
        cout << left << setw(25) << cart[i].itemname;
        setcolor(6);
        cout << right << setw(6) << cart[i].itemprice << " Rs" << endl;
    }
    setcolor(6);
    cout << "----------------------------------------\n";
    cout << fixed << setprecision(2);
    setcolor(6);
    cout << "Subtotal:                  " << setw(8) << subtotal << " Rs\n";
    cout << "Sales Tax (5%):            " << setw(8) << tax << " Rs\n";
    cout << "Service Charges (2%):      " << setw(8) << service << " Rs\n";
    setcolor(6);
    cout << "----------------------------------------\n";
    setcolor(6);
    cout << "Gross Total:               " << setw(8) << grosstotal << " Rs\n";
    cout << "Discount (15%):           -" << setw(8) << discount << " Rs\n";
    setcolor(6);
    cout << "========================================\n";
    setcolor(14);
    cout << "FINAL AMOUNT PAYABLE:      " << setw(8) << finalamount << " Rs\n";
    setcolor(6);
    cout << "========================================\n";
    setcolor(14);
    cout << "Payment Method:            " << setw(8) << "Cash\n";
    setcolor(6);
    cout << "----------------------------------------\n";
    setcolor(10);
    cout << "Thank you for dining with us!\n";
    cout << "Please visit again.\n";
    setcolor(6);
    cout << "========================================\n";
    
    // RESET CART
    cartsize = 0;

    setcolor(7);
    cout << "\nPress any key to return to main menu...";
    getch();
    system("cls");
    goto mainmenu;

    return 0;
}

//--------------------------------------
// MAIN
//--------------------------------------
int main() {
    srand(time(0));
    menu();
    return 0;
}
