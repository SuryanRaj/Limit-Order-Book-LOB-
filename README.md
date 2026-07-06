High-Frequency Trading Limit Order Book (LOB) Engine 📈⚡

A lightning-fast, native C++ matching engine that simulates the core architectural logic of modern financial stock exchanges (like the NASDAQ and NYSE).

This project is a fully functional algorithmic trading engine built entirely from scratch using the C++ Standard Template Library (STL). It utilizes advanced data structures to achieve strict Price-Time Priority, efficiently matching chaotic, rapid-fire buy and sell orders in a simulated High-Frequency Trading (HFT) environment.

🚀 The Core Architecture

To process trades efficiently without relying on slow arrays, this engine leverages highly optimized data structures:

•Red-Black Trees (std::map): The order books are built on associative containers that guarantee O(log N) time complexity for insertions and lookups.

   •The Ask Book (Sellers) automatically sorts orders from lowest to highest price.

   •The Bid Book (Buyers) uses std::greater<double> to invert the sorting, ensuring the highest-paying buyers are always prioritized at the top.

•FIFO Queues (std::queue): To enforce absolute fairness, every specific price level contains a queue. If multiple traders bid the exact same price, the engine uses First-In-First-Out logic to reward whoever's signal arrived first.

•Memory-Safe Execution: The matching loop utilizes memory references (&) to instantly execute partial and full order fills without creating artificial data or causing memory leaks.

🛠️ Features

•Dynamic Bid-Ask Spread: Automatically calculates and isolates the spread between the highest buyer and the lowest seller.

•Algorithmic Order Matching: Safely computes intersection volumes using std::min() to handle partial fills flawlessly.

•Hardware-Seeded Market Chaos: Uses C++ <random> (std::random_device and the std::mt19937 Mersenne Twister) to bombard the engine with random, Bell-Curve distributed market orders to stress-test the state machine.

•ANSI Color-Coded UI: A custom-built, real-time terminal dashboard that prints executed trades in green and perfectly renders the surviving order book with calculated volumes.

💻 How to Compile and Run

This project requires absolutely zero external libraries or dependencies. It runs on pure, standard C++.

1. Clone the repository:

git clone [https://github.com/YOUR_USERNAME/YOUR_REPOSITORY_NAME.git](https://github.com/YOUR_USERNAME/YOUR_REPOSITORY_NAME.git)
cd YOUR_REPOSITORY_NAME


2. Compile the C++ code:
(Ensure you have a C++ compiler like GCC/G++ installed)

g++ limit_order_book.cpp -o engine


3. Run the executable:

# On Mac/Linux:
./engine

# On Windows:
engine.exe


🧠 Technical Skills Demonstrated

Languages: C++

Systems Engineering: Memory Management, Pointers/References, State Machines.

Computer Science: Big-O Time Complexity, Data Structures (Maps, Queues), Algorithms.

Quantitative Finance: Limit Order Books, Price-Time Priority, Bid-Ask Spreads, Market Microstructure.

Created as a deep dive into the intersection of Computer Science and Quantitative Finance.
