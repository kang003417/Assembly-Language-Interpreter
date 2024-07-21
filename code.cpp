#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

class StringUtils {
public:
    static string trim(const string &str) {
        stringstream ss(str);
        string word;
        while (getline(ss, word, ' ')) {
            word = trimleft(word);
            word = trimright(word);
        }
        return word;
    }

    static string trimleft(const string &str) {
        string trimmedStr = str;
        while (!trimmedStr.empty() && trimmedStr[0] == ' ') {
            trimmedStr = trimmedStr.substr(1);
        }
        if (!trimmedStr.empty() && trimmedStr[0] == ',') {
            trimmedStr.erase(0, 1);
        }
        return trimmedStr;
    }

    static string trimright(const string &str) {
        string trimmedStr = str;
        while (!trimmedStr.empty() && trimmedStr[trimmedStr.length() - 1] == ' ') {
            trimmedStr = trimmedStr.substr(0, trimmedStr.length() - 1);
        }
        if (!trimmedStr.empty() && trimmedStr.back() == ',') {
            trimmedStr.pop_back();
        }
        return trimmedStr;
    }
};
string decToBinary(int n) {
    string binary = "";
    while (n > 0) {
        binary = to_string(n % 2) + binary;
        n /= 2;
    }
    return binary;
}

// Function to convert binary to decimal
int binaryToDec(const string& binary) {
    int decimal = 0;
    for (char bit : binary) {
        decimal = decimal * 2 + (bit - '0');
    }
    return decimal;
}

// Function to perform left shift
string leftShift(const string& binary, int shift) {
    string shiftedBinary = binary.substr(shift) + string(shift, '0');
    return shiftedBinary;
}

// Function to perform right shift
string rightShift(const string& binary, int shift) {
    string shiftedBinary = string(shift, '0') + binary.substr(0, binary.size() - shift);
    return shiftedBinary;
}
bool allDigits(const string& str) {
    for (char ch : str) {
        if (ch < '0' || ch > '9') {
            return false;
        }
    }
    return true;
}
string trim(string str);
string trimleft(string str);
string trimright(string str);

void main_process(const string &op_word, const string &arg1, const string arg2);
void func_IN(const string &arg1);
void func_OUT(const string &arg1);
void func_MOV(const string &arg1, const string &arg2);
void func_ADD(const string &arg1, const string &arg2);
void func_SUB(const string &arg1, const string &arg2);
void func_MUL(const string &arg1, const string &arg2);
void func_DIV(const string &arg1, const string &arg2);
void func_INC(const string &arg1);
void func_DEC(const string &arg1);
void func_ROL(const string &arg1, const string &arg2);
void func_ROR(const string &arg1, const string &arg2);
void func_SHL(const string &arg1, const string &arg2);
void func_SHR(const string &arg1, const string &arg2);
void func_LOAD(const string &arg1, const string &arg2);
void func_STORE(const string &arg1, const string &arg2);

unsigned int counter = 0;
unsigned char reg[8] = {0}; 
int flags[4] = {0, 0, 0, 0};
unsigned char memory[64] = {0};
bool OF[7] = {false}; 
bool ZF[7] = {false};
bool CF[7] = {false}; 
bool UF[7] = {false}; 

int main() {
    
    int decimalNumber = 10;
    int shiftAmount = 2;
    string thefile;
    ifstream file;
    string line;

    string binary = decToBinary(decimalNumber);
    
    // Left shift
    string leftShiftedBinary = leftShift(binary, shiftAmount);
    int leftShiftedDecimal = binaryToDec(leftShiftedBinary);

    // Right shift
    string rightShiftedBinary = rightShift(binary, shiftAmount);
    int rightShiftedDecimal = binaryToDec(rightShiftedBinary);
    
    file.open("file.asm");
    if (file.fail()) {
        cout << "Cannot Open File" << endl;
        return -1;
    }

    while (getline(file, line)) {
        stringstream lineStream(line);
        string op_word, arg1, arg2 = "";
        lineStream >> op_word >> arg1 >> arg2;
        
        op_word = StringUtils::trim(op_word);
        arg1 = StringUtils::trim(arg1);
        arg2 = StringUtils::trim(arg2);

        main_process(op_word, arg1, arg2);
        counter++;
    }

    cout << "Register :";
    for (unsigned int i = 0; i < 8; i++) {
        cout << setw(2) << setfill('0') << static_cast<int>(reg[i]);
        if (i < 7) {
            cout << " ";
        }
    }
    cout << "#" << endl;

    bool cf = 0, of = 0, zf = 0, uf = 0;
    for (int i = 0; i < 7; i++)
    {
        if (CF[i])
        {
        cf = true;
        break;
        }
    }
    for (int i = 0; i < 7; i++)
    {
        if (ZF[i])
        {
        zf = true;
        break;
        }
    }
    for (int i = 0; i < 7; i++)
    {
        if (OF[i])
        {
        of = true;
        break;
        }
    }
    for (int i = 0; i < 7; i++)
    {
        if (UF[i]) 
        {
            uf = true;
            break;
        }
    }

    
    cout << "Flags\t: " << cf << " " << of << " " << uf << " " << zf << "#" << endl;

    cout << "PC\t:" << counter << endl;

    cout << endl << endl;
    
    cout << "Memory" << ":" << endl;
    
    for (unsigned int i = 0; i < 64; i++){
        cout << setw(2) << setfill('0') << static_cast<int>(memory[i]) << " ";
        if ((i + 1) % 8 == 0){
        cout << endl;
        }
    }
    cout << "#" << endl;
    return 0;
}

void main_process(const string &op_word, const string &arg1, const string arg2)
{
  cout << "op_wor: " << op_word << ", arg1: " << arg1 << ", arg2: " << arg2 << endl;
  if (op_word == "IN")
  {
    func_IN(arg1);
  }
  else if (op_word == "OUT")
  {
    func_OUT(arg1);
  }
  else if (op_word == "MOV")
  {
    func_MOV(arg1, arg2);
  }
  else if (op_word == "ADD")
  {
    func_ADD(arg1, arg2);
  }
  else if (op_word == "SUB")
  {
    func_SUB(arg1, arg2);
  }
  else if (op_word == "MUL")
  {
    func_MUL(arg1, arg2);
  }
  else if (op_word == "DIV")
  {
    func_DIV(arg1, arg2);
  }
  else if (op_word == "INC")
  {
    func_INC(arg1);
  }
  else if (op_word == "DEC")
  {
    func_DEC(arg1);
  }
  else if (op_word == "ROL")
  {
    func_ROL(arg1, arg2);
  }
  else if (op_word == "ROR")
  {
    func_ROR(arg1, arg2);
  }
  else if (op_word == "SHL")
  {
    func_SHL(arg1, arg2);
  }
  else if (op_word == "SHR")
  {
    func_SHR(arg1, arg2);
  }
  else if (op_word == "LOAD")
  {
    func_LOAD(arg1, arg2);
  }
  else if (op_word == "STORE")
  {
    func_STORE(arg1, arg2);
  }
  else
  {
    cout << "Unknown op_word: " << op_word << endl;
    exit(0);
  }
}


void func_IN(const string &arg1){
    int value = 0;
    unsigned int operand = stoi(arg1.substr(1, 1));
    if (arg1[0] == 'R' && operand >= 0 && operand <= 7){
        cout << "Please enter a value: ";
        cin >> value;
        if (value > 127){
            flags[0]++;
        }else if(value < -128){
            flags[1]++;
        }else if(value == 0){
            flags[3]++;
        }else if(value <= 127 && value >= -128) {
            reg[operand] = value;
        }else{
            throw invalid_argument("Invalid arguments for IN operation");
        }      
    }
}


void func_OUT(const string &arg1)
{
  if (arg1.substr(0, 1) == "R" && arg1.length() == 2 && isdigit(arg1[1]))
    {
        unsigned int regIndex = arg1[1] - '0';
        if (regIndex >= 0 && regIndex < 8)
        {
            cout << arg1 << ": " << static_cast<int>(reg[regIndex]) << endl;
        }
        else
        {
            throw invalid_argument("Invalid register index");
        }
    }
    else
    {
        throw invalid_argument("Invalid arguments for OUT operation");
    }
}

void func_MOV(const string &arg1, const string &arg2)
{
    if (isdigit(arg1[0]) && arg2[0] == 'R' && arg2.length() == 2 && isdigit(arg2[1]))
    {
        unsigned int value = stoi(arg1);
        unsigned int regIndex = arg2[1] - '0';

        if (regIndex >= 0 && regIndex < 8)
        {
            reg[regIndex] = value;
            cout << "Value " << value << " stored in register R" << regIndex << endl;
            return;
        }
        else
        {
            throw invalid_argument("Invalid register index");
        }
    }
    else if (arg1[0] == 'R' && arg1.length() == 2 && isdigit(arg1[1]) && arg2[0] == 'R' && arg2.length() == 2 && isdigit(arg2[1]))
    {
        // Handle register-to-register move operation
        unsigned int srcRegIndex = arg1[1] - '0';
        unsigned int destRegIndex = arg2[1] - '0';

        if (srcRegIndex >= 0 && srcRegIndex < 8 && destRegIndex >= 0 && destRegIndex < 8)
        {
            reg[destRegIndex] = reg[srcRegIndex];
            cout << "Value " << reg[srcRegIndex] << " copied from R" << srcRegIndex << " to R" << destRegIndex << endl;
            return;
        }
        else
        {
            throw invalid_argument("Invalid register index");
        }
    }
    else if (arg1[0] == '[' && arg1[arg1.length() - 1] == ']' && arg2[0] == 'R' && arg2.length() == 2 && isdigit(arg2[1]))
    {
        string memAddressStr = arg1.substr(2, arg1.length() - 3); 
        unsigned int memAddress = stoi(memAddressStr);

        if (memAddress >= 0 && memAddress < 64)
        {
            // Extract register index from arg2
            unsigned int regIndex = arg2[1] - '0';
            if (regIndex >= 0 && regIndex < 8)
            {
                // Move value from memory to register
                reg[regIndex] = reg[memAddress];
                cout << "Value " << static_cast<int>(reg[memAddress]) << " moved from 'R' " << memAddress << " to R" << regIndex << endl;
                return;
            }
            else
            {
                throw invalid_argument("Invalid register index");
            }
        }
        else
        {
            throw invalid_argument("Invalid memory address");
        }
    }
}



void func_ADD(const string &arg1, const string &arg2) {
    unsigned int op1 = arg1[1] - '0';
    unsigned int op2 = arg2[1] - '0';

    if (arg1[0] == 'R' && op1 >= 0 && op1 < 8 &&
        arg2[0] == 'R' && op2 >= 0 && op2 < 8) {
        int result = static_cast<int>(reg[op2]) + static_cast<int>(reg[op1]);
        reg[op2] = static_cast<unsigned char>(result);
        if (result > 127 || result < -128) {
            flags[0]++; 
        } else if (result == 0) {
            flags[3]++; 
        }
    } else if (arg1[0] == 'R' && op1 >= 0 && op1 < 8 &&
               isdigit(arg2[0])) {
        int value2 = stoi(arg2);
        int result = static_cast<int>(reg[op1]) + value2;
        reg[op1] = static_cast<unsigned char>(result);
        if (result > 127 || result < -128) {
            flags[0]++; 
        } else if (result == 0) {
            flags[3]++; 
        }
    } else {
        throw invalid_argument("Invalid arguments for ADD operation");
    }
}


void func_SUB(const string &arg1, const string &arg2) {
    int op1 = arg1[1] - '0';
    int op2 = arg2[1] - '0';

    if (arg1[0] == 'R' && arg2[0] == 'R' && op1 >= 0 && op1 < 8 && op2 >= 0 && op2 < 8) {
        int result = static_cast<int>(reg[op2]) - static_cast<int>(reg[op1]);
        reg[op2] = static_cast<unsigned char>(result);
        if (result > 127 || result < -128) {
            flags[0]++; 
        } else if (result == 0) {
            flags[3]++; 
        }
    } else if (arg1[0] == 'R' && isdigit(arg2[0])) {
        int value2 = stoi(arg2);
        int result = static_cast<int>(reg[op1]) - value2;
        reg[op1] = static_cast<unsigned char>(result);
        if (result > 127 || result < -128) {
            flags[0]++; 
        } else if (result == 0) {
            flags[3]++; 
        }
    } else {
        throw invalid_argument("Invalid arguments for SUB operation");
    }
}


void func_MUL(const string &arg1, const string &arg2) {
        unsigned int op1 = arg1[1] - '0'; 
        unsigned int op2 = arg2[1] - '0'; 
    
    if (arg1[0] == 'R' && arg2[0] == 'R' && op1 >= 0 && op1 < 8 && op2 >= 0 && op2 < 8) {
        reg[op2] *= reg[op1]; 
        int result = reg[op2];
        if (result > 127) {
            flags[0]++; 
        } else if (result < -128) {
            flags[1]++; 
        } else if (result == 0) {
            flags[3]++; 
        } else if (result <= 127 && result >= -128) {
            return; 
        } else {
            cout << "Wrong Input !!" << endl;
            exit(1);
        }
    }    else if (arg1[0] == 'R' && isdigit(arg2[0])) {
        int value2 = stoi(arg2);
            reg[op1] = reg[op1] * value2;
            int result = reg[op1];
            if (result > 127) {
                flags[0]++; 
            } else if (result < -128) {
                flags[1]++; 
            } else if (result == 0) {
                flags[3]++; 
            }
    } else {
        cout << "Wrong Input!!" << endl;
        exit(1);
    }
}


void func_DIV(const string &arg1, const string &arg2) {
    unsigned int op1 = arg1[1] - '0'; 
    unsigned int op2 = arg2[1] - '0'; 

    if (arg1[0] == 'R' && arg2[0] == 'R' && op1 >= 0 && op1 < 8 && op2 >= 0 && op2 < 8) {
        if (reg[op1] == 0) {
            cout << "Division at zero worng !!" << endl;
            exit(1);
        }
        reg[op2] = reg[op2] / reg[op1];
        int result = reg[op2];
        if (result > 127) {
            flags[0]++; 
        } else if (result < -128) {
            flags[1]++; 
        } else if (result == 0) {
            flags[3]++; 
        }
    } else if (arg1[0] == 'R' && isdigit(arg2[0])) {
        int value2 = stoi(arg2);
        if (value2 == 0) {
            cout << "Division at zero wrong !!" << endl;
            exit(1);
        }
        else if(value2 != 0)
        {
            reg[op1] = reg[op1] / value2;
            int result = reg[op1];
            if (result > 127) {
                flags[0]++; 
            } else if (result < -128) {
                flags[1]++; 
            } else if (result == 0) {
                flags[3]++; 
            }
        }
    } else {
        throw invalid_argument("Invalid arguments for DIV operation");
    }
}


void func_INC(const string &arg1){
    unsigned int op1 = stoi(arg1.substr(1, 1));
    if (arg1[0] == 'R' && op1 >= 0 && op1 <= 7){
        reg[op1] += 1;
        unsigned int value = reg[op1];
        if (value > 127){
            flags[0]++;
        }else if(value < -128){
            flags[1]++;
        }else if(value == 0){
            flags[3]++;
        }else if(value <= 127 && value >= -128) {
            return;
        }else{
            throw invalid_argument("Invalid arguments for INC operation");
        }      
    }
}


void func_DEC(const string &arg1){
    unsigned int op1 = stoi(arg1.substr(1, 1));
    if (arg1[0] == 'R' && op1 >= 0 && op1 <= 7){
        reg[op1] -= 1;
        unsigned int value = reg[op1];
        if (value > 127){
            flags[0]++;
        }else if(value < -128){
            flags[1]++;
        }else if(value == 0){
            flags[3]++;
        }else if(value <= 127 && value >= -128) {
            return;
        }else{
            throw invalid_argument("Invalid arguments for DEC operation");
        }      
    }
}

void func_ROL(const string &arg1, const string &arg2) {
    unsigned int regIndex = stoi(arg1.substr(1, 1));
    int rotationCount = stoi(arg2);

    if (arg1[0] == 'R' && regIndex >= 0 && regIndex < 8 && rotationCount >= 0 && rotationCount <= 7) {
        rotationCount %= 8; 
        reg[regIndex] = (reg[regIndex] << rotationCount) | (reg[regIndex] >> (8 - rotationCount));
        reg[regIndex] &= 0xFF;
    } else {
        throw invalid_argument("Invalid arguments for ROL operation");
    }
}


void func_ROR(const string &arg1, const string &arg2){
    unsigned int op1 = stoi(arg1.substr(1, 1));
    if (arg1[0] == 'R' && op1 >= 0 && op1 <= 6)
    {
        int rotate = stoi(arg2);
        int a = reg[op1] >> rotate;
        int b = reg[op1] << (8 - rotate);
        reg[op1] = b | a;
    }
}

void func_SHL(const string &arg1, const string &arg2){
    unsigned int op1 = stoi(arg1.substr(1, 1));
    if (arg1[0] == 'R' && op1 >= 0 && op1 <= 6)
    {
        int shift = stoi(arg2);
        reg[op1] = reg[op1] << shift;
    }
}

void func_SHR(const string &arg1, const string &arg2){
    unsigned int op1 = stoi(arg1.substr(1, 1));
    if (arg1[0] == 'R' && op1 >= 0 && op1 <= 6)
    {
        int shift = stoi(arg2);
        reg[op1] = reg[op1] >> shift;
    }
}

void func_LOAD(const string &arg1, const string &arg2) {
    unsigned int regIndex = arg1[1] - '0'; // Extract register index from arg1
    int memAddr = 0;
    
    if (arg2[0] == '[' && arg2[arg2.length() - 1] == ']') {
        // Extract memory address from arg2 if it's in the form [Rn]
        int regIndex2 = arg2[2] - '0'; // Extract register index from arg2
        memAddr = reg[regIndex2];
    } else {
        // Convert arg2 to integer if it's a direct memory address
        memAddr = stoi(arg2);
    }
    
    // Check if the memory address is valid
    if (memAddr >= 0 && memAddr < 64) {
        // Load value from memory into the specified register
        reg[regIndex] = memory[memAddr];
    } else {
        throw invalid_argument("Invalid memory address");
    }
}


void func_STORE(const string &arg1, const string &arg2)
{
    if (arg1[0] == 'R')
    {
        // Extract register index from arg1
        unsigned int regIndex = arg1[1] - '0';
        
        if (regIndex >= 0 && regIndex < 8)
        {
            if (arg2[0] == '[' && arg2[arg2.length() - 1] == ']') // Check if arg2 is in the format [Rx]
            {
                // Extract register index from arg2
                unsigned int memRegIndex = arg2[2] - '0';
                unsigned int memAddress = reg[memRegIndex]; // Extract memory address from register

                // Check if the memory address is within bounds
                if (memAddress >= 0 && memAddress < 64)
                {
                    // Store value from register to memory
                    memory[memAddress] = reg[regIndex];
                    cout << "Value " << static_cast<int>(reg[regIndex]) << " stored in memory address " << memAddress << endl;
                    
                    // Also keep the value in register if it's different from the memory address
                    if (regIndex != memRegIndex)
                    {
                        reg[regIndex] = memory[memAddress];
                        cout << "Value " << static_cast<int>(memory[memAddress]) << " loaded into register R" << regIndex << endl;
                    }

                    return;
                }
                else
                {
                    throw invalid_argument("Invalid memory address");
                }
            }
            else if (isdigit(arg2[0])) // Check if arg2 is a direct memory address
            {
                size_t found = arg2.find_first_of("0123456789");
                unsigned int memAddress = stoi(arg2.substr(found)); // Extract memory address from arg2

                // Check if the memory address is within bounds
                if (memAddress >= 0 && memAddress < 64)
                {
                    // Store value from register to memory
                    memory[memAddress] = reg[regIndex];
                    cout << "Value " << static_cast<int>(reg[regIndex]) << " stored in memory address " << memAddress << endl;
                    
                    // Also keep the value in register if it's different from the memory address
                    if (regIndex != memAddress)
                    {
                        reg[regIndex] = memory[memAddress];
                        cout << "Value " << static_cast<int>(memory[memAddress]) << " loaded into register R" << regIndex << endl;
                    }

                    return;
                }
                else
                {
                    throw invalid_argument("Invalid memory address");
                }
            }
            else
            {
                throw invalid_argument("Invalid memory address format: " + arg2);
            }
        }
        else
        {
            throw invalid_argument("Invalid register index");
        }
    }
    else
    {
        throw invalid_argument("Invalid STORE operation: " + arg1 + ", " + arg2);
    }
}

