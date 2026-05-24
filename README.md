# 🚗 Example: Binary CAN Frame → Parsed Output

This project includes a minimal CAN frame deserializer that converts a raw binary buffer into a structured `CanFrame` object.

### **Input buffer (raw CAN frame)**

```
12 34 56 78 04 AA BB CC
```

This represents:

- **ID**: `0x12345678`  
- **DLC**: `0x04`  
- **Data bytes**: `AA BB CC` (remaining bytes padded with `00`)

---

### **Parsed output**

```text
{
  id: 0x12345678,
  dlc: 4,
  data: [AA, BB, CC, 00]
}
```

This is exactly what the parser returns internally and what the unit tests print to the terminal and CI logs.

---

# 🧪 Test Output (Local + CI)

When running tests locally or in GitHub Actions, you will see output like:

```
Input buffer:
12 34 56 78 04 AA BB CC

Output struct:
ID=0x12345678
DLC=4
Data=[AA BB CC 00]
```

# 🛠 How it works

The parser reads:

1. **4 bytes → 32‑bit CAN ID (big‑endian)**  
2. **1 byte → DLC**  
3. **N bytes → Data payload**  
4. Pads remaining bytes with `0x00` to reach 8 bytes  

This matches typical automotive ECU expectations.

---

# 📦 Running the tests

```
cmake -S . -B build
cmake --build build
./build/tests
```

GitHub Actions runs the same tests automatically on:

- Ubuntu  
- Windows  
- macOS
