#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <iomanip>
#include <random>
#include <cmath>
#include <algorithm>

using namespace std;

 enum class Side{BUY , SELL};

 struct Order
 {
    int orderid;
    Side side;
    double price;
    int quantity;

    Order (int id,Side s,double p,int q)
    {
        orderid=id;
        side=s;
        price=p;
        quantity=q;
    }
 };

 map<double , queue<Order>> asks;
 map<double , queue<Order> , greater<double>> bids;
 
 void addorder(Order neworder)
 {
    if(neworder.side==Side::BUY)
    {
        if(asks.empty())
        {
         bids[neworder.price].push(neworder);
         return;
        }
        while(neworder.quantity>0 && !asks.empty())
        {
         double cheapestsellerprice = asks.begin()->first;
         if(cheapestsellerprice>neworder.price)
         {
            break;
         }

           Order& frontseller = asks.begin()->second.front();
           int tradedshares = min(neworder.quantity, frontseller.quantity);

           neworder.quantity -= tradedshares;
            frontseller.quantity -= tradedshares;

            cout << "\033[32m[MATCH]\033[0m Trade Executed: " << tradedshares 
                 << " shares at $" << fixed << setprecision(2) << cheapestsellerprice << endl;

                 if (frontseller.quantity == 0)
                  {
                asks.begin()->second.pop();
            }
            if (asks.begin()->second.empty())
             {
                asks.erase(asks.begin());
            }
        }

            if (neworder.quantity > 0)
             {
            bids[neworder.price].push(neworder);
        }

    }
    else if (neworder.side == Side::SELL) {
        if (bids.empty()) {
            asks[neworder.price].push(neworder);
            return;
        }

        while (neworder.quantity > 0 && !bids.empty()) {
            double highestbuyerprice = bids.begin()->first;
            
            if (highestbuyerprice < neworder.price) {
                break;
            }

            Order& frontbuyer = bids.begin()->second.front();
            int tradedshares = min(neworder.quantity, frontbuyer.quantity);
            
            neworder.quantity -= tradedshares;
            frontbuyer.quantity -= tradedshares;

            cout << "\033[32m[MATCH]\033[0m Trade Executed: " << tradedshares 
                 << " shares at $" << fixed << setprecision(2) << highestbuyerprice << endl;

            if (frontbuyer.quantity == 0) {
                bids.begin()->second.pop();
            }
            if (bids.begin()->second.empty()) {
                bids.erase(bids.begin());
            }
        }
         if (neworder.quantity > 0) {
            asks[neworder.price].push(neworder);
        }
      }


 }

void printBook() {
    cout << "\n=======================================" << endl;
    cout << "   NASDAQ C++ LIMIT ORDER BOOK (LOB)   " << endl;
    cout << "=======================================" << endl;
    
    cout << "\033[31m  [ASKS] - Sellers\033[0m" << endl;
    
    for (auto it = asks.rbegin(); it != asks.rend(); ++it) {
        int totalShares = 0;
        queue<Order> tempQueue = it->second;
        
        while (!tempQueue.empty()) {
            totalShares += tempQueue.front().quantity;
            tempQueue.pop();
        }
        cout << "  $" << fixed << setprecision(2) << setw(7) << left << it->first 
             << " | Vol: " << totalShares << endl;
    }

    cout << "---------------------------------------" << endl;
    
    cout << "\033[32m  [BIDS] - Buyers\033[0m" << endl;
    
    for (auto it = bids.begin(); it != bids.end(); ++it) {
        int totalShares = 0;
        queue<Order> tempQueue = it->second;
        
        while (!tempQueue.empty()) {
            totalShares += tempQueue.front().quantity;
            tempQueue.pop();
        }
        cout << "  $" << fixed << setprecision(2) << setw(7) << left << it->first 
             << " | Vol: " << totalShares << endl;
    }
    cout << "=======================================\n" << endl;
}

int main()
{
    random_device rd;
    mt19937 generator(rd());

    // Setup distributions
    normal_distribution<double> priceDist(150.0, 2.0); // Bell curve around $150.00
    uniform_int_distribution<int> qtyDist(1, 10);      // Random multiplier for shares
    uniform_int_distribution<int> sideDist(0, 1);      // 50/50 Coin Flip (0 or 1)

    cout << "INITIALIZING HIGH-FREQUENCY TRADING SIMULATION...\n" << endl;

    // Simulating 75 rapid-fire Wall Street orders
    for (int i = 1; i <= 75; i++) {

        Side randomSide = (sideDist(generator) == 0) ? Side::BUY : Side::SELL;

        double randomPrice = round(priceDist(generator) * 100.0) / 100.0;

        int randomQty = qtyDist(generator) * 10; 

        Order generatedOrder(i, randomSide, randomPrice, randomQty);

        addorder(generatedOrder);
    }

    printBook();

    return 0;
}