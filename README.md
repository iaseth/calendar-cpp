
## **📆 Calendar CLI (C++)**
A simple **command-line calendar tool** written in **C++**, supporting multiple months, colored weekends, and flexible date inputs.

🔗 **GitHub Repository:** [iaseth/calendar-cpp](https://github.com/iaseth/calendar-cpp.git)

---

## **🚀 Features**
✅ Print the **calendar for any month and year**  
✅ Accepts **month as number or name (full/partial)**  
✅ Print **multiple months** using `-n` (e.g., next 3 months)  
✅ **Sundays in red** and **Saturdays in orange**  
✅ **Fully customizable and cross-platform**  

---

## **📥 Installation**
### **🔹 Clone the Repository**
```bash
git clone https://github.com/iaseth/calendar-cpp.git
cd calendar-cpp
```

### **🔹 Build Using CMake**
```bash
mkdir build && cd build
cmake ..
make
```
The compiled executable will be **`cal`** inside the `build/` directory.

---

## **📌 Usage**
### **🔹 Print Current Month**
```bash
./cal
```

### **🔹 Print a Specific Month**
```bash
./cal --month 5        # May of the current year
./cal -m October       # October of the current year
./cal -m Jan           # January of the current year
```

### **🔹 Print a Specific Year**
```bash
./cal --year 2024
./cal -y 2023
```

### **🔹 Print Multiple Months (`-n`)**
```bash
./cal -m 10 -y 2023 -n 5
```
🔹 **Prints:** **October 2023 → February 2024**.

### **🔹 Display Help**
```bash
./cal --help
```

---

## **🎨 Color Formatting**
- **🔴 Sundays are printed in red**  
- **🟠 Saturdays are printed in orange**  

🖥️ **Note:** Colors work in most **modern terminals**.

---

## **🔧 Development**
To modify the source, edit:
```
src/calendar.cpp
```
Then rebuild:
```bash
cd build
make
```

---

## **📜 License**
This project is **open-source** under the **MIT License**.  

Feel free to contribute! 🚀
