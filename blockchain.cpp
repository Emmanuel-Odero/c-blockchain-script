#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

// Block class represents a single block in the blockchain
class Block {
private:
    int index;                 // Position of the block in the blockchain
    std::string previousHash;  // Hash of the previous block (for linking blocks)
    std::string data;          // Block's data (e.g., transaction details)
    std::string hash;          // Hash of this block (computed using SHA-256)
    time_t timestamp;          // Time when the block was created
    int nonce;                 // A number used for mining (Proof of Work)

public:
    // Constructor to create a new block
    Block(int idx, std::string prevHash, std::string blockData) 
        : index(idx), previousHash(prevHash), data(blockData), timestamp(std::time(nullptr)), nonce(0) {
        hash = calculateHash(); // Compute initial hash of the block
    }

    // Computes the SHA-256 hash of the block’s contents
    std::string calculateHash() const {
        std::stringstream ss;
        ss << index << previousHash << data << timestamp << nonce;
        std::string input = ss.str(); // Concatenates block data for hashing

        unsigned char hash[SHA256_DIGEST_LENGTH]; // Array to store hash output
        SHA256((unsigned char*)input.c_str(), input.length(), hash);

        std::stringstream hashStream;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            hashStream << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }
        return hashStream.str(); // Returns the final hash as a string
    }

    // Getter functions for retrieving block information
    std::string getHash() const { return hash; }
    std::string getPreviousHash() const { return previousHash; }
    std::string getData() const { return data; }
    int getIndex() const { return index; }

    // Mines the block by finding a hash that starts with a given number of leading zeros (Proof of Work)
    void mineBlock(int difficulty) {
        std::string target(difficulty, '0'); // Example: difficulty = 4, target = "0000"
        do {
            nonce++;            // Increment nonce to try different hashes
            hash = calculateHash(); // Recalculate hash with the new nonce
        } while (hash.substr(0, difficulty) != target); // Repeat until condition is met

        std::cout << "Block mined! Hash: " << hash << " Nonce: " << nonce << std::endl;
    }
};

// Blockchain class manages the chain of blocks
class Blockchain {
private:
    std::vector<Block> chain; // Vector to store the chain of blocks
    int difficulty;           // Mining difficulty (number of leading zeros required in hash)

    // Creates the first block in the blockchain (Genesis Block)
    Block createGenesisBlock() {
        return Block(0, "0", "Genesis Block");
    }

public:
    // Constructor initializes the blockchain with the Genesis Block
    Blockchain(int diff = 4) : difficulty(diff) {
        chain.push_back(createGenesisBlock());
    }

    // Adds a new block to the blockchain with the given data
    void addBlock(std::string data) {
        Block newBlock(chain.size(), chain.back().getHash(), data); // Create new block
        newBlock.mineBlock(difficulty); // Perform mining before adding to chain
        chain.push_back(newBlock); // Add mined block to the chain
    }

    // Checks if the blockchain is valid by verifying hashes and links
    bool isChainValid() const {
        for (size_t i = 1; i < chain.size(); i++) {
            const Block& current = chain[i];
            const Block& previous = chain[i - 1];

            // Verify that the stored hash matches the recalculated hash
            if (current.getHash() != current.calculateHash()) {
                std::cout << "Block " << i << " has been tampered with!" << std::endl;
                return false;
            }

            // Verify that the block links correctly to the previous block
            if (current.getPreviousHash() != previous.getHash()) {
                std::cout << "Block " << i << " is not linked correctly!" << std::endl;
                return false;
            }
        }
        return true;
    }

    // Prints all blocks in the blockchain
    void printChain() const {
        for (const auto& block : chain) {
            std::cout << "Block " << block.getIndex() 
                      << " [Hash: " << block.getHash() 
                      << ", PrevHash: " << block.getPreviousHash() 
                      << ", Data: " << block.getData() << "]" << std::endl;
        }
    }
};

int main() {
    Blockchain bc(4); // Initialize blockchain with difficulty level 4

    std::cout << "Mining block 1..." << std::endl;
    bc.addBlock("Transaction 1: Alice sends 10 coins to Bob");

    std::cout << "Mining block 2..." << std::endl;
    bc.addBlock("Transaction 2: Bob sends 5 coins to Charlie");

    // Display the contents of the blockchain
    std::cout << "\nBlockchain contents:" << std::endl;
    bc.printChain();

    // Verify the blockchain's integrity
    std::cout << "\nIs blockchain valid? " << (bc.isChainValid() ? "Yes" : "No") << std::endl;

    return 0;
}