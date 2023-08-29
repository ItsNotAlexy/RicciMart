#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>

using namespace std;

string ExtractFromReciept(const string &ReceiptVar);
string CheckCoupon(string code, const string *coupon);
string MakeReceipt(const string *products, const int *prices, const int *quantity, int n, bool discount);


int main()
{
    string products[5] = {"Chitato", "HappyTos", "Coca Cola", "Pepsi", "Cheetos"};
    string coupon[2] = {"SMARICCI2HEBAT", "SMARICCI2"};
    int prices[5] = {10000, 10000, 6000, 6000, 7000};
    int quantity[5] = {0, 0, 0, 0, 0};
    int total = 0;
    int choice = 0;
    int maxQuantity = 2;

    cout << "=============================" << endl;
    cout << "RicciMart Cashier System" << endl;
    cout << "=============================" << endl;
    cout << "Press 0 for exit" << endl;
    cout << "Press 8 for product list" << endl;
    cout << "=============================" << endl;

    while (true)
    {
        cout << "Enter Option: ";
        cin >> choice;

        if (choice == 8)
        {
            system("cls");

            cout << "=============================" << endl;
            cout << "Here is the product list : " << endl;
            cout << "=============================" << endl;
            for (int i = 0; i < 5; i++)
            {
                cout << i + 1 << ". " << products[i] << " - Rp" << prices[i] << endl;
            }
            cout << "Enter '0' to proceed to checkout" << endl;
            cout << "=============================" << endl;
            int ProductChoice = -1;

            while (ProductChoice != 0)
            {
                cout << "Please select a product : ";
                cin >> ProductChoice;

                if (ProductChoice == 0)
                {
                    cout << "=============================" << endl;
                    cout << "Here is your receipt : " << endl;
                    cout << MakeReceipt(products, prices, quantity, 5, false) << endl;
                    cout << "=============================" << endl;
                    cout << "Please enter your coupon code (use 'none' to exit): ";
                    string code;
                    cin >> code;
                    cout << "=============================" << endl;
                    bool isCoupon = false;

                    string IsValid = CheckCoupon(code, coupon);
                    if (IsValid == "Valid")
                    {
                        cout << "Here is your receipt with discount : " << endl;
                        cout << MakeReceipt(products, prices, quantity, 5, true) << endl;
                        isCoupon = true;
                    }
                    else
                    {
                        if (code == "none"){
                            cout << "Here is your receipt without discount : " << endl;
                            cout << MakeReceipt(products, prices, quantity, 5, false) << endl;
                        } else {
                            cout << "Your coupon is " << IsValid << endl;
                            cout << "Here is your receipt without discount : " << endl;
                            cout << MakeReceipt(products, prices, quantity, 5, false) << endl;
                        }
                    }
                    
                    cout << "=============================" << endl;
                    cout << "Input your payment : ";
                    int payment;
                    cin >> payment;
                    cout << "=============================" << endl;

                    string ReceiptVar;
                    string Total;
                    int IntTotal;

                    if(isCoupon == true){
                        ReceiptVar = MakeReceipt(products, prices, quantity, 5, true);
                        Total = ExtractFromReciept(ReceiptVar);
                        IntTotal = stoi(Total);
                    } else {
                        ReceiptVar = MakeReceipt(products, prices, quantity, 5, false);
                        Total = ExtractFromReciept(ReceiptVar);
                        IntTotal = stoi(Total);
                    }
                    

                    if (payment < IntTotal)
                    {
                        cout << "Your payment is not enough" << endl;
                        cout << "=============================" << endl;
                        return 0;
                    }
                    else
                    {
                        int change = 0;
                        if(IntTotal > payment){
                            change = IntTotal - payment;
                            cout << "Your change is Rp" << change << endl;
                            cout << "=============================" << endl;
                            cout << "Thank you for shopping at RicciMart" << endl;
                            cout << "=============================" << endl;
                            Sleep(2000);
                            return 0;
                        } else {
                            change = payment - IntTotal;
                            cout << "Your change is Rp" << change << endl;
                            cout << "=============================" << endl;
                            cout << "Thank you for shopping at RicciMart" << endl;
                            cout << "=============================" << endl;
                            Sleep(2000);
                            return 0;
                        }
                    }
                }
                else if (ProductChoice > 5)
                {
                    cout << "Invalid product, please try again" << endl;
                    cout << "=============================" << endl;
                }
                else
                {
                    int ItemQuantity = 0;
                    cout << "Enter quantity : ";
                    cin >> ItemQuantity;
                    cout << "=============================" << endl;

                    if(quantity[ProductChoice - 1] + ItemQuantity > maxQuantity)
                    {
                        cout << "You can only buy " << maxQuantity << " " << products[ProductChoice - 1] << endl;
                        cout << "=============================" << endl;
                    }
                    else
                    {
                        quantity[ProductChoice - 1] += ItemQuantity;
                        cout << "You have added " << ItemQuantity << " " << products[ProductChoice - 1] << endl;
                        cout << "=============================" << endl;
                    }
                }
            }
        }
        else
        {
            if (choice == 0)
            {
                cout << "Exiting..." << endl;
                Sleep(2000);
                break;
            }
            else
            {
                cout << "Invalid option, please try again" << endl;
            }
        }
    }
    return 0;
}

string CheckCoupon(string code, const string *coupon)
{
    int length = 5;
    for (int i = 0; i < length; i++)
    {
        if (code == coupon[i])
        {
            return "Valid";
        }
    }
    return "Invalid";
}

string MakeReceipt(const string *products, const int *prices, const int *quantity, int n, bool discount)
{
    string receipt = "";
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        if (quantity[i] > 0)
        {
            receipt += products[i] + " - " + to_string(quantity[i]) + " - Rp" + to_string(prices[i] * quantity[i]) + "\n";
            if (discount)
            {
                receipt += "Discount - 10%\n";
                total += prices[i] * quantity[i] * 0.9;
            }
            else
            {
                total += prices[i] * quantity[i];
            }
        }
    }
    receipt += "Total - Rp" + to_string(total) + "\n";
    return receipt;
}

string ExtractFromReciept(const string &ReceiptVar)
{
    string Total = "";
    int length = ReceiptVar.length();
    for (int i = 0; i < length; i++)
    {
        if (ReceiptVar[i] == 'T' && ReceiptVar[i + 1] == 'o' && ReceiptVar[i + 2] == 't' && ReceiptVar[i + 3] == 'a' && ReceiptVar[i + 4] == 'l')
        {
            for (int j = i + 8; j < length; j++)
            {
                if (isdigit(ReceiptVar[j]))
                {
                    Total += ReceiptVar[j];
                }
                else if (ReceiptVar[j] == '\n')
                {
                    break;
                }
            }
        }
    }
    return Total;
}
