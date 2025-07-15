# 🛠️ C++ User‑Manager CLI

A role‑based **User Management** console application written in modern **C++17**.  
It demonstrates classic OOP features—**inheritance, polymorphism, virtual destructors**—along with a clean menu‑driven UI.

---

## ✨ Features
| Capability | Details |
|------------|---------|
| **Register Users** | Create **Regular** or **Admin** accounts (enforced uniqueness) |
| **Login / Logout** | Authenticates against in‑memory store; tracks active session |
| **Role‑Based Access** | Admin‑only commands: list users, delete users |
| **User Info Summary** | `getUserInfo()` composes name, username, and role in one call |
| **OOP Showcase** | Abstract base `User`, derived `RegularUser` / `AdminUser`, virtual destructor |
| **Easy to Extend** | Code structured for quick swaps to smart pointers, file persistence, or hash maps |

---

## 🔧 Build & Run

> Requires a C++17‑compatible compiler (GCC ≥ 7, Clang ≥ 6, MSVC ≥ 19.14).

```bash
# Clone repository
git clone https://github.com/dhyeythummar09/CPP-User-Manager-CLI.git
cd cpp-user-manager-cli

# Compile
g++ -std=c++17 main.cpp -o usermgr

# Run
./usermgr
