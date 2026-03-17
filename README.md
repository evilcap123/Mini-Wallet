# MiniWallet - UPI-Based Digital Wallet System

A C++ console application implementing a digital wallet system with UPI capabilities, user authentication, and transaction history management.

## Project Overview

MiniWallet is a simple yet functional wallet system that allows users to:

- Create secure wallet accounts with PIN protection
- Perform deposit and withdrawal operations
- Send money to other users (UPI transfers)
- View transaction history
- Persist data to files for persistence

---

## System Architecture

### Class Diagram

```
classDiagram
    class Account {
        #name: string
        #mobile: string
        #balance: double
        +Account(name, mobile, balance)
        +depo(amount): bool
        +withdraw(amount): bool
        +getBalance(): double
        +getMobile(): string
        +getName(): string
    }

    class UpiUser {
        -pin: int
        -history: vector~Transaction~
        +UpiUser(name, mobile, balance, pin)
        +verifyPin(enteredPin): bool
        +addTransaction(transaction): void
        +showHistory(n): void
        +setPin(newPin): void
        +getPin(): int
        +getTransaction(): vector~Transaction~
    }

    class Transaction {
        -type: string
        -otherUser: string
        -amount: double
        -timestamp: string
        +getCurrentTime(): string
        +Transaction(type, otherUser, amount, timestamp)
        +getTs(): string
        +getType(): string
        +getOtherUser(): string
        +getAmount(): double
    }

    class WalletSys {
        -users: vector~UpiUser~
        +CreateUser(): void
        +findUser(mobile): int
        +userDashboard(index): void
        +userLogin(): void
        +adminDashboard(index): void
        +deleteUser(mobile): bool
        +saveToFile(): void
        +LoadFromFile(): void
    }

    Account <|-- UpiUser
    UpiUser "1" --> "*" Transaction: contains
    WalletSys "1" --> "*" UpiUser: manages
```

---

## Application Workflow

### 1. Startup Flow

```
    A[Application Start] --> B[Load Users from File]
    B --> C{File Exists?}
    C -->|Yes| D[Load All Users]
    C -->|No| E[Start with Empty Wallet]
    D --> F[Show Main Menu]
    E --> F
```

### 2. Main Menu Flow

```
    A[Main Menu] --> B{User Choice}
    B -->|1| C[Create Wallet]
    B -->|2| D[Login]
    B -->|3| E[Exit]

    C --> F[Get User Details]
    F --> G[Create UpiUser]
    G --> H[Save to File]
    H --> A

    D --> I[Enter Mobile & PIN]
    I --> J{Credentials Valid?}
    J -->|Yes| K[User Dashboard]
    J -->|No| L[Login Failed]
    L --> A
    K --> A
```

### 3. User Dashboard Flow

```
    A[User Dashboard] --> B{User Choice}
    B -->|View Balance| C[Display Balance]
    B -->|Deposit| D[Enter Amount]
    B -->|Withdraw| E[Enter Amount]
    B -->|Transfer Money| F[Enter Recipient Mobile]
    B -->|View History| G[Display Transactions]
    B -->|Logout| H[Return to Main Menu]

    D --> I[Credit Account]
    E --> J[Debit Account]
    F --> K[Create Transaction]

    I --> L[Add to History]
    J --> L
    K --> L
    L --> M[Save to File]
    M --> A
```

### 4. Authentication & Security Flow

```
    A[User Login] --> B[Enter Mobile Number]
    B --> C{Mobile Exists?}
    C -->|No| D[Show Error]
    D --> E[Return to Main Menu]
    C -->|Yes| F[Enter PIN]
    F --> G{PIN Correct?}
    G -->|No| H[Authentication Failed]
    H --> E
    G -->|Yes| I[Access Granted]
    I --> J[Load User Dashboard]
```

---

## Data Structures

### Account (Base Class)

- **name**: User's full name
- **mobile**: Unique mobile number (acts as username)
- **balance**: Current account balance

### UpiUser (Derived from Account)

- **pin**: 4-digit PIN for authentication
- **history**: Vector of all transactions

### Transaction

- **type**: "DEPOSIT", "WITHDRAW", "TRANSFER"
- **otherUser**: Name/mobile of other party in transaction
- **amount**: Transaction amount
- **timestamp**: Auto-generated timestamp

### WalletSys

- **users**: Vector storing all registered UPI users

---

## File Persistence

### Data Storage

- **users.txt**: Stores user account data (name, mobile, balance, pin)
- **transactions.txt**: Stores all transaction records

### Save/Load Operations

- Data is automatically saved after every transaction
- Users are loaded from file on application startup
- Transaction history is maintained across sessions

---

## Key Features

 **User Authentication**: PIN-based security  
 **Transaction Management**: Complete transaction history with timestamps  
 **Persistent Storage**: Data saved and loaded from files  
 **Balance Management**: Deposit and withdrawal operations  
 **User-Friendly**: Console-based menu system

---

## Files Structure

```
MiniWallet/
├── Account.h              # Base account class
├── Account.cpp
├── UPIUser.h              # UPI user (derived class)
├── UPIUser.cpp
├── Transaction.h          # Transaction record class
├── Transaction.cpp
├── WalletSystem.h         # Main wallet system manager
├── WalletSystem.cpp
├── main.cpp               # Application entry point
├── users.txt              # User data file (generated)
├── transactions.txt       # Transaction log file (generated)
└── README.md              # This file
```

---

## Usage Example

```
====== MINI WALLET ======
1. Create Wallet
2. Login
3. Exit
Enter choice: 1

Enter Name: John Doe
Enter Mobile: 9876543210
Enter Initial Balance: 5000
Enter PIN: 1234

User created successfully!

====== MINI WALLET ======
1. Create Wallet
2. Login
3. Exit
Enter choice: 2

Enter Mobile: 9876543210
Enter PIN: 1234

Welcome John Doe! Balance: 5000
```

---

## Design Patterns Used

1. **Inheritance**: `UpiUser` inherits from `Account`
2. **Composition**: `WalletSys` composes multiple `UpiUser` objects
3. **Encapsulation**: Private data members with public accessors
4. **Single Responsibility**: Each class has a clear, focused purpose

---

## Future Enhancements

- [ ] Admin dashboard with user management
- [ ] Peer-to-peer transfers between accounts
- [ ] Transaction filters and search
- [ ] Database integration
- [ ] Email/SMS notifications
- [ ] Advanced security (encryption, OTP)

---

## Author

MiniWallet - A simple UPI wallet system in C++


Made_by/
├──Archit Singhal
├──Dhairya Bhardwaj
├──Parav Rana
├──Sanskriti

