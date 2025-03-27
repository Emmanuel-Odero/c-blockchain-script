# Simple Blockchain Implementation in C++

This project is a basic blockchain implementation written in C++. It simulates a simple blockchain with Proof of Work (PoW) mining, allowing transactions to be recorded in blocks that are securely linked together.

## Features
- **Block Structure**: Each block contains an index, timestamp, transaction data, hash, and a reference to the previous block.
- **Proof of Work (PoW)**: Uses a mining mechanism where a valid hash must start with a specified number of leading zeros.
- **Blockchain Integrity Check**: Ensures that the blockchain is valid by verifying hashes and links between blocks.
- **Genesis Block**: Initializes the blockchain with the first block.
- **SHA-256 Hashing**: Uses OpenSSL for secure hash generation.

## Prerequisites
To compile and run this project, you need:
- C++ compiler (e.g., g++)
- OpenSSL library (for SHA-256 hashing)

### Install OpenSSL (if not installed)
```sh
sudo apt-get install libssl-dev  # For Linux
brew install openssl  # For macOS
```

## Compilation and Execution
Compile the program using g++:
```sh
g++ -o blockchain blockchain.cpp -lssl -lcrypto
```
Run the executable:
```sh
./blockchain
```

## Code Structure
### `Block` Class
Represents a block in the blockchain:
- `calculateHash()`: Computes SHA-256 hash of the block.
- `mineBlock(int difficulty)`: Mines a block by solving Proof of Work.
- `getHash()`, `getPreviousHash()`, and `getData()`: Retrieve block information.

### `Blockchain` Class
Manages the entire blockchain:
- `createGenesisBlock()`: Creates the first block.
- `addBlock(string data)`: Adds a mined block to the chain.
- `isChainValid()`: Checks blockchain integrity.
- `printChain()`: Displays all blocks.

### `main()` Function
- Initializes the blockchain.
- Adds and mines new blocks.
- Prints the blockchain and validates its integrity.

## Example Output
```sh
Mining block 1...
Block mined! Hash: 0000abcd... Nonce: 12345

Mining block 2...
Block mined! Hash: 0000efgh... Nonce: 67890

Blockchain contents:
Block 0 [Hash: abc123..., PrevHash: 0, Data: Genesis Block]
Block 1 [Hash: 0000abcd..., PrevHash: abc123..., Data: Transaction 1]
Block 2 [Hash: 0000efgh..., PrevHash: 0000abcd..., Data: Transaction 2]

Is blockchain valid? Yes
```

## Future Improvements
- Implement decentralized peer-to-peer networking.
- Add digital signatures for transactions.
- Optimize mining process for efficiency.
